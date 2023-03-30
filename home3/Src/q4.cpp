#include "home3/home3.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::volatilityVarInterp(const std::vector<double> &rTimes,
                                       const std::vector<double> &rVols,
                                       double dInitialTime,
                                       const cfl::Interp &rInterp)
{
    PRECONDITION(rTimes.size() == rVols.size());
    PRECONDITION(rTimes.size() > 0);
    PRECONDITION(rTimes.front() > dInitialTime);
    PRECONDITION(std::is_sorted(rTimes.begin(), rTimes.end(), std::less_equal<double>()));

    std::vector<double> uTimes(rTimes.size() + 1);
    uTimes.front() = dInitialTime;
    std::copy(rTimes.begin(), rTimes.end(), uTimes.begin() + 1);

    std::vector<double> uMarketVar(uTimes.size());
    uMarketVar.front() = 0.;
    std::transform(rVols.begin(), rVols.end(), rTimes.begin(), uMarketVar.begin() + 1,
                   [&dInitialTime](double dVol, double dTimes)
                   { return std::pow(dVol, 2) * (dTimes - dInitialTime); });
    
    Function uF = rInterp.interpolate(begin(uTimes), end(uTimes), begin(uMarketVar));

    std::function<double(double)> uVolatilityVarInterp = [dInitialTime, rTimes, uF](double dT)
    {
        PRECONDITION(dT >= dInitialTime);
        dT = (dT == dInitialTime) ? rTimes[0] : dT; 
        return std::sqrt(uF(dT) / (dT - dInitialTime));
    };

    return Function(uVolatilityVarInterp, dInitialTime); 
}
