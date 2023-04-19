#include "home6/home6.hpp"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_halfcomplex.h>

using namespace cfl;
using namespace std;


typedef std::unique_ptr<gsl_fft_halfcomplex_wavetable, decltype(&gsl_fft_halfcomplex_wavetable_free)> ghctable_; 
typedef std::unique_ptr<gsl_fft_real_workspace, decltype(&gsl_fft_real_workspace_free)> grealwork_;
typedef std::unique_ptr<gsl_fft_real_wavetable, decltype(&gsl_fft_real_wavetable_free)> grealtable_;


class FFT : public IGaussRollback
{
public:
    FFT() {}

    FFT(unsigned iSize, double dH, double dVar) : m_dH(dH), m_dVar(dVar), m_iSize(iSize) {}

    IGaussRollback *newObject(unsigned iSize, double dH, double dVar) const
    {
        return new FFT(iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
        double dA[m_iSize];
        std::copy(begin(rValues), end(rValues), dA);

        ghctable_ hc(gsl_fft_halfcomplex_wavetable_alloc(m_iSize), &gsl_fft_halfcomplex_wavetable_free);
        grealwork_ work (gsl_fft_real_workspace_alloc(m_iSize), &gsl_fft_real_workspace_free);
        grealtable_ real (gsl_fft_real_wavetable_alloc(m_iSize), &gsl_fft_real_wavetable_free);

        gsl_fft_real_transform(dA, 1, m_iSize, real.get(), work.get());

        for (int k = 1; k <= m_iSize/2; k++) 
        {
            double dMult = std::exp(-0.5 * pow(2. * M_PI * k / (m_iSize * m_dH), 2) * m_dVar);
            dA[2 * k - 1] *= dMult;
            dA[2 * k] *= 2 * k < m_iSize ? dMult : 1.;
        }

        gsl_fft_halfcomplex_inverse(dA, 1, m_iSize, hc.get(), work.get());
    
        rValues = std::valarray(dA, m_iSize);
    }

private:
    double m_dH, m_dVar;
    unsigned m_iSize;
};

cfl::GaussRollback prb::fft()
{
    return cfl::GaussRollback(new FFT());
}
