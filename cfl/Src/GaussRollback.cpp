#include "cfl/GaussRollback.hpp"
#include "cfl/Error.hpp"
#include <functional>

using namespace cfl;
using namespace std;

// class GaussRollback

cfl::GaussRollback::GaussRollback(IGaussRollback *pNewP)
    : m_uP(pNewP) {}

std::valarray<double> state(unsigned iSize, double dH)
{
  std::valarray<double> uState(iSize);
  uState[0] = -((iSize - 1) * dH) / 2.;
  std::transform(begin(uState), end(uState) - 1, begin(uState) + 1,
                 [dH](double dX)
                 { return dX + dH; });
  return uState;
}

void cfl::GaussRollback::rollback(std::valarray<double> &rValues,
                                  std::valarray<double> &rDelta) const
{
  PRECONDITION(m_dVar > cfl::EPS);
  std::valarray<double> uState = state(m_iSize, m_dH);
  rDelta = rValues * uState;
  rollback(rValues);
  rollback(rDelta);
  rDelta -= (rValues * uState);
  rDelta /= m_dVar;
}

void cfl::GaussRollback::rollback(std::valarray<double> &rValues,
                                  std::valarray<double> &rDelta,
                                  std::valarray<double> &rGamma) const
{
  PRECONDITION(m_dVar > cfl::EPS);
  std::valarray<double> uState = state(m_iSize, m_dH);
  std::valarray<double> uState2 = uState * uState;
  rDelta = rValues * uState;
  rGamma = rValues * uState2;
  rollback(rValues);
  rollback(rDelta);
  rollback(rGamma);
  rGamma += (-2. * uState * rDelta + uState2 * rValues);
  rGamma /= m_dVar;
  rGamma -= rValues;
  rGamma /= m_dVar;
  rDelta -= (rValues * uState);
  rDelta /= m_dVar;
}

void cfl::GaussRollback::assign(unsigned iSize, double dH, double dVar)
{
  m_uP.reset(m_uP->newObject(iSize, dH, dVar));
  m_dH = dH;
  m_iSize = iSize;
  m_dVar = dVar;
}

void cfl::GaussRollback::vega(std::valarray<double> &rGamma) const
{
  rGamma *= std::sqrt(m_dVar);
}
