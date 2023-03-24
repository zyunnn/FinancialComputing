#include "home2/home2.hpp"

using namespace cfl;
using namespace std;

// YIELD TO MATURITY FOR A CASH FLOW
double prb::yieldTMCashFlow(const std::vector<double> &rPayments,
                            const std::vector<double> &rPaymentTimes,
                            double dValue, double dInitialTime,
                            double dY0, double dY1, const cfl::Root &rRoot)
{
    std::function<double(double)> uYieldYTMCashFlow = [rPayments, rPaymentTimes, dValue, dInitialTime](double dYTM) 
    {
        double dPrice = 0.;
        for (int i = 0; i < rPayments.size(); i++) {
            dPrice += rPayments[i] * std::exp(-dYTM * (rPaymentTimes[i] - dInitialTime));
        }
        return dPrice - dValue;
    };
    Function rF(uYieldYTMCashFlow, dY0, dY1);
    return rRoot.find(rF, dY0, dY1);
};
