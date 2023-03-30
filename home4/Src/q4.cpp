#include "home4/home4.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::discountNelsonSiegelFit(const std::vector<double> &rTimes,
                                           const std::vector<double> &rDF,
                                           double dLambda, double dInitialTime,
                                           cfl::Function &rErr, cfl::FitParam &rParam)
{
    PRECONDITION(rTimes.size() == rDF.size());
    PRECONDITION(rTimes.size() > 0);
    PRECONDITION(rTimes.front() > dInitialTime);
    PRECONDITION(std::is_sorted(rTimes.begin(), rTimes.end(), std::less_equal<double>()));
    PRECONDITION(dLambda >= 0);

    // Market yield
    vector<double> uGamma(rTimes.size());
    std::transform(rTimes.begin(), rTimes.end(), rDF.begin(), uGamma.begin(), 
                   [&dInitialTime](double dT, double dD) 
                   { 
                    return -std::log(dD) / (dT - dInitialTime); 
                   });

    // Least-squares fit
    Function uFree = Function(0.);
    std::vector<Function> uBase(3, Function (1.));
    uBase[1] = Function([&dInitialTime, &dLambda](double dX)
                        {
                            return (1 - std::exp(-dLambda * (dX - dInitialTime))) / (dLambda * (dX - dInitialTime));
                        });
    uBase[2] = Function([&dInitialTime, &dLambda](double dX)
                        { 
                            return (1 - std::exp(-dLambda * (dX - dInitialTime))) / (dLambda * (dX - dInitialTime)) - 
                                    std::exp(-dLambda * (dX - dInitialTime)); 
                        });
    Fit uFit = prb::linear(uBase, uFree);
    uFit.assign(begin(rTimes), end(rTimes), begin(uGamma));
    Function uF = uFit.fit();
    rErr = uFit.err();
    rParam = uFit.param();

    // Discount curve
    std::function<double(double)> uDiscountNelsonSiegelFit = 
        [dLambda, dInitialTime, dC0 = rParam.fit[0], dC1 = rParam.fit[1], dC2 = rParam.fit[2]](double dT)
    {
        PRECONDITION(dT >= dInitialTime);
        if (dT == dInitialTime) return 1.;

        double dX = (1 - std::exp(-dLambda * (dT - dInitialTime))) / (dLambda * (dT - dInitialTime));
        double dYield = dC0 + dC1 * dX + dC2 * (dX - std::exp(-dLambda * (dT - dInitialTime)));
        return std::exp(-dYield * (dT - dInitialTime));
    };

    return Function(uDiscountNelsonSiegelFit, dInitialTime);
}