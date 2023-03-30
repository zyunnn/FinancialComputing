#include "home2/home2.hpp"

using namespace cfl;
using namespace std;

// PRICE FOR A COUPON BOND
double prb::couponBond(double dRate, double dPeriod, double dMaturity,
                       double dYTM, double dInitialTime, bool bClean) 
{
    double dCoupon = dRate * dPeriod;
    double dPrincipal = std::exp(-dYTM * (dMaturity - dInitialTime));
     
    vector<double> vCouponTimes{dMaturity};
    for (int i = 0; i < (dMaturity - dInitialTime)/dPeriod; i++) {
        vCouponTimes.push_back(dMaturity - (dPeriod * (i+1)));
    }
    sort(vCouponTimes.begin(), vCouponTimes.end());
    
    // get discounting factors
    double dFactor = 0;
    for (int i = 1; i < vCouponTimes.size(); i++) {
        dFactor += std::exp(-dYTM * (vCouponTimes[i] - dInitialTime));
    }
    
    // dirty price
    double dPrice = dCoupon * dFactor + dPrincipal;
    if (!bClean) return dPrice;

    // clean price
    auto it = lower_bound(vCouponTimes.begin(), vCouponTimes.end(), dInitialTime);
    dPrice -= dRate * (dInitialTime - *(it-1));
    return dPrice;
}