#include "home5/home5.hpp"

using namespace cfl;
using namespace std;

cfl::Function prb::forwardFXCarryFit(double dSpotFX, const std::vector<double> &rTimes,
                                     const std::vector<double> &rDomesticDiscountFactors,
                                     const std::vector<double> &rForeignDiscountFactors,
                                     double dInitialTime, cfl::Fit &rFit, cfl::Function &rErr)
{
    PRECONDITION(rTimes.size() == rDomesticDiscountFactors.size());
    PRECONDITION(rTimes.size() == rForeignDiscountFactors.size());
    PRECONDITION(rTimes.size() > 0);
    PRECONDITION(std::is_sorted(rTimes.begin(), rTimes.end(), std::less_equal<double>()));
    PRECONDITION(rTimes[0] > dInitialTime);

    vector<double> uCoC(rTimes.size());
    for (int i = 0; i < rTimes.size(); i++) {
        uCoC[i] = (std::log(rForeignDiscountFactors[i] / rDomesticDiscountFactors[i])) / (rTimes[i] - dInitialTime);
    }

    rFit.assign(begin(rTimes), end(rTimes), begin(uCoC));
    Function uT([dInitialTime](double dT) { return dT - dInitialTime; });
    Function uDiscount = dSpotFX * exp(rFit.fit() * uT);
    rErr = uDiscount * uT * rFit.err();
    return uDiscount;
}