#include <cmath>
#include "cfl/Function.hpp"
#include "cfl/Error.hpp"

using namespace cfl;
using namespace std;

cfl::Function::Function(IFunction *pNewP)
    : m_pF(pNewP) {}

namespace cflFunction
{
  //  CLASS: Adapter

  class Adapter : public cfl::IFunction
  {
  public:
    Adapter(const std::function<double(double)> &rF,
            const std::function<bool(double)> &rB)
        : m_uF(rF), m_uB(rB) {}

    Adapter(const std::function<double(double)> &rF, double dL, double dR)
        : Adapter(rF, [dL, dR](double dX)
                  { return (dL <= dX) && (dX <= dR); })
    {
      POSTCONDITION(dL <= dR);
    }

    Adapter(double dV, double dL = -std::numeric_limits<double>::max(),
            double dR = std::numeric_limits<double>::max())
        : Adapter([dV](double dX)
                  { return dV; },
                  dL, dR) {}

    double operator()(double dX) const
    {
      PRECONDITION(belongs(dX));
      return m_uF(dX);
    }
    bool belongs(double dX) const { return m_uB(dX); }

  private:
    std::function<double(double)> m_uF;
    std::function<bool(double)> m_uB;
  };

  // CLASS: Composite

  class Composite : public IFunction
  {
  public:
    Composite(const Function &rFunc, const std::function<double(double)> &rUnOp)
        : m_uFunc(rFunc), m_uUnOp(rUnOp) {}

    double operator()(double dX) const
    {
      return m_uUnOp(m_uFunc(dX));
    }
    bool belongs(double dX) const
    {
      return m_uFunc.belongs(dX);
    }

  private:
    Function m_uFunc;
    std::function<double(double)> m_uUnOp;
  };

  // CLASS: BinComposite

  class BinComposite : public IFunction
  {
  public:
    BinComposite(const Function &rFunc1, const Function &rFunc2,
                 const std::function<double(double, double)> &rBinOp)
        : m_uFunc1(rFunc1), m_uFunc2(rFunc2), m_uBinOp(rBinOp) {}

    double operator()(double dX) const
    {
      return m_uBinOp(m_uFunc1(dX), m_uFunc2(dX));
    }
    bool belongs(double dX) const
    {
      return (m_uFunc1.belongs(dX)) && (m_uFunc2.belongs(dX));
    }

  private:
    Function m_uFunc1;
    Function m_uFunc2;
    std::function<double(double, double)> m_uBinOp;
  };
} // namespace cflFunction

// CLASS: Function

cfl::Function::Function(double dV, double dL, double dR)
    : m_pF(new cflFunction::Adapter(dV, dL, dR)) {}

cfl::Function::Function(const std::function<double(double)> &rF,
                        double dL, double dR)
    : m_pF(new cflFunction::Adapter(rF, dL, dR)) {}

cfl::Function::Function(const std::function<double(double)> &rF,
                        const std::function<bool(double)> &rBelongs)
    : m_pF(new cflFunction::Adapter(rF, rBelongs)) {}

Function &cfl::Function::operator=(double dV)
{
  m_pF.reset(new cflFunction::Adapter(dV));
  return *this;
}

Function &cfl::Function::operator+=(const Function &rFunc)
{
  m_pF.reset(new cflFunction::BinComposite(*this, rFunc, std::plus<double>()));
  return *this;
}

Function &cfl::Function::operator*=(const Function &rFunc)
{
  m_pF.reset(new cflFunction::BinComposite(*this, rFunc, std::multiplies<double>()));
  return *this;
}

Function &cfl::Function::operator-=(const Function &rFunc)
{
  m_pF.reset(new cflFunction::BinComposite(*this, rFunc, std::minus<double>()));
  return *this;
}

Function &cfl::Function::operator/=(const Function &rFunc)
{
  m_pF.reset(new cflFunction::BinComposite(*this, rFunc, std::divides<double>()));
  return *this;
}

Function &cfl::Function::operator+=(double dX)
{
  m_pF.reset(new cflFunction::Composite(*this, [dX](double dY)
                                        { return dY + dX; }));
  return *this;
}

Function &cfl::Function::operator-=(double dX)
{
  m_pF.reset(new cflFunction::Composite(*this, [dX](double dY)
                                        { return dY - dX; }));
  return *this;
}

Function &cfl::Function::operator*=(double dX)
{
  m_pF.reset(new cflFunction::Composite(*this, [dX](double dY)
                                        { return dY * dX; }));
  return *this;
}

Function &cfl::Function::operator/=(double dX)
{
  m_pF.reset(new cflFunction::Composite(*this, [dX](double dY)
                                        { return dY / dX; }));
  return *this;
}

// GLOBAL

cfl::Function cfl::apply(const cfl::Function &rF, const std::function<double(double)> &rOp)
{
  return Function(new cflFunction::Composite(rF, rOp));
}

cfl::Function cfl::apply(const cfl::Function &rF, const cfl::Function &rG,
                         const std::function<double(double, double)> &rOp)
{
  return Function(new cflFunction::BinComposite(rF, rG, rOp));
}
