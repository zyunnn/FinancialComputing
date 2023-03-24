#include "home2/home2.hpp"

using namespace cfl;
using namespace std;
#include <gsl/gsl_errno.h>
#include <gsl/gsl_roots.h>

namespace cflRoot 
{   
    double value(double dX, void *pF)
    {
        const std::vector<Function> &rF = *(const std::vector<Function> *)pF;
        ASSERT(rF.front().belongs(dX));
        return rF.front()(dX);
    } 

    class GSL_FSolver : public IRoot
    {
    public:
        GSL_FSolver(double dAbsErr, double dRelErr, unsigned iMaxSteps, const gsl_root_fsolver_type *pT)
        {
            m_dAbsErr = dAbsErr;
            m_dRelErr = dRelErr;
            m_iMaxSteps = iMaxSteps;
            m_bFErr = false;
            m_pT = pT;
        } 
        
        GSL_FSolver(double dFuncErr, unsigned iMaxSteps, const gsl_root_fsolver_type *pT) 
        {
            m_dFErr = dFuncErr;
            m_iMaxSteps = iMaxSteps;
            m_bFErr = true;
            m_pT = pT;
        }

        double find(const cfl::Function &rF, double dL, double dR) const
        {
            gsl_function uF;
            std::vector<Function> uG = {rF};
            uF.function = &value;
            uF.params = &uG;

            std::unique_ptr<gsl_root_fsolver, decltype(&gsl_root_fsolver_free)>
                uSolver(gsl_root_fsolver_alloc(m_pT), &gsl_root_fsolver_free);

            gsl_root_fsolver_set(uSolver.get(), &uF, dL, dR);
            int iStatus = GSL_CONTINUE;
            double dLo = dL, dHi = dR;
            double dRoot = 0;
            unsigned iSteps = 0;
            if (m_bFErr)
            {
                double dY;
                while ((iStatus == GSL_CONTINUE) && (iSteps < m_iMaxSteps))
                {
                    iSteps++;
                    gsl_root_fsolver_iterate(uSolver.get());
                    dRoot = gsl_root_fsolver_root(uSolver.get());
                    dLo = gsl_root_fsolver_x_lower(uSolver.get());
                    dHi = gsl_root_fsolver_x_upper(uSolver.get());
                    dY = GSL_FN_EVAL(&uF, dRoot);
                    iStatus = gsl_root_test_residual(dY, m_dFErr);
                }
            }
            else
            {
                ASSERT(m_bFErr == false);
                while ((iStatus == GSL_CONTINUE) && (iSteps < m_iMaxSteps))
                {
                    iSteps++;
                    gsl_root_fsolver_iterate(uSolver.get());
                    dRoot = gsl_root_fsolver_root(uSolver.get());
                    dLo = gsl_root_fsolver_x_lower(uSolver.get());
                    dHi = gsl_root_fsolver_x_upper(uSolver.get());
                    iStatus = gsl_root_test_interval(dLo, dHi, m_dAbsErr, m_dRelErr);
                }
            }
            return dRoot;
        }

    private:
        double m_dAbsErr, m_dRelErr, m_dFErr;
        unsigned m_iMaxSteps;
        bool m_bFErr;
        const gsl_root_fsolver_type *m_pT;
    };
}

using namespace cflRoot;

cfl::Root prb::bisection(double dFuncErr, unsigned iMaxSteps)
{
    return cfl::Root(new GSL_FSolver(dFuncErr, iMaxSteps, gsl_root_fsolver_bisection));
};

cfl::Root prb::bisection(double dAbsErr, double dRelErr, unsigned iMaxSteps) 
{
    return cfl::Root(new GSL_FSolver(dAbsErr, dRelErr, iMaxSteps, gsl_root_fsolver_bisection));
};

cfl::Root prb::falsepos(double dAbsErr, double dRelErr, unsigned iMaxSteps)
{
    return cfl::Root(new GSL_FSolver(dAbsErr, dRelErr, iMaxSteps, gsl_root_fsolver_falsepos));
};

cfl::Root prb::falsepos(double dFuncErr, unsigned iMaxSteps)
{
    return cfl::Root(new GSL_FSolver(dFuncErr, iMaxSteps, gsl_root_fsolver_falsepos));
};

cfl::Root prb::brent(double dAbsErr, double dRelErr, unsigned iMaxSteps)
{
    return cfl::Root(new GSL_FSolver(dAbsErr, dRelErr, iMaxSteps, gsl_root_fsolver_brent));
};

cfl::Root prb::brent(double dFuncErr, unsigned iMaxSteps) 
{
    return cfl::Root(new GSL_FSolver(dFuncErr, iMaxSteps, gsl_root_fsolver_brent));
}



