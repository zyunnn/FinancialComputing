#include "home3/home3.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::forwardCarrySteffenInterp(double dSpot,
                                             const std::vector<double> &rDeliveryTimes,
                                             const std::vector<double> &rForwardPrices,
                                             double dInitialTime)
{
    PRECONDITION(rDeliveryTimes.size() == rForwardPrices.size());
    PRECONDITION(rDeliveryTimes.size() > 0);
    PRECONDITION(rDeliveryTimes.front() > dInitialTime);
    PRECONDITION(std::is_sorted(rDeliveryTimes.begin(), rDeliveryTimes.end(), std::less_equal<double>()));

    std::vector<double> uTimes(rDeliveryTimes.size() + 1);
    uTimes.front() = dInitialTime;
    std::copy(rDeliveryTimes.begin(), rDeliveryTimes.end(), uTimes.begin() + 1);

    std::vector<double> uCostofCarry(uTimes.size());
    std::transform(rForwardPrices.begin(), rForwardPrices.end(), rDeliveryTimes.begin(), uCostofCarry.begin() + 1,
                   [&dSpot, &dInitialTime](double dPrice, double dTimes)
                   { return std::log(dPrice / dSpot) / (dTimes - dInitialTime); });
    uCostofCarry.front() = uCostofCarry[1];

    cfl::Interp rInterp = prb::steffen();
    Function uF = rInterp.interpolate(begin(uTimes), end(uTimes), begin(uCostofCarry));

    std::function<double(double)> uForwardCarrySteffenInterp = [dSpot, rDeliveryTimes, dInitialTime, uF](double dT)
    {
        PRECONDITION(dT >= dInitialTime);
        return dSpot * std::exp(uF(dT) * (dT - dInitialTime));
    };
    
    return Function(uForwardCarrySteffenInterp, dInitialTime);
}
