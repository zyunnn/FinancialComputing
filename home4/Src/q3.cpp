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

    // Helper function
    Function uT([dInitialTime](double dT) { return dT - dInitialTime; }, dInitialTime);

    // Market yield
    vector<double> uGamma(rDiscountTimes.size());
    std::transform(rDiscountTimes.begin(), rDiscountTimes.end(), rDiscountFactors.begin(), uGamma.begin(), 
                   [uT](double dT, double dD)  {  return -std::log(dD) / uT(dT);  });

    // Fitting functions
    Function uFree (0.);
    Function uBasis1 (1.);
    Function uBasis2 ([dLambda, uT](double dX)
                     { 
                        double dY = dLambda * uT(dX);
                        return (1 - std::exp(-dY)) / dY; 
                     });
    std::vector<Function> uBase{uBasis1, uBasis2};

    // Least-squares fit
    Fit uFit = prb::linear(uBase, uFree);
    uFit.assign(begin(rDiscountTimes), end(rDiscountTimes), begin(uGamma));
    rParam = uFit.param();

    // Discount curve and error of fit
    Function uDiscount([uFit, uT](double dT) 
                       { 
                            PRECONDITION(uT(dT) >= 0); 
                            return uT(dT) ? exp(-uFit.fit()(dT) * uT(dT)): 1.; 
                        });
                       
    rErr = Function([uDiscount, uFit, uT](double dT)
                    { 
                        PRECONDITION(uT(dT) >= 0); 
                        return uT(dT) ? uDiscount(dT) * uT(dT) * uFit.err()(dT) : 0.; 
                    });

    return uDiscount;
}