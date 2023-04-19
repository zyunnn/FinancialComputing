#include "home6/home6.hpp"

using namespace cfl;
using namespace std;


class Explicit : public IGaussRollback
{
public:
    Explicit(double dP, unsigned iSize = 0) : m_dP(dP), m_iSize(iSize) {}

    Explicit(double dP, unsigned iSize, double dH, double dVar) 
        : Explicit(dP, iSize)
    {
        m_iStep = std::ceil(dVar / (2 * pow(dH, 2) * dP));
        m_dQ = dVar / (2 * pow(dH, 2) * m_iStep);
    }

    IGaussRollback *newObject(unsigned iSize, double dH, double dVar) const
    {
        return new Explicit(m_dP, iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
        std::valarray<double> uGrid(rValues);

        for (int m = 0; m < m_iStep; m++) 
        {
            // Compute delta for current timestep
            std::valarray<double> uDelta(m_iSize);
            for (int n = 0; n < m_iSize; n++)
            {
                int idx = n == 0 ? 1 : (n == m_iSize-1 ? m_iSize-2 : n);
                uDelta[n] = uGrid[idx-1] - 2 * uGrid[n] + uGrid[idx+1];
            }
            // Update value
            uDelta *= m_dQ;
            uGrid += uDelta;
        }
        rValues = uGrid;
    }

private:
    double m_dP, m_dQ;
    unsigned m_iSize;
    int m_iStep;
};

cfl::GaussRollback prb::expl(double dP)
{
    PRECONDITION((dP > 0) && (dP <= 0.5));
    return cfl::GaussRollback(new Explicit(dP));
}
