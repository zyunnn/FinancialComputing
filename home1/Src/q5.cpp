#include "home1/home1.hpp"
#include <vector>
#include <numeric>

using namespace cfl;
using namespace std;


Function prb::forwardCouponBond(double dRate, double dPeriod, double dMaturity,
                                const cfl::Function &rDiscount,
                                double dInitialTime, bool bClean) 
{
    std::function<double(double)> uForwardCouponBond = [dRate, dPeriod, dMaturity, rDiscount, dInitialTime, bClean](double dT) 
    {
        // Follow Q4 approach
        PRECONDITION(dT >= dInitialTime);
        double dCoupon = dRate * dPeriod;
        vector<double> vCouponTimes, vDistFactors;
        for (int i = 0; i < (dMaturity - dInitialTime)/dPeriod; i++) {
            double dTime = dPeriod * (i+1) + dInitialTime;
            vCouponTimes.push_back(dTime);
            vDistFactors.push_back(rDiscount(dTime));
        };

        // Spot price = Coupon + Principal payment
        double dSpot = vDistFactors[vDistFactors.size()-1] + dCoupon 
                            * accumulate(vDistFactors.begin(), vDistFactors.end(), 0.0);
        
        double dPaid = 0;
        auto it = lower_bound(vCouponTimes.begin(), vCouponTimes.end(), dT);
        for (int i = 0; i < it - vCouponTimes.begin(); i++) {
            dPaid += (dCoupon * vDistFactors[i]);
        }
        
        // Dirty price
        double dDirty = (dSpot - dPaid) / rDiscount(dT);
        if (!bClean) { return dDirty; } 

        // Adjust by accrued interest
        double i = it - vCouponTimes.begin();
        dDirty -= i == 0 ? dRate * (dT - dInitialTime) : dRate * (dT - vCouponTimes[i-1]);        
        return dDirty;
            
    };
    return Function(uForwardCouponBond, dInitialTime);    
}