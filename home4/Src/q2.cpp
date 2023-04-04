#include "home4/home4.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::discountYieldFit(const std::vector<double> &rTimes, const std::vector<double> &rDF,
                                    double dInitialTime, cfl::Fit &rFit, cfl::Function &rErr) 
{
    PRECONDITION(rTimes.size() == rDF.size());
    PRECONDITION(rTimes.size() > 0);
    PRECONDITION(rTimes.front() > dInitialTime);
    PRECONDITION(std::is_sorted(rTimes.begin(), rTimes.end(), std::less_equal<double>()));

    // Helper function
    Function uT([dInitialTime](double dT) { return dT - dInitialTime; }, dInitialTime);

    // Market yield
    vector<double> uGamma(rTimes.size());
    std::transform(rTimes.begin(), rTimes.end(), rDF.begin(), uGamma.begin(), 
                   [uT](double dT, double dD) { return -std::log(dD) / uT(dT); });

    // Least-squares fit
    rFit.assign(begin(rTimes), end(rTimes), begin(uGamma));
    
    // Discount curve and error of fit
    Function uDiscount = exp(-rFit.fit() * uT);
    rErr = uDiscount * uT * rFit.err();
    return uDiscount;
}