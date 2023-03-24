#include <cmath>
#include <limits>
#include "cfl/MultiFunction.hpp"
#include "cfl/Function.hpp"
#include "cfl/Error.hpp"

using namespace cfl;
using namespace std;

cfl::MultiFunction::MultiFunction(IMultiFunction *pNewF)
    : m_pF(pNewF)
{
}

namespace cflMultiFunction
{
  // CLASS: Adapter
  class Adapter : public cfl::IMultiFunction
  {
  public:
    Adapter(const std::function<double(const std::valarray<double> &)> &rF,
            const std::function<bool(const std::valarray<double> &)> &rB,
            unsigned iDim)
        : m_uF(rF), m_uB(rB), m_iDim(iDim) {}

    Adapter(const std::function<double(const std::valarray<double> &)> &rF, unsigned iDim)
        : Adapter(
              rF, [](const std::valarray<double> &rX)
              { return true; },
              iDim)
    {
    }

    Adapter(double dV, unsigned iDim)
        : Adapter([dV](const std::valarray<double> rX)
                  { return dV; },
                  iDim) {}

    double operator()(const std::valarray<double> &rX) const
    {
      PRECONDITION(belongs(rX));
      return m_uF(rX);
    }
    bool belongs(const std::valarray<double> &rX) const
    {
      PRECONDITION(rX.size() == m_iDim);
      return m_uB(rX);
    }
    unsigned dim() const
    {
      return m_iDim;
    }

  private:
    std::function<double(const std::valarray<double> &)> m_uF;
    std::function<bool(const std::valarray<double> &)> m_uB;
    unsigned m_iDim;
  };

  // CLASS: Composite

  class Composite : public IMultiFunction
  {
  public:
    Composite(const MultiFunction &rFunc, const std::function<double(double)> &rUnOp)
        : m_uFunc(rFunc), m_uUnOp(rUnOp)
    {
    }

    double operator()(const std::valarray<double> &rX) const
    {
      PRECONDITION(rX.size() == m_uFunc.dim());
      return m_uUnOp(m_uFunc(rX));
    }
    bool belongs(const std::valarray<double> &rX) const
    {
      PRECONDITION(rX.size() == m_uFunc.dim());
      return m_uFunc.belongs(rX);
    }
    unsigned dim() const
    {
      return m_uFunc.dim();
    }

  private:
    MultiFunction m_uFunc;
    std::function<double(double)> m_uUnOp;
  };

  // CLASS: BinComposite

  class BinComposite : public IMultiFunction
  {
  public:
    BinComposite(const MultiFunction &rFunc1,
                 const MultiFunction &rFunc2,
                 const std::function<double(double, double)> &rBinOp)
        : m_uFunc1(rFunc1), m_uFunc2(rFunc2), m_uBinOp(rBinOp)
    {
      POSTCONDITION(m_uFunc1.dim() == m_uFunc2.dim());
    }

    double operator()(const std::valarray<double> &rX) const
    {
      PRECONDITION(rX.size() == dim());
      return m_uBinOp(m_uFunc1(rX), m_uFunc2(rX));
    }

    bool belongs(const std::valarray<double> &rX) const
    {
      PRECONDITION(rX.size() == dim());
      return (m_uFunc1.belongs(rX)) && (m_uFunc2.belongs(rX));
    }

    unsigned dim() const
    {
      PRECONDITION(m_uFunc1.dim() == m_uFunc2.dim());
      return m_uFunc1.dim();
    }

  private:
    MultiFunction m_uFunc1;
    MultiFunction m_uFunc2;
    std::function<double(double, double)> m_uBinOp;
  };
} // namespace cflMultiFunction

// CLASS: MultiFunction

cfl::MultiFunction::MultiFunction(const std::function<double(const std::valarray<double> &)> &rF,
                                  const std::function<bool(const std::valarray<double> &)> &rB,
                                  unsigned iDim)
    : m_pF(new cflMultiFunction::Adapter(rF, rB, iDim)) {}

cfl::MultiFunction::MultiFunction(const std::function<double(const std::valarray<double> &)> &rF,
                                  unsigned iDim)
    : m_pF(new cflMultiFunction::Adapter(rF, iDim)) {}

cfl::MultiFunction::MultiFunction(double dV, unsigned iDim)
    : m_pF(new cflMultiFunction::Adapter(dV, iDim)) {}

MultiFunction &cfl::MultiFunction::operator=(double dV)
{
  m_pF.reset(new cflMultiFunction::Adapter(dV, dim()));
  return *this;
}

MultiFunction &cfl::MultiFunction::operator+=(const MultiFunction &rFunc)
{
  m_pF.reset(new cflMultiFunction::BinComposite(*this, rFunc, std::plus<double>()));
  return *this;
}

MultiFunction &cfl::MultiFunction::operator*=(const MultiFunction &rFunc)
{
  m_pF.reset(new cflMultiFunction::BinComposite(*this, rFunc, std::multiplies<double>()));
  return *this;
}

MultiFunction &cfl::MultiFunction::operator-=(const MultiFunction &rFunc)
{
  m_pF.reset(new cflMultiFunction::BinComposite(*this, rFunc, std::minus<double>()));
  return *this;
}

MultiFunction &cfl::MultiFunction::operator/=(const MultiFunction &rFunc)
{
  m_pF.reset(new cflMultiFunction::BinComposite(*this, rFunc, std::divides<double>()));
  return *this;
}

MultiFunction &cfl::MultiFunction::operator+=(double dX)
{
  m_pF.reset(new cflMultiFunction::Composite(*this, [dX](double dY)
                                             { return dY + dX; }));
  return *this;
}

MultiFunction &cfl::MultiFunction::operator-=(double dX)
{
  m_pF.reset(new cflMultiFunction::Composite(*this, [dX](double dY)
                                             { return dY - dX; }));
  return *this;
}

MultiFunction &cfl::MultiFunction::operator*=(double dX)
{
  m_pF.reset(new cflMultiFunction::Composite(*this, [dX](double dY)
                                             { return dY * dX; }));
  return *this;
}

MultiFunction &cfl::MultiFunction::operator/=(double dX)
{
  m_pF.reset(new cflMultiFunction::Composite(*this, [dX](double dY)
                                             { return dY / dX; }));
  return *this;
}

// GLOBAL FUNCTIONS

cfl::MultiFunction cfl::apply(const cfl::MultiFunction &rF, const std::function<double(double)> &rOp)
{
  return MultiFunction(new cflMultiFunction::Composite(rF, rOp));
}

cfl::MultiFunction cfl::apply(const cfl::MultiFunction &rF, const cfl::MultiFunction &rG,
                              const std::function<double(double, double)> &rOp)
{
  return MultiFunction(new cflMultiFunction::BinComposite(rF, rG, rOp));
}

namespace cflMultiFunction
{
  class Adapter2 : public IMultiFunction
  {
  public:
    Adapter2(const Function &rFunc, unsigned iArgIndex, unsigned iDim)
        : m_uFunc(rFunc), m_iArgIndex(iArgIndex), m_iDim(iDim)
    {
      POSTCONDITION(m_iArgIndex < m_iDim);
    }

    double operator()(const std::valarray<double> &rX) const
    {
      PRECONDITION(rX.size() == m_iDim);
      PRECONDITION(belongs(rX));
      return m_uFunc(rX[m_iArgIndex]);
    }
    bool belongs(const std::valarray<double> &rX) const
    {
      PRECONDITION(rX.size() == m_iDim);
      return m_uFunc.belongs(rX[m_iArgIndex]);
    }
    unsigned dim() const { return m_iDim; }

  private:
    Function m_uFunc;
    unsigned m_iArgIndex, m_iDim;
  };
} // namespace cflMultiFunction

MultiFunction cfl::toMultiFunction(const cfl::Function &rFunc, unsigned iArgIndex,
                                   unsigned iDim)
{
  return MultiFunction(new cflMultiFunction::Adapter2(rFunc, iArgIndex, iDim));
}

namespace cflMultiFunction
{
  std::valarray<double> extend(const std::valarray<double> &rX,
                               const std::valarray<double> &rPoint,
                               const std::vector<unsigned> &rState)
  {
    PRECONDITION(rX.size() == rState.size());
    std::valarray<double> uP(rX.size() + rPoint.size());
    unsigned int iJ = 0;
    unsigned int iK = 0;
    for (unsigned int iI = 0; iI < uP.size(); iI++)
    {
      if ((iJ < rState.size()) && (rState[iJ] == iI))
      {
        uP[iI] = rX[iJ++];
      }
      else
      {
        uP[iI] = rPoint[iK++];
      }
    }
    return uP;
  }

  class Section : public IMultiFunction
  {
  public:
    Section(const MultiFunction &rFunc, const std::vector<unsigned> &rState,
            const std::valarray<double> &rPoint)
        : m_uFunc(rFunc), m_uState(rState), m_uPoint(rPoint)
    {
      ASSERT(m_uFunc.dim() == m_uState.size() + m_uPoint.size());
      ASSERT(m_uState.size() > 0);
    }

    double operator()(const std::valarray<double> &rX) const
    {
      PRECONDITION(rX.size() == m_uState.size());
      PRECONDITION(belongs(rX));
      return m_uFunc(extend(rX, m_uPoint, m_uState));
    }
    bool belongs(const std::valarray<double> &rX) const
    {
      PRECONDITION(rX.size() == dim());
      return m_uFunc.belongs(extend(rX, m_uPoint, m_uState));
    }
    unsigned dim() const
    {
      return m_uState.size();
    }

  private:
    MultiFunction m_uFunc;
    std::vector<unsigned> m_uState;
    std::valarray<double> m_uPoint;
  };
} // namespace cflMultiFunction

MultiFunction cfl::toMultiFunction(const MultiFunction &rF,
                                   const std::vector<unsigned> &rS,
                                   const std::valarray<double> &rP)
{
  return MultiFunction(new cflMultiFunction::Section(rF, rS, rP));
}

namespace cflMultiFunction
{
  class Adapter3 : public IFunction
  {
  public:
    Adapter3(const MultiFunction &rFunc, unsigned iArg,
             const std::valarray<double> &rOtherArg)
        : m_uFunc(rFunc), m_iArg(iArg), m_uPoint(rFunc.dim())
    {
      ASSERT(m_uFunc.dim() <= 1);
      ASSERT(iArg < rFunc.dim());
      ASSERT(rOtherArg.size() + 1 == rFunc.dim());

      if (rOtherArg.size() > 0)
      {
        m_uPoint[std::slice(0, iArg, 1)] = rOtherArg[std::slice(0, iArg, 1)];
        m_uPoint[std::slice(iArg + 1, rOtherArg.size() - iArg, 1)] =
            rOtherArg[std::slice(iArg, rOtherArg.size() - iArg, 1)];
      }
    }
    double operator()(double dX) const
    {
      PRECONDITION(belongs(dX));
      m_uPoint[m_iArg] = dX;
      return m_uFunc(m_uPoint);
    }
    bool belongs(double dX) const
    {
      m_uPoint[m_iArg] = dX;
      return m_uFunc.belongs(m_uPoint);
    }

  private:
    MultiFunction m_uFunc;
    unsigned m_iArg;
    mutable std::valarray<double> m_uPoint;
  };
} // namespace cflMultiFunction

Function cfl::toFunction(const cfl::MultiFunction &rFunc, unsigned iArg,
                         const std::valarray<double> &rOtherArg)
{
  return Function(new cflMultiFunction::Adapter3(rFunc, iArg, rOtherArg));
}
