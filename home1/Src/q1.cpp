#include "home1/home1.hpp"

using namespace cfl;
using namespace std;


// COST-OF-CARRY RATE IN BLACK MODEL
Function prb::carryBlack(double dTheta, double dLambda, 
                         double dSigma, double dInitialTime) 
{
    std::function<double(double)> uCarryBlack = [dTheta, dLambda, dSigma, dInitialTime](double dT) 
    {
        PRECONDITION(dT >= dInitialTime);
        double dX = dLambda * (dT - dInitialTime);
        double dY = dLambda * (dT - dInitialTime) * 2.;
        dX = (std::abs(dX) < cfl::EPS) ? 1. + dX : (1. - std::exp(-dX)) / dX;
        dY = (std::abs(dY) < cfl::EPS) ? 1. + 0.5 * dY : (1. - std::exp(-dY)) / dY;
        return dTheta * dX + pow(dSigma,2) / 2 * dY;
    };
    return Function(uCarryBlack, dInitialTime);
}
