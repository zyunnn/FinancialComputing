#include "home1/home1.hpp"

using namespace cfl;
using namespace std;


// STATIONARY IMPLIED VOLATILITY IN BLACK MODEL
Function prb::volatilityBlack(double dSigma, double dLambda, double dInitialTime) 
{
    std::function<double(double)> uVolatilityBlack = [dSigma, dLambda, dInitialTime](double dT) 
    {
        PRECONDITION(dT >= dInitialTime);
        double dX = 2. * dLambda * (dT - dInitialTime);
        dX = (std::abs(dX) < cfl::EPS) ? 1. + dX : (1. - std::exp(-dX)) / dX;
        return dSigma * std::sqrt(dX);
    };
    return Function(uVolatilityBlack, dInitialTime);
}


