#include "home4/home4.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::discountSvenssonFit(const std::vector<double> &rTimes,
                                       const std::vector<double> &rDF,
                                       double dLambda1, double dLambda2,
                                       double dInitialTime, cfl::Function &rErr,
                                       cfl::FitParam &rParam)
{
    PRECONDITION(rTimes.size() == rDF.size());
    PRECONDITION(rTimes.size() > 0);
    PRECONDITION(rTimes.front() > dInitialTime);
    PRECONDITION(std::is_sorted(rTimes.begin(), rTimes.end(), std::less_equal<double>()));
    PRECONDITION(dLambda1 > 0);
    PRECONDITION(dLambda2 > 0);
    PRECONDITION(dLambda1 != dLambda2);

    // Market yield
    vector<double> uGamma(rTimes.size());
    std::transform(rTimes.begin(), rTimes.end(), rDF.begin(), uGamma.begin(), 
                   [&dInitialTime](double dT, double dD) 
                   { 
                    return -std::log(dD) / (dT - dInitialTime); 
                   });

    // Least-squares fit
    Function uFree = Function(0.);
    std::vector<Function> uBase(4, Function (1.));
    uBase[1] = Function([&dInitialTime, &dLambda1](double dX)
                        {
                            return (1 - std::exp(-dLambda1 * (dX - dInitialTime))) / (dLambda1 * (dX - dInitialTime));
                        });
    uBase[2] = Function([&dInitialTime, &dLambda1](double dX)
                        { 
                            return (1 - std::exp(-dLambda1 * (dX - dInitialTime))) / (dLambda1 * (dX - dInitialTime)) 
                                      - std::exp(-dLambda1 * (dX - dInitialTime)); 
                        });
    uBase[3] = Function([&dInitialTime, &dLambda2](double dX)
                        { 
                            return (1 - std::exp(-dLambda2 * (dX - dInitialTime))) / (dLambda2 * (dX - dInitialTime)) 
                                      - std::exp(-dLambda2 * (dX - dInitialTime)); 
                        });
    Fit uFit = prb::linear(uBase, uFree);
    uFit.assign(begin(rTimes), end(rTimes), begin(uGamma));
    Function uF = uFit.fit();
    rErr = uFit.err();
    rParam = uFit.param();

    // Discount curve
    std::function<double(double)> uDiscountSvenssonFit = [dLambda1, dLambda2, dInitialTime, 
                                        dC0 = rParam.fit[0], dC1 = rParam.fit[1], 
                                        dC2 = rParam.fit[2], dC3 = rParam.fit[3]](double dT)
    {
        PRECONDITION(dT >= dInitialTime);
        if (dT == dInitialTime) return 1.;

        double dX1 = std::exp(-dLambda1 * (dT - dInitialTime));
        double dX2 = std::exp(-dLambda2 * (dT - dInitialTime));
        double dY1 = (1 - dX1) / (dLambda1 * (dT - dInitialTime));
        double dY2 = (1 - dX2) / (dLambda2 * (dT - dInitialTime));

        double dYield = dC0 + dC1 * dY1 + dC2 * (dY1 - dX1) + dC3 * (dY2 - dX2);
        return std::exp(-dYield * (dT - dInitialTime));
    };

    return Function(uDiscountSvenssonFit, dInitialTime);
}