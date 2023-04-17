#include "home6/home6.hpp"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_halfcomplex.h>

using namespace cfl;
using namespace std;

#include <iostream>
#include <numeric>
#include <math.h>

#define _USE_MATH_DEFINES

class FFT2 : public IGaussRollback
{
public:
    FFT2() {}
    // FFT2(double dP) : m_dP(dP) {}

    FFT2(unsigned iSize, double dH, double dVar) : m_dH(dH)
    {
        // m_iStep = std::ceil(dVar / (2 * pow(dH, 2) * dP));
        // m_dQ = dVar / (2 * pow(dH, 2) * m_iStep);
    }

    IGaussRollback *newObject(unsigned iSize, double dH, double dVar) const
    {
        return new FFT2(iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
        int iN = rValues.size();
        int iK = (iN-1)/2;
        double dACoef[iN];
        // std::copy(begin(rValues), end(rValues), dACoef);
        for (int i = 0; i < iN; i++)
        { 
            dACoef[i] = rValues[i];
            // /iN;
        } 

        gsl_fft_halfcomplex_wavetable *hc = gsl_fft_halfcomplex_wavetable_alloc(iN);
        gsl_fft_real_workspace * work = gsl_fft_real_workspace_alloc(iN);
        gsl_fft_real_wavetable * real = gsl_fft_real_wavetable_alloc(iN);
        // gsl_fft_halfcomplex_wavetable * hcomplex = gsl_fft_halfcomplex_wavetable_alloc(iN);

        gsl_fft_halfcomplex_inverse(dACoef, 1, iN, hc, work);

        double b[iN];
        b[0] = dACoef[0];
        // std::copy(dACoef.begin(), dACoef.end()+iK, )
        for (int i = 1; i < iK; i++)
        {
            // TODO:
            b[i] = dACoef[i];
            b[iN-i] = -dACoef[i];
            // b[i] = iN * rValues[i] - dACoef[0] - dACoef[iN-i];
        }
        
        gsl_fft_real_transform(b, 1, iN, real, work);

        // double real[iK];
        // real[0] = dAcoef[0];
        // double complex[iK];

        // for (int i = 1; i < iK; i++) 
        // {
        //     real[i] = dACoef[i];
        //     // real[iN-i] = dACoef[i];
        //     complex[i] = dACoef[iN-i];
        //     // complex[iN-i] = -1. * dACoef[iN-i];
        // }
        // real[iK] = dACoef[iK];
        // complex[iK] = 0;
    
        rValues = std::valarray(b, iN);
    }

private:
    double m_dH;
    // int m_iStep;
};

cfl::GaussRollback prb::fft2()
{
    return cfl::GaussRollback(new FFT2());
}
