#include "home3/home3.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::volatilityVarInterp(const std::vector<double> &rTimes,
                                       const std::vector<double> &rVols,
                                       double dInitialTime,
                                       const cfl::Interp &rInterp)
{
    std::vector<double> vTimes{dInitialTime};
    std::vector<double> vMarketVar{0};
    for (int i = 0; i < rTimes.size(); i++) 
    {
        vTimes.push_back(rTimes[i]);
        vMarketVar.push_back(std::pow(rVols[i], 2) * (rTimes[i] - dInitialTime));
    }
    
    Function uF = rInterp.interpolate(begin(vTimes), end(vTimes), begin(vMarketVar));

    std::function<double(double)> uVolatilityVarInterp = [dInitialTime, rTimes, uF](double dT)
    {
        PRECONDITION(dT >= dInitialTime);
        dT = (dT == dInitialTime) ? rTimes[0] : dT; 
        return std::sqrt(uF(dT) / (dT - dInitialTime));
    };

    return Function(uVolatilityVarInterp, dInitialTime); 
}
