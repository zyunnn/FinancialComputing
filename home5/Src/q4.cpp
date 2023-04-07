#include "home5/home5.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace cfl;
using namespace std;


cfl::Function prb::discountSwapFit(const std::vector<double> &rSwapRates,
                                   double dPeriod, double dInitialTime,
                                   cfl::Fit &rFit, cfl::Function &rErr)
{
    int iM = rSwapRates.size();
    vector<double> uMaturity(iM);
    std::iota(uMaturity.begin(), uMaturity.end(), 1);
    std::transform(uMaturity.begin(), uMaturity.end(), uMaturity.begin(), 
                  [dInitialTime, dPeriod](double dM) { return dInitialTime + dM * dPeriod; });

    vector<double> uDiscountFactor(iM);
    uDiscountFactor.front() = 1 / (1 + rSwapRates[0] * dPeriod);
    for (int i = 1; i < iM; i++) 
    {
        uDiscountFactor[i] = (1 - rSwapRates[i] * dPeriod * std::accumulate(uDiscountFactor.begin(), uDiscountFactor.begin()+i, 0.)) / 
                             (1 + rSwapRates[i] * dPeriod);
    }    

    vector<double> uYield(iM);
    std::transform(uDiscountFactor.begin(), uDiscountFactor.end(), uMaturity.begin(), uYield.begin(),
                  [dInitialTime](double dDF, double dM)
                  { return -1 * std::log(dDF) / (dM - dInitialTime); });
    
    rFit.assign(begin(uMaturity), end(uMaturity), begin(uYield));
    Function uT([dInitialTime](double dT) { return dT - dInitialTime; }, dInitialTime);
    Function uDiscount = exp(-rFit.fit() * uT);
    rErr = uDiscount * uT * rFit.err();
    return uDiscount;
}