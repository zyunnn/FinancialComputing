#include "home4/home4.hpp"
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_deriv.h>

using namespace cfl;
using namespace std;
#include <iostream>

typedef std::unique_ptr<gsl_vector, decltype(&gsl_vector_free)> gvector_; 
typedef std::unique_ptr<gsl_matrix, decltype(&gsl_matrix_free)> gmatrix_; 

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
        PRECONDITION((rArg.size() == rVal.size()) && (rArg.size() == rWt.size()));
        PRECONDITION(rArg.size() > 1);

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
        
        gvector_ uW(gsl_vector_alloc(iN), &gsl_vector_free);
        std::copy(rWt.begin(), rWt.end(), gsl_vector_ptr(uW.get(), 0));
        
        gvector_ uY(gsl_vector_alloc(iN), &gsl_vector_free);
        std::transform(rVal.begin(), rVal.end(), rArg.begin(), gsl_vector_ptr(uY.get(), 0), 
                       [&rFreeF](double dVal, double dArg) 
                       { return dVal - rFreeF(dArg); });
        
        gvector_ uC(gsl_vector_alloc(iM), &gsl_vector_free);
        gmatrix_ uCov(gsl_matrix_alloc(iM, iM), &gsl_matrix_free);

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
        std::function<double(double)> uErr = [uBasis = m_uBasisF, uCov = m_uParam.cov](double dX)
        {
            // std::cout << "dX:" << dX << std::endl;
            int iM = uBasis.size();
            std::vector<double> uV(iM);
            std::transform(uBasis.begin(), uBasis.end(), uV.begin(), [dX](Function uF){ return uF(dX); });

            std::vector<double> uU(uV);
            gsl_vector_const_view uUView = gsl_vector_const_view_array(uU.data(), uU.size());
            gsl_vector_view uVView = gsl_vector_view_array(uV.data(), uV.size());
            gsl_matrix_const_view uCovView = gsl_matrix_const_view_array(&uCov[0], iM, iM);
            gsl_blas_dsymv(CblasUpper, 1., &uCovView.matrix, &uUView.vector, 0., &uVView.vector);
            gsl_blas_ddot(&uUView.vector, &uVView.vector, &dX);

            // gsl_function F;
            // F.function = uBasis[0];
            // F.function()
            // gsl_deriv_central();

            // ASSERT(dX >= 0);

            return std::sqrt(dX);
        };
        return Function(uErr,
                        [uBasis = m_uBasisF, uG = m_uFreeF](double dX)
                        {
                            return uG.belongs(dX) && std::all_of(uBasis.begin(), uBasis.end(), 
                                        [&dX](Function uF) { return uF.belongs(dX); });
                        });
    }

private:
    std::vector<cfl::Function> m_uBasisF;
    Function m_uFreeF;
    FitParam m_uParam;
};

cfl::Fit prb::linear(const std::vector<cfl::Function> &rBasisF,
                     const cfl::Function &rFreeF)
{
    return Fit(new LeastSquareFit(rBasisF, rFreeF));
}