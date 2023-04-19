#include "home6/home6.hpp"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_halfcomplex.h>

using namespace cfl;
using namespace std;


class FFT2 : public IGaussRollback
{
public:
    FFT2() {}
    
    FFT2(unsigned iSize, double dH, double dVar) : m_dH(dH), m_dVar(dVar), m_iSize(iSize) {}

    IGaussRollback *newObject(unsigned iSize, double dH, double dVar) const
    {
        return new FFT2(iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
        double dA[m_iSize];
        std::copy(begin(rValues), end(rValues), dA);
        
        gsl_fft_real_radix2_transform(dA, 1, m_iSize);

        for (int k = 1; k <= m_iSize/2; k++) 
        {
            double dMult = std::exp(-0.5 * pow(2. * M_PI * k / (m_iSize * m_dH), 2) * m_dVar);
            dA[k] *= dMult;
            dA[m_iSize-k] *= dMult;
        }

        gsl_fft_halfcomplex_radix2_inverse(dA, 1, m_iSize);

        rValues = std::valarray(dA, m_iSize);
    }

private:
    double m_dH, m_dVar;
    unsigned m_iSize;
};


cfl::GaussRollback prb::fft2()
{
    return cfl::GaussRollback(new FFT2());
}

