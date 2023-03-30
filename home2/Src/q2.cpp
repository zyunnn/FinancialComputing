#include "home2/home2.hpp"

using namespace cfl;
using namespace std;

// DURATION FOR A COUPON BOND
double prb::durationCouponBond(double dRate, double dPeriod, double dMaturity,
                               double dYTM, double dInitialTime) 
{
    double dCoupon = dRate * dPeriod;
    double dPrincipal = std::exp(-dYTM * (dMaturity - dInitialTime));
    vector<double> vCouponTimes;
    for (int i = 0; i < (dMaturity - dInitialTime)/dPeriod; i++) {
        vCouponTimes.push_back(dMaturity - (dPeriod * i));
    }
    sort(vCouponTimes.begin(), vCouponTimes.end());

    double d1 = 0;
    for (double dT : vCouponTimes) {
        d1 += -(dT - dInitialTime) * std::exp(-dYTM * (dT - dInitialTime));
    }
    return -(d1 * dCoupon 
                - (dMaturity - dInitialTime) * dPrincipal);
}