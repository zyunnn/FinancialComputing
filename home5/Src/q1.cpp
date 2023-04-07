#include "home5/home5.hpp"
#include <gsl/gsl_bspline.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_blas.h>

using namespace cfl;
using namespace std;

typedef std::unique_ptr<gsl_vector, decltype(&gsl_vector_free)> gvector_; 
typedef std::unique_ptr<gsl_matrix, decltype(&gsl_matrix_free)> gmatrix_; 
typedef std::unique_ptr<gsl_bspline_workspace, decltype(&gsl_bspline_free)> gSplineWork_;
typedef std::unique_ptr<gsl_multifit_linear_workspace, decltype(&gsl_multifit_linear_free)> gLinearWork_;

class LSSplineFit : public IFit 
{
public:
    LSSplineFit(unsigned iOrder, double dL, double dR, unsigned iBreakpoints, bool bUniform)
            : m_iOrder(iOrder), m_iBreakpoints(iBreakpoints), m_dL(dL), m_dR(dR), m_bUniform(bUniform) {}

    LSSplineFit(unsigned iOrder,  const std::vector<double> &rBreakpoints) 
            : m_iOrder(iOrder), m_uBreakpoints(rBreakpoints) {}

    LSSplineFit(unsigned iOrder, const std::vector<double> &rBreakpoints, 
                double dL, double dR, unsigned iBreakpoints,
                const std::vector<double> &rArg,
                const std::vector<double> &rVal,
                const std::vector<double> &rWt, bool bChi2, bool bUniform)
            : LSSplineFit(iOrder, dL, dR, iBreakpoints, bUniform)
    {
        PRECONDITION((rArg.size() == rVal.size()) && (rArg.size() == rWt.size()));
        PRECONDITION(rArg.size() > 1);

        int iL = m_bUniform ? iBreakpoints : rBreakpoints.size();     
        int iM = iL + m_iOrder - 2;         // number of coefficients
        int iN = rArg.size();               // number of observations

        // Solvers
        uSplineWork.reset(gsl_bspline_alloc(m_iOrder, iL));
        gLinearWork_ uLinearWork(gsl_multifit_linear_alloc(iN, iM), &gsl_multifit_linear_free);
        
        // Construct gsl data
        gvector_ uW(gsl_vector_alloc(iN), &gsl_vector_free);
        std::copy(rWt.begin(), rWt.end(), gsl_vector_ptr(uW.get(), 0));

        gvector_ uY(gsl_vector_alloc(iN), &gsl_vector_free);
        std::copy(rVal.begin(), rVal.end(), gsl_vector_ptr(uY.get(), 0));

        gvector_ uB(gsl_vector_alloc(iL), &gsl_vector_free);            // extract knots
        gmatrix_ uX(gsl_matrix_alloc(iN, iM), &gsl_matrix_free);
        uC.reset(gsl_vector_alloc(iM));
        uCov.reset(gsl_matrix_alloc(iM, iM));

        // B-spline knots
        if (m_bUniform) {
            gsl_bspline_knots_uniform(m_dL, m_dR, uSplineWork.get());
        } else {
            gvector_ uBreak(gsl_vector_alloc(iM), &gsl_vector_free);
            std::copy(rBreakpoints.begin(), rBreakpoints.end(), gsl_vector_ptr(uBreak.get(), 0));
            gsl_bspline_knots(uBreak.get(), uSplineWork.get());
        }      

        for (int i = 0; i < iN; i++)
        {
            gsl_bspline_eval(rArg[i], uB.get(), uSplineWork.get());
            for (int j = 0; j < iM; j++)
            {
                double dBj = gsl_vector_get(uB.get(), j);
                gsl_matrix_set(uX.get(), i, j, dBj);
            }
        }

        // Least-squares fit
        double *pChi2 = &m_uParam.chi2;

        gsl_multifit_wlinear(uX.get(), uW.get(), uY.get(), uC.get(), uCov.get(), pChi2, uLinearWork.get());

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
        return new LSSplineFit(m_iOrder, m_uBreakpoints, m_dL, m_dR, m_iBreakpoints, 
                               rArg, rVal, rWt, bChi2, m_bUniform);
    }

    FitParam param() const
    {
        return m_uParam;
    }

    Function fit() const
    {
        std::function<double(double)> uFit = [this](double dX) 
        {
            double dY = 0., dYerr;
            int iM = gsl_bspline_ncoeffs(uSplineWork.get());    
            int iL = iM + 2 - m_iOrder;                         // number of breakpoints
            gvector_ uBTmp(gsl_vector_alloc(iL), &gsl_vector_free); 
            gsl_bspline_eval(dX, uBTmp.get(), uSplineWork.get());            
            gsl_multifit_linear_est(uBTmp.get(), uC.get(), uCov.get(), &dY, &dYerr);
            return dY;
        };
        return Function(uFit);
    }

    Function err() const
    {
        std::function<double(double)> uErr = [this](double dX)
        {
            int iM = gsl_bspline_ncoeffs(uSplineWork.get());    
            int iL = iM + 2 - m_iOrder; 

            std::vector<double> uV(iM, 1);
            
            gvector_ uBTmp(gsl_vector_alloc(iL), &gsl_vector_free); 
            gsl_bspline_eval(dX, uBTmp.get(), uSplineWork.get()); 
            for (int j = 0; j < iM; j++)
            {
                double dBj = gsl_vector_get(uBTmp.get(), j);
                uV[j] = dBj;
            }
            std::vector<double> uU(uV);

            gsl_vector_const_view uUView = gsl_vector_const_view_array(uU.data(), uU.size());
            gsl_vector_view uVView = gsl_vector_view_array(uV.data(), uV.size());
            gsl_matrix_const_view uCovView = gsl_matrix_const_view_array(&m_uParam.cov[0], iM, iM);
            gsl_blas_dsymv(CblasUpper, 1., &uCovView.matrix, &uUView.vector, 0., &uVView.vector);
            gsl_blas_ddot(&uUView.vector, &uVView.vector, &dX);
            return std::sqrt(dX);
        };
        return Function(uErr);
    }

private:
    unsigned m_iOrder, m_iBreakpoints;
    const std::vector<double> m_uBreakpoints;
    double m_dL, m_dR;
    bool m_bUniform = false;
    FitParam m_uParam;

    // GSL parameter
    gSplineWork_ uSplineWork {gsl_bspline_alloc(2,2), &gsl_bspline_free};
    gvector_ uC {gsl_vector_alloc(1), &gsl_vector_free};
    gmatrix_ uCov {gsl_matrix_alloc(1,1), &gsl_matrix_free};
};



cfl::Fit prb::bspline(unsigned iOrder, const std::vector<double> &rBreakpoints)
{
    return Fit(new LSSplineFit(iOrder, rBreakpoints));
}

cfl::Fit prb::bspline(unsigned iOrder, double dL, double dR, unsigned iBreakpoints)
{
    return Fit(new LSSplineFit(iOrder, dL, dR, iBreakpoints, true));
}