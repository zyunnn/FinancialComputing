#include "home4/home4.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::discountHullWhiteFit(const std::vector<double> &rDiscountTimes,
                                        const std::vector<double> &rDiscountFactors,
                                        double dLambda, double dInitialTime,
                                        cfl::Function &rErr, cfl::FitParam &rParam)
{
    PRECONDITION(rDiscountTimes.size() == rDiscountFactors.size());
    PRECONDITION(rDiscountTimes.size() > 0);
    PRECONDITION(rDiscountTimes.front() > dInitialTime);
    PRECONDITION(std::is_sorted(rDiscountTimes.begin(), rDiscountTimes.end(), std::less_equal<double>()));
    PRECONDITION(dLambda >= 0);

    // Market yield
    vector<double> uGamma(rDiscountTimes.size());
    std::transform(rDiscountTimes.begin(), rDiscountTimes.end(), rDiscountFactors.begin(), uGamma.begin(), 
                   [&dInitialTime](double dT, double dD) 
                   { 
                    return -std::log(dD) / (dT - dInitialTime); 
                   });

    // Least-squares fit
    Function uFree = Function(0.);
    std::vector<Function> uBase(2, Function (1.));
    uBase.back() = Function([&dInitialTime, &dLambda](double dX)
                            { 
                                return (1 - std::exp(-dLambda * (dX - dInitialTime))) / (dLambda * (dX - dInitialTime)); 
                            });
    Fit uFit = prb::linear(uBase, uFree);
    uFit.assign(begin(rDiscountTimes), end(rDiscountTimes), begin(uGamma));
    Function uF = uFit.fit();
    rErr = uFit.err();
    rParam = uFit.param();

    // Discount curve
    std::function<double(double)> uDiscountHullWhiteFit = 
        [dLambda, dInitialTime, dC0 = rParam.fit[0], dC1 = rParam.fit[1]](double dT)
    {
        PRECONDITION(dT >= dInitialTime);
        if (dT == dInitialTime) return 1.;

        double dYield = dC0 + dC1 * (1 - std::exp(-dLambda * (dT - dInitialTime))) / (dLambda * (dT - dInitialTime));
        return std::exp(-dYield * (dT - dInitialTime));
    };

    return Function(uDiscountHullWhiteFit, dInitialTime);
}