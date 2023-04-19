#include "home6/home6.hpp"
#include <gsl/gsl_linalg.h>
#include <vector>

using namespace cfl;
using namespace std;


class CrankNicolson : public IGaussRollback
{
public:
    CrankNicolson(double dR, unsigned iSize = 0) 
        : m_dR(dR), m_iSize(iSize) {}

    CrankNicolson(double dR, unsigned iSize, double dH, double dVar) 
        : CrankNicolson(dR, iSize)
    {
        m_iStep = std::ceil(dVar / (dH * dR));
        m_dQ = dVar / (2 * pow(dH, 2) * m_iStep);
    }

    IGaussRollback *newObject(unsigned iSize, double dH, double dVar) const
    {
        return new CrankNicolson(m_dR, iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
        vector<double> uGrid(begin(rValues), end(rValues));

        // Build tridiagonal matrix (positive definite)
        std::valarray<double> dCoef{-m_dQ / 2, 1 + m_dQ, -m_dQ / 2};        // Coef: (-q/2, q+1, -q/2)
        vector<vector<double>> uTridiag(m_iSize, vector<double>(m_iSize));
        uTridiag.front().front() = 1.;
        uTridiag.back().back() = 1.;
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
            // Build B matrix to solve Ax=B
            vector<double> uB(m_iSize);
            uB.front() = (m_dQ / 2 + 1) * uGrid[0] - m_dQ * uGrid[1] + 
                          m_dQ / 2 * uGrid[2];
            uB.back() = m_dQ / 2 * uGrid[m_iSize-3] - m_dQ * uGrid[m_iSize-2] + 
                       (m_dQ / 2 + 1) * uGrid[m_iSize-1];
            for(int i = 1; i < m_iSize-1; i++) 
            {
                uB[i] = m_dQ / 2 * uGrid[i-1] + (1 - m_dQ) * uGrid[i] + 
                        m_dQ / 2 * uGrid[i+1];
            }
            gsl_vector_view uBView = gsl_vector_view_array(&uB[0], m_iSize);
            unique_ptr<gsl_vector, decltype(&gsl_vector_free)> uX(gsl_vector_alloc(m_iSize), &gsl_vector_free);
            gsl_linalg_solve_tridiag(&uDiagView.vector, &uEView.vector, &uFView.vector, &uBView.vector, uX.get());
            uGrid.assign(gsl_vector_ptr(uX.get(), 0), gsl_vector_ptr(uX.get(), m_iSize-1));
        }
        rValues = std::valarray<double>(uGrid.data(), m_iSize);
    }

private:
    double m_dR, m_dQ;
    unsigned m_iSize;
    int m_iStep;
};


cfl::GaussRollback prb::crankNicolson(double dR)
{
    PRECONDITION(dR > 0);
    return cfl::GaussRollback(new CrankNicolson(dR));
}
