#include "home2/home2.hpp"

using namespace cfl;
using namespace std;

// YIELD TO MATURITY FOR COUPON BOND
double prb::yieldTMCouponBond(double dRate, double dPeriod, double dMaturity,
                              double dInitialTime, double dPrice, double dYield0,
                              double dErr)
{
    double dYield = dYield0;
    double dUpdate = INT_MAX;
    double dBond, dDuration;
    while (std::abs(dUpdate) >= dErr) {
        dBond = couponBond(dRate, dPeriod, dMaturity, dYield, dInitialTime, false);
        dDuration = durationCouponBond(dRate, dPeriod, dMaturity, dYield, dInitialTime);
        dUpdate = (dPrice - dBond) / dDuration; 
        dYield -= dUpdate;
    }
    return dYield;
}