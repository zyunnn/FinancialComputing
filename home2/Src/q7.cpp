#include "home2/home2.hpp"

using namespace cfl;
using namespace std;

// FORWARD YIELD TO MATURITY FOR A CASH FLOW
cfl::Function prb::forwardYTMCashFlow(const std::vector<double> &rPayments,
                                      const std::vector<double> &rPaymentTimes,
                                      const cfl::Function &rForward,
                                      double dInitialTime, double dY0, double dY1,
                                      const cfl::Root &rRoot)
{
    std::function<double(double)> uForwardYTMCashFlow = [rPayments, rPaymentTimes, rForward, dInitialTime, dY0, dY1, rRoot](double dT) 
    {
        PRECONDITION(dT >= dInitialTime);
        std::function<double(double)> uHelper = [rPayments, rPaymentTimes, rForward, dInitialTime, dT](double dYTM) mutable
        {
            double dPrice = 0.;
            auto iI = std::lower_bound(rPaymentTimes.begin(), rPaymentTimes.end(), dT) - rPaymentTimes.begin();
            for (; iI < rPaymentTimes.size(); iI++) 
            {
                dPrice += rPayments[iI] * std::exp(-dYTM * (rPaymentTimes[iI] - dInitialTime));
            }
            dPrice *= std::exp(dYTM * (dT - dInitialTime));
            return dPrice - rForward(dT);
        };
        Function rF(uHelper, dY0, dY1);
        return rRoot.find(rF, dY0, dY1);
    };
    return Function(uForwardYTMCashFlow, dInitialTime);
}

