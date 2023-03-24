#include "home1/home1.hpp"
#include <vector>

using namespace cfl;
using namespace std;


// FORWARD PRICES FOR A STOCK WITH DIVIDENDS
Function prb::forwardStockDividends(double dSpot,
                                    const std::vector<double> &rDividendsTimes,
                                    const std::vector<double> &rDividends,
                                    const cfl::Function &rDiscount,
                                    double dInitialTime) 
{
    std::function<double(double)> uForwardStockDividends = [dSpot, rDividendsTimes, rDividends, rDiscount, dInitialTime](double dT) mutable
    {
        PRECONDITION(dT >= dInitialTime);
        auto it = lower_bound(rDividendsTimes.begin(), rDividendsTimes.end(), dT);
        double dDividend = 0;
        for (int i = 0; i < it - rDividendsTimes.begin(); i++) {
            dDividend += (rDividends[i] * rDiscount(rDividendsTimes[i]));
        }
        return (dSpot - dDividend) / rDiscount(dT);
    };
    return Function(uForwardStockDividends, dInitialTime);
}