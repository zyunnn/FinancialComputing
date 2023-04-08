#include "home6/home6.hpp"
#include <gsl/gsl_linalg.h>
#include <vector>

using namespace cfl;
using namespace std;



class CrankNicolson : public IGaussRollback
{
public:
    CrankNicolson(double dR) : m_dR(dR) {}

    CrankNicolson(double dR, unsigned iSize, double dH, double dVar) 
        : CrankNicolson(dR)
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
        int iN = rValues.size();
        vector<vector<double>> uGrid(m_iStep+1, vector<double>(iN));
        uGrid[0].assign(begin(rValues), end(rValues));

        gsl_vector_view uAView = gsl_vector_view_array(uGrid[0].data(), iN);
        gsl_vector_view uXView = gsl_vector_view_array(uGrid[0].data(), iN);
        gsl_vector_view uBView = gsl_vector_view_array(uGrid[0].data(), iN);
        rValues = std::valarray<double>(uGrid[m_iStep].data(), iN);
        // gsl_linalg_solve_tridiag(&uDiagView.vector, &uEView.vector, &uFView.vector, &uBView.vector, uX.get());
    }

private:
    double m_dR, m_dQ;
    int m_iStep;
};


cfl::GaussRollback prb::crankNicolson(double dR)
{
    PRECONDITION(dR > 0);
    return cfl::GaussRollback(new CrankNicolson(dR));
}
