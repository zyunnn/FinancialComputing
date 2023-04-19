#include "home6/home6.hpp"
#include <gsl/gsl_linalg.h>
#include <vector>

using namespace cfl;
using namespace std;


class Implicit : public IGaussRollback
{
public:
    Implicit(double dP, unsigned iSize = 0) : m_dP(dP), m_iSize(iSize) {}

    Implicit(double dP, unsigned iSize, double dH, double dVar) 
        : Implicit(dP, iSize)
    {
        m_iStep = std::ceil(dVar / (2 * pow(dH, 2) * dP));
        m_dQ = dVar / (2 * pow(dH, 2) * m_iStep);
    }

    IGaussRollback *newObject(unsigned iSize, double dH, double dVar) const
    {
        return new Implicit(m_dP, iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
        vector<double> uGrid(begin(rValues), end(rValues));

        // Build tridiagonal matrix (positive definite)
        std::valarray<double> dCoef{-m_dQ, (1 + 2 * m_dQ), -m_dQ};        // Coef: (-q, (2q+1), -q)
        vector<vector<double>> uTridiag(m_iSize, vector<double>(m_iSize));
        uTridiag[0][0] = 1.;
        uTridiag[m_iSize-1][m_iSize-1] = 1.;
        for (int i = 1; i < m_iSize-1; i++)
        {
            std::copy(begin(dCoef), end(dCoef), uTridiag[i].begin() + i - 1);
        }

        // Extract super-diagonal & sub-diagonal vector
        std::valarray<double> uDiag(m_iSize), uOffDiag(m_iSize-1);
        uDiag[0] = uTridiag[0][0];
        for (int i = 1; i < m_iSize; i++) {
            uDiag[i] = uTridiag[i][i];
            uOffDiag[i-1] = uTridiag[i-1][i];
        }
        gsl_vector_view uDiagView = gsl_vector_view_array(&uDiag[0], m_iSize);
        gsl_vector_view uEView = gsl_vector_view_array(&uOffDiag[0], m_iSize-1);
        gsl_vector_view uFView = gsl_vector_view_array(&uOffDiag[0], m_iSize-1);

        // Start recursion
        for (int m = 0; m < m_iStep; m++)
        {
            gsl_vector_view uBView = gsl_vector_view_array(&uGrid[0], m_iSize);
            unique_ptr<gsl_vector, decltype(&gsl_vector_free)> uX(gsl_vector_alloc(m_iSize), &gsl_vector_free);
            gsl_linalg_solve_tridiag(&uDiagView.vector, &uEView.vector, &uFView.vector, &uBView.vector, uX.get());
            uGrid.assign(gsl_vector_ptr(uX.get(), 0), gsl_vector_ptr(uX.get(), m_iSize-1));
        }
        rValues = std::valarray<double>(uGrid.data(), m_iSize);
    }

private:
    double m_dP, m_dQ;
    unsigned m_iSize;
    int m_iStep;
};


cfl::GaussRollback prb::impl(double dP)
{
    PRECONDITION(dP > 0);
    return cfl::GaussRollback(new Implicit(dP));
}
