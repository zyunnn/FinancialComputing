#include "home4/home4.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::discountYieldFit(const std::vector<double> &rTimes, const std::vector<double> &rDF,
                                    double dInitialTime, cfl::Fit &rFit, cfl::Function &rErr) 
{
    PRECONDITION(rTimes.size() == rDF.size());
    PRECONDITION(rTimes.size() > 0);
    PRECONDITION(rTimes.front() > dInitialTime);
    PRECONDITION(std::is_sorted(rTimes.begin(), rTimes.end(), std::less_equal<double>()));

    vector<double> uGamma(rTimes.size());
    std::transform(rTimes.begin(), rTimes.end(), rDF.begin(), uGamma.begin(), 
                   [&dInitialTime](double dT, double dD) 
                   {
                    return -std::log(dD) / (dT - dInitialTime);
                   });

    rFit.assign(begin(rTimes), end(rTimes), begin(uGamma));
    Function uF = rFit.fit();

    std::function<double(double)> uDiscountYieldFit = [dInitialTime, uF](double dT)
    {
        PRECONDITION(dT >= dInitialTime);
        return std::exp(-uF(dT) * (dT - dInitialTime));
    };

    return Function(uDiscountYieldFit, dInitialTime);
}