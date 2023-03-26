#include "home3/home3.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::forwardCarryInterp(double dSpot,
                                      const std::vector<double> &rDeliveryTimes,
                                      const std::vector<double> &rForwardPrices,
                                      double dInitialCarryRate, double dInitialTime,
                                      const cfl::Interp &rInterp)
{
    std::vector<double> vCostOfCarry {dInitialCarryRate};
    std::vector<double> vTimes {dInitialTime};
    for (int i = 0; i < rDeliveryTimes.size(); i++) 
    {
        vTimes.push_back(rDeliveryTimes[i]);
        vCostOfCarry.push_back(std::log(rForwardPrices[i] / dSpot) / (rDeliveryTimes[i] - dInitialTime));
    }
    Function uF = rInterp.interpolate(begin(vTimes), end(vTimes), begin(vCostOfCarry));

    std::function<double(double)> uForwardCarryInterp = [dSpot, dInitialTime, uF](double dT) 
    {
        PRECONDITION(dT >= dInitialTime);
        double dYield = uF(dT);
        return dSpot * std::exp(dYield * (dT - dInitialTime));
    };

    return Function(uForwardCarryInterp, dInitialTime);
} 