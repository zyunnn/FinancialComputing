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

    // Helper function
    Function uT([dInitialTime](double dT) { return dT - dInitialTime; }, dInitialTime);

    // Market yield
    vector<double> uGamma(rTimes.size());
    std::transform(rTimes.begin(), rTimes.end(), rDF.begin(), uGamma.begin(), 
                   [uT](double dT, double dD) { return -std::log(dD) / uT(dT); });

    // Fitting function
    Function uFree (0.);
    Function uBasis1 (1.);
    Function uBasis2 ([dLambda, uT](double dX)
                     {
                        double dY = dLambda * uT(dX);
                        return (1 - std::exp(-dY)) / dY;
                     });
    Function uBasis3 ([dLambda, uT](double dX)
                     { 
                        double dY = dLambda * uT(dX);
                        return (1 - std::exp(-dY)) / dY - std::exp(-dY); 
                     });
    std::vector<Function> uBase{uBasis1, uBasis2, uBasis3};

    // Least-squares fit
    Fit uFit = prb::linear(uBase, uFree);
    uFit.assign(begin(rTimes), end(rTimes), begin(uGamma));
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