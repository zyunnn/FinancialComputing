#include "home5/home5.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::discountApproxFit(const std::vector<double> &rDiscountTimes,
                                     const std::vector<double> &rDiscountFactors,
                                     double dInitialTime, cfl::Fit &rFit,
                                     cfl::Function &rErr)
{
    int iM = rDiscountTimes.size();
    vector<double> uWeights(iM);
    std::transform(rDiscountTimes.begin(), rDiscountTimes.end(), rDiscountFactors.begin(), uWeights.begin(),
                   [dInitialTime](double dT, double dDF)
                   { return pow(dDF, 2) * pow(dT - dInitialTime, 2); });   
    
    vector<double> uYield(iM);
    std::transform(rDiscountTimes.begin(), rDiscountTimes.end(), rDiscountFactors.begin(), uYield.begin(),
                   [dInitialTime](double dT, double dDF) 
                   { return -std::log(dDF) / (dT - dInitialTime); });
    
    rFit.assign(begin(rDiscountTimes), end(rDiscountTimes), begin(uYield),
                begin(uWeights), true);
    
    Function uT([dInitialTime](double dT) { return dT - dInitialTime; }, dInitialTime);
    Function uDiscount = exp(-rFit.fit() * uT);
    rErr = uDiscount * uT * rFit.err();
    return uDiscount;
}