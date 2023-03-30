#include "home4/home4.hpp"
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_blas.h>

using namespace cfl;
using namespace std;
#include <iostream>

class LeastSquareFit : public IFit 
{
public:
    LeastSquareFit(const std::vector<cfl::Function> &rBasisF, const cfl::Function &rFreeF) 
            : m_uBasisF(rBasisF), m_uFreeF(rFreeF) {}

    LeastSquareFit(const std::vector<cfl::Function> &rBasisF, const cfl::Function &rFreeF,
                   const std::vector<double> &rArg,
                   const std::vector<double> &rVal,
                   const std::vector<double> &rWt, bool bChi2) 
            : LeastSquareFit(rBasisF, rFreeF)
    {
        int iN = rArg.size();       // number of observations
        int iM = rBasisF.size();    // number of coefficients

        std::unique_ptr<gsl_matrix, decltype(&gsl_matrix_free)>
            uX(gsl_matrix_alloc(iN, iM), &gsl_matrix_free);
        for (int j = 0; j < iM; j++) 
        {
            Function uF = rBasisF[j];
            for (int i = 0; i < iN; i++) 
            {
                gsl_matrix_set(uX.get(), i, j, uF(rArg[i]));
            }
        }
        
        std::unique_ptr<gsl_vector, decltype(&gsl_vector_free)>
            uW(gsl_vector_alloc(iN), &gsl_vector_free);
        std::copy(rWt.begin(), rWt.end(), gsl_vector_ptr(uW.get(), 0));
        
        std::unique_ptr<gsl_vector, decltype(&gsl_vector_free)>
            uY(gsl_vector_alloc(iN), &gsl_vector_free);
        std::transform(rVal.begin(), rVal.end(), rArg.begin(), gsl_vector_ptr(uY.get(), 0), 
                       [&rFreeF](double dVal, double dArg) 
                       { return dVal - rFreeF(dArg); });
        
        std::unique_ptr<gsl_vector, decltype(&gsl_vector_free)>
            uC(gsl_vector_alloc(iM), &gsl_vector_free);
        
        std::unique_ptr<gsl_matrix, decltype(&gsl_matrix_free)>
            uCov(gsl_matrix_alloc(iM, iM), &gsl_matrix_free);

        std::unique_ptr<gsl_multifit_linear_workspace, decltype(&gsl_multifit_linear_free)> 
            uWork(gsl_multifit_linear_alloc(iN, iM), &gsl_multifit_linear_free);

        // m_uParam.fit.resize(iM);
        // m_uParam.cov.resize(iM*iM);

        double *pChi2 = &m_uParam.chi2;

        gsl_multifit_wlinear(uX.get(), uW.get(), uY.get(), 
                             uC.get(), uCov.get(), pChi2, uWork.get());

        std::valarray<double> uFitParam (gsl_vector_const_ptr(uC.get(), 0), iM);
        std::valarray<double> uCovParam (gsl_matrix_const_ptr(uCov.get(), 0, 0), iM*iM);
        m_uParam.fit = uFitParam;
        m_uParam.cov = uCovParam;

        if (bChi2) 
        {
            double dVar = m_uParam.chi2 / (iN - iM);
            m_uParam.cov *= dVar;
        }
    }

    IFit *newObject(const std::vector<double> &rArg, const std::vector<double> &rVal,
                    const std::vector<double> &rWt, bool bChi2) const
    {
        return new LeastSquareFit(m_uBasisF, m_uFreeF, rArg, rVal, rWt, bChi2);
    }

    FitParam param() const
    {
        return m_uParam;
    }

    Function fit() const
    {
        Function uF = m_uFreeF;
        for (int i = 0; i < m_uBasisF.size(); i++) 
        {
            uF += m_uParam.fit[i] * m_uBasisF[i];
        }
        return uF;
    }

    Function err() const
    {
        // TODO:
        return sqrt(m_uFreeF);
    }

private:
    std::vector<cfl::Function> m_uBasisF;
    Function m_uFreeF;
    // std::vector<double> m_dVal, m_dArg;
    FitParam m_uParam;
};

cfl::Fit prb::linear(const std::vector<cfl::Function> &rBasisF,
                     const cfl::Function &rFreeF)
{
    return Fit(new LeastSquareFit(rBasisF, rFreeF));
}