#include "home1/home1.hpp"

using namespace cfl;
using namespace std;


// SVENSSON YIELD CURVE
Function prb::yieldSvensson(double dC0, double dC1, double dC2, double dC3, 
                            double dLambda1, double dLambda2, double dInitialTime) 
{
    std::function<double(double)> uYieldSvensson = [dC0, dC1, dC2, dC3, dLambda1, dLambda2, dInitialTime](double dT) 
    {
        PRECONDITION(dT >= dInitialTime);
        double dX1 = dLambda1 * (dT - dInitialTime);
        double dX2 = dLambda2 * (dT - dInitialTime);
        dX1 = (std::abs(dX1) < cfl::EPS) ? 1. + dX1 : (1. - std::exp(-dX1)) / dX1;
        dX2 = (std::abs(dX2) < cfl::EPS) ? 1. + dX2 : (1. - std::exp(-dX2)) / dX2;
        return dC0 + dC1 * dX1 
                + dC2 * (dX1 - std::exp(-dLambda1 * (dT - dInitialTime)))
                + dC3 * (dX2 - std::exp(-dLambda2 * (dT - dInitialTime)));
    };
    return Function(uYieldSvensson, dInitialTime);
}
