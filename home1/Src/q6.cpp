#include "home1/home1.hpp"

using namespace cfl;
using namespace std;

// FORWARD RATES
Function prb::forwardRate(double dPeriod,
                          const cfl::Function &rDiscount)
{
    std::function<double(double)> uForwardRate = [dPeriod, rDiscount](double dT) 
    {
        double dSpot1 = rDiscount(dT);
        double dSpot2 = rDiscount(dT + dPeriod);
        return (dSpot1 / dSpot2 - 1) / dPeriod;
    };
    return Function(uForwardRate);
}