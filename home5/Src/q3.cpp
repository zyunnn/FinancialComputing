#include "home5/home5.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::discountRateFit(const std::vector<double> &rPeriods,
                                   const std::vector<double> &rRates,
                                   double dInitialTime, cfl::Fit &rFit,
                                   cfl::Function &rErr) 
{
    PRECONDITION(rPeriods.size() == rRates.size());
    PRECONDITION(rPeriods.size() > 0);
    PRECONDITION(std::is_sorted(rPeriods.begin(), rPeriods.end(), std::less_equal<double>()));

    vector<double> uTimes(rPeriods.size());
    std::transform(rPeriods.begin(), rPeriods.end(), uTimes.begin(), 
                   [&dInitialTime](double dPeriod) { return dInitialTime + dPeriod; });

    vector<double> uYield(rPeriods.size());
    std::transform(rPeriods.begin(), rPeriods.end(), rRates.begin(), uYield.begin(),
                   [](double dPeriod, double dRate) { return - std::log(1 / (1 + dRate * dPeriod)) / dPeriod; });
    
    rFit.assign(begin(uTimes), end(uTimes), begin(uYield));
    Function uT([dInitialTime](double dT) { return dT - dInitialTime; }, dInitialTime);
    Function uDiscount = exp(-rFit.fit() * uT);
    rErr = uDiscount * uT * rFit.err();
    return uDiscount;
}