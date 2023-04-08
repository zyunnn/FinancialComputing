#include "home6/home6.hpp"
#include <gsl/gsl_linalg.h>
#include <vector>

using namespace cfl;
using namespace std;


class Implicit : public IGaussRollback
{
public:
    Implicit(double dP) : m_dP(dP) {}

    Implicit(double dP, unsigned iSize, double dH, double dVar) 
        : Implicit(dP)
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
        int iN = rValues.size();
        vector<vector<double>> uGrid(m_iStep+1, vector<double>(iN));
        uGrid[0].assign(begin(rValues), end(rValues));

        // Build tridiagonal matrix (positive definite)
        vector<double> dCoef{-m_dQ, (1 + 2 * m_dQ), -m_dQ};        // Coef: (-q, (2q+1), -q)
        vector<vector<double>> uTridiag(iN, vector<double>(iN));
        uTridiag.front().front() = 1.;
        uTridiag.back().back() = 1.;
        for (int i = 1; i < iN-1; i++)
        {
            std::copy(dCoef.begin(), dCoef.end(), uTridiag[i].begin() + i - 1);
        }

        // Extract super-diagonal & sub-diagonal vector
        vector<double> uDiag(iN), uOffDiag(iN-1);
        uDiag.front() = uTridiag[0][0];
        for (int i = 1; i < iN; i++) {
            uDiag[i] = uTridiag[i][i];
            uOffDiag[i-1] = uTridiag[i-1][i];
        }
        gsl_vector_view uDiagView = gsl_vector_view_array(&uDiag[0], iN);
        gsl_vector_view uEView = gsl_vector_view_array(&uOffDiag[0], iN-1);
        gsl_vector_view uFView = gsl_vector_view_array(&uOffDiag[0], iN-1);

        // Start recursion
        for (int m = 0; m < m_iStep; m++)
        {
            gsl_vector_view uBView = gsl_vector_view_array(&uGrid[m][0], iN);
            unique_ptr<gsl_vector, decltype(&gsl_vector_free)> uX(gsl_vector_alloc(iN), &gsl_vector_free);
            gsl_linalg_solve_tridiag(&uDiagView.vector, &uEView.vector, &uFView.vector, &uBView.vector, uX.get());
            uGrid[m+1].assign(gsl_vector_ptr(uX.get(), 0), gsl_vector_ptr(uX.get(), iN-1));
        }
        rValues = std::valarray<double>(uGrid[m_iStep].data(), iN);
    }

private:
    double m_dP, m_dQ;
    int m_iStep;
};


cfl::GaussRollback prb::impl(double dP)
{
    PRECONDITION(dP > 0);
    return cfl::GaussRollback(new Implicit(dP));
}
