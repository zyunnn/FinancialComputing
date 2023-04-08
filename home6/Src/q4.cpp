#include "home6/home6.hpp"
#include <vector>

using namespace cfl;
using namespace std;


class FFT : public IGaussRollback
{
public:
    FFT(double dP) : m_dP(dP) {}

    FFT(double dP, unsigned iSize, double dH, double dVar) 
        : FFT(dP)
    {
        m_iStep = std::ceil(dVar / (2 * pow(dH, 2) * dP));
        m_dQ = dVar / (2 * pow(dH, 2) * m_iStep);
    }

    IGaussRollback *newObject(unsigned iSize, double dH, double dVar) const
    {
        return new FFT(m_dP, iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
    }

private:
    double m_dP, m_dQ;
    int m_iStep;
};

cfl::GaussRollback prb::fft2()
{
    return cfl::GaussRollback(new FFT2());
}
