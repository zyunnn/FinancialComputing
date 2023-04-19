#include "home6/home6.hpp"

using namespace cfl;
using namespace std;

class Chain : public IGaussRollback
{
public:
    Chain(unsigned iExplSteps, const cfl::GaussRollback &rFast, unsigned iImplSteps, double dExplP, double dImplP)
        : m_fast(rFast), m_iEXplSteps(iExplSteps), m_iImplSteps(iImplSteps), m_dExplP(dExplP), m_dImplP(dImplP)
    { }

    Chain(const cfl::GaussRollback &rFast, unsigned iEXplSteps, unsigned iImplSteps, double dExplP, double dImplP, 
          unsigned iSize, double dH, double dVar) 
        : Chain(iEXplSteps, rFast, iImplSteps, dExplP, dImplP)
    {
        double dTe = 2 * pow(dH, 2) * dExplP * iEXplSteps;
        double dTi = 2 * pow(dH, 2) * dImplP * iImplSteps;
        
        m_expl = prb::expl(dExplP);
        if (dVar > dTe + dTi) 
        {
            m_bFirst = true;
            m_expl.assign(iSize, dH, dTe);
            m_fast.assign(iSize, dH, dVar - (dTe + dTi));
            m_impl = prb::impl(dImplP);
            m_impl.assign(iSize, dH, dTi);
        } 
        else 
        {
            m_expl.assign(iSize, dH, dVar);
        }
    }

    IGaussRollback *newObject(unsigned iSize, double dH, double dVar) const
    {
        return new Chain(m_fast, m_iEXplSteps, m_iImplSteps, m_dExplP, m_dImplP, iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
        m_expl.rollback(rValues);
        if (m_bFirst) 
        {
            m_fast.rollback(rValues);
            m_impl.rollback(rValues);
        }
    }

private:
    cfl::GaussRollback m_expl, m_fast, m_impl;
    unsigned m_iEXplSteps, m_iImplSteps;
    double m_dExplP, m_dImplP;
    bool m_bFirst = false;
};


cfl::GaussRollback prb::chain(unsigned iExplSteps, 
                              const cfl::GaussRollback &rFast, 
                              unsigned iImplSteps,
                              double dExplP, 
                              double dImplP)
{
    return cfl::GaussRollback(new Chain(iExplSteps, rFast, iImplSteps, dExplP, dImplP));
}

