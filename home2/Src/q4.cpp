#include "home2/home2.hpp"

using namespace cfl;
using namespace std;

// YIELD TO MATURITY FOR COUPON BOND WITH cfl::RootD
double prb::yieldTMCouponBond(double dRate, double dPeriod, double dMaturity,
                              double dInitialTime, double dPrice, double dYield0,
                              const cfl::RootD &rRootD) 
{
    std::function<double(double)> uBond = [dRate, dPeriod, dMaturity, dInitialTime, dPrice](double dYTM) 
    {
        return couponBond(dRate, dPeriod, dMaturity, dYTM, dInitialTime, false) - dPrice;
    };
    std::function<double(double)> uDuration = [dRate, dPeriod, dMaturity, dInitialTime] (double dYTM)
    {
        return -1. * durationCouponBond(dRate, dPeriod, dMaturity, dYTM, dInitialTime);
    };
    Function rF(uBond, dYield0);
    Function rDF(uDuration, dYield0);
    return rRootD.find(rF, rDF, dYield0);
}