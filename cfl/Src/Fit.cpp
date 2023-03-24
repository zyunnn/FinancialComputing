#include "cfl/Fit.hpp"
#include "cfl/Error.hpp"
#include <gsl/gsl_fit.h>
#include <gsl/gsl_blas.h>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace cfl;
using namespace std;

// class Fit

cfl::Fit::Fit(IFit *pNewP) : m_uP(pNewP) {}

// class OneDimFit

class OneDimFit : public IFit
{
public:
  OneDimFit(const Function &rBaseF, const Function rFreeF)
      : m_uBaseF(rBaseF), m_uFreeF(rFreeF) {}

  OneDimFit(const Function &rBaseF, const Function rFreeF,
            const std::vector<double> &rArg,
            const std::vector<double> &rVal,
            const std::vector<double> &rWt, bool bChi2)
      : OneDimFit(rBaseF, rFreeF)
  {
    PRECONDITION(std::all_of(rArg.begin(), rArg.end(), [&rBaseF](double dX)
                             { return rBaseF.belongs(dX); }));
    PRECONDITION(std::all_of(rWt.begin(), rWt.end(), [](double dW)
                             { return dW > 0; }));
    PRECONDITION((rArg.size() == rVal.size()) && (rArg.size() == rWt.size()));
    PRECONDITION(rArg.size() > 1);

    std::vector<double> uX(rArg.size());
    std::transform(rArg.begin(), rArg.end(), uX.begin(),
                   [&rBaseF](double dT)
                   { return rBaseF(dT); });

    std::vector<double> uY(rArg.size());
    std::transform(rArg.begin(), rArg.end(), rVal.begin(), uY.begin(),
                   [&rFreeF](double dX, double dY)
                   {
                     return dY - rFreeF(dX);
                   });

    gsl_fit_wmul(uX.data(), 1, rWt.data(), 1, uY.data(),
		 1, rArg.size(), &m_dC, &m_dVar, &m_dChi2);

    if (bChi2)
    {
      double dVar = m_dChi2 / (rArg.size() - 1);
      m_dVar *= dVar;
    }
  }

  IFit *
  newObject(const std::vector<double> &rArg, const std::vector<double> &rVal,
            const std::vector<double> &rWt, bool bChi2) const
  {
    return new OneDimFit(m_uBaseF, m_uFreeF, rArg, rVal, rWt, bChi2);
  }

  Function fit() const
  {
    return m_dC * m_uBaseF + m_uFreeF;
  }

  Function err() const
  {
    return sqrt(m_dVar * m_uBaseF * m_uBaseF);
  }

  FitParam param() const
  {
    FitParam uParam;
    uParam.fit = std::valarray<double>(m_dC, 1);
    uParam.cov = std::valarray<double>(m_dVar, 1);
    uParam.chi2 = m_dChi2;
    return uParam;
  }

private:
  Function m_uBaseF, m_uFreeF;
  double m_dC, m_dVar, m_dChi2;
};

// linear one-dim

cfl::Fit cfl::NFit::linear(const cfl::Function &rBaseF, const cfl::Function &rFreeF)
{
  return Fit(new OneDimFit(rBaseF, rFreeF));
}

// class Regression

class Regression : public IFit
{
public:
  Regression(const Function &rBaseF, const Function rFreeF)
      : m_uBaseF(rBaseF), m_uFreeF(rFreeF) {}

  Regression(const Function &rBaseF, const Function rFreeF,
             const std::vector<double> &rArg,
             const std::vector<double> &rVal,
             const std::vector<double> &rWt, bool bChi2)
      : Regression(rBaseF, rFreeF)
  {
    PRECONDITION(std::all_of(rArg.begin(), rArg.end(), [&rBaseF](double dX)
                             { return rBaseF.belongs(dX); }));
    PRECONDITION(std::all_of(rWt.begin(), rWt.end(), [](double dW)
                             { return dW > 0; }));
    PRECONDITION((rArg.size() == rVal.size()) && (rArg.size() == rWt.size()));
    PRECONDITION(rArg.size() > 1);

    std::vector<double> uX(rArg.size());
    std::transform(rArg.begin(), rArg.end(), uX.begin(),
                   [&rBaseF](double dT)
                   { return rBaseF(dT); });

    std::vector<double> uY(rArg.size());
    std::transform(rArg.begin(), rArg.end(), rVal.begin(), uY.begin(),
                   [&rFreeF](double dX, double dY)
                   {
                     return dY - rFreeF(dX);
                   });

    m_uParam.fit.resize(2);
    m_uParam.cov.resize(4);

    double *pC0 = &m_uParam.fit[0];
    double *pC1 = &m_uParam.fit[1];
    double *pCov00 = &m_uParam.cov[0];
    double *pCov01 = &m_uParam.cov[1];
    double *pCov11 = &m_uParam.cov[3];
    double *pChi2 = &m_uParam.chi2;

    gsl_fit_wlinear(uX.data(), 1, rWt.data(), 1, uY.data(), 1, rArg.size(),
                    pC0, pC1, pCov00, pCov01, pCov11, pChi2);

    m_uParam.cov[2] = m_uParam.cov[1];

    if (bChi2)
    {
      double dVar = m_uParam.chi2 / (rArg.size() - 2.);
      m_uParam.cov *= dVar;
    }
  }

  IFit *
  newObject(const std::vector<double> &rArg, const std::vector<double> &rVal,
            const std::vector<double> &rWt, bool bChi2) const
  {
    return new Regression(m_uBaseF, m_uFreeF, rArg, rVal, rWt, bChi2);
  }

  Function fit() const
  {
    return m_uParam.fit[0] + m_uParam.fit[1] * m_uBaseF + m_uFreeF;
  }

  Function err() const
  {
    std::function<double(double)> uErr =
        [uBase = m_uBaseF, uCov = m_uParam.cov](double dX)
    {
      std::vector<double> uV(2);
      uV.front() = 1.;
      uV.back() = uBase(dX);

      std::vector<double> uU(uV);
      gsl_vector_const_view uUView = gsl_vector_const_view_array(uU.data(), uU.size());
      gsl_vector_view uVView = gsl_vector_view_array(uV.data(), uV.size());
      gsl_matrix_const_view uCovView = gsl_matrix_const_view_array(&uCov[0], 2, 2);
      gsl_blas_dsymv(CblasUpper, 1., &uCovView.matrix, &uUView.vector, 0., &uVView.vector);
      gsl_blas_ddot(&uUView.vector, &uVView.vector, &dX);

      ASSERT(dX >= 0);

      return std::sqrt(dX);
    };
    return Function(uErr,
                    [uBase = m_uBaseF, uG = m_uFreeF](double dX)
                    {
                      return uBase.belongs(dX) && uG.belongs(dX);
                    });
  }

  FitParam param() const
  {
    return m_uParam;
  }

private:
  Function m_uBaseF, m_uFreeF;
  FitParam m_uParam;
};

// linear regression

cfl::Fit cfl::NFit::linear_regression(const cfl::Function &rBaseF,
				      const cfl::Function &rFreeF)
{
  return Fit(new Regression(rBaseF, rFreeF));
}
