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

    // Helper function
    Function uT([dInitialTime](double dT) { return dT - dInitialTime; }, dInitialTime);

    // Market yield
    vector<double> uGamma(rTimes.size());
    std::transform(rTimes.begin(), rTimes.end(), rDF.begin(), uGamma.begin(), 
                   [uT](double dT, double dD) { return -std::log(dD) / uT(dT); });

    // Least-squares fit
    Function uFree (0.);
    Function uBasis1 (1.);
    Function uBasis2 ([dLambda1, uT](double dX) 
                     {
                        double dY = dLambda1 * uT(dX);
                        return (1 - std::exp(-dY)) / dY;
                     });
    Function uBasis3 ([dLambda1, uT](double dX)
                     { 
                        double dY = dLambda1 * uT(dX);
                        return (1 - std::exp(-dY)) / dY - std::exp(-dY); 
                     });
    Function uBasis4 ([dLambda2, uT](double dX)
                     { 
                        double dY = dLambda2 * uT(dX);
                        return (1 - std::exp(-dY)) / dY - std::exp(-dY); 
                     });
    std::vector<Function> uBase{uBasis1, uBasis2, uBasis3, uBasis4};

    Fit uFit = prb::linear(uBase, uFree);
    uFit.assign(begin(rTimes), end(rTimes), begin(uGamma));
    rParam = uFit.param();

    // Discount curve and error of fit
    Function uDiscount ([dInitialTime, uFit](double dT)
                       { PRECONDITION(dT >= dInitialTime); 
                         return dT == dInitialTime ? 1. : std::exp(-uFit.fit()(dT) * (dT - dInitialTime)); });

    rErr = Function([uDiscount, uFit, dInitialTime](double dT) 
                    { return dT == dInitialTime ? 0. : uDiscount(dT) * (dT - dInitialTime) * uFit.err()(dT); });
    
    return uDiscount;
}