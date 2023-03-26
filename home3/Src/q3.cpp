#include "home3/home3.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::forwardCarrySteffenInterp(double dSpot,
                                             const std::vector<double> &rDeliveryTimes,
                                             const std::vector<double> &rForwardPrices,
                                             double dInitialTime)
{
    std::vector<double> vTimes {dInitialTime};
    std::vector<double> vCostOfCarry;
    for (int i = 0; i < rDeliveryTimes.size(); i++) 
    {
        vTimes.push_back(rDeliveryTimes[i]);
        vCostOfCarry.push_back(std::log(rForwardPrices[i] / dSpot) / (rDeliveryTimes[i] - dInitialTime));
    }
    vCostOfCarry.insert(begin(vCostOfCarry), vCostOfCarry[0]);

    cfl::Interp rInterp = prb::steffen();
    Function uF = rInterp.interpolate(begin(vTimes), end(vTimes), begin(vCostOfCarry));

    std::function<double(double)> uForwardCarrySteffenInterp = [dSpot, rDeliveryTimes, dInitialTime, uF](double dT)
    {
        PRECONDITION(dT >= dInitialTime);
        return dSpot * std::exp(uF(dT) * (dT - dInitialTime));
    };
    return Function(uForwardCarrySteffenInterp, dInitialTime);
}
