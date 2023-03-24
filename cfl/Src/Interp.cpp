#include "cfl/Interp.hpp"
#include "cfl/Error.hpp"
#include <gsl/gsl_spline.h>

using namespace cfl;

// class Interp

cfl::Interp::Interp(IInterp *pNewP)
    : m_uP(pNewP) {}

// class LinInterp

class LinInterp : public IInterp
{
public:
  Function
  interpolate(const std::vector<double> &rArg, const std::vector<double> &rVal) const
  {
    PRECONDITION((rArg.size() == rVal.size()) && (rArg.size() >= 2));
    PRECONDITION(is_sorted(rArg.begin(), rArg.end(), std::less_equal<double>()));

    std::shared_ptr<gsl_spline> uS(gsl_spline_alloc(gsl_interp_linear, rArg.size()), &gsl_spline_free);
    gsl_spline_init(uS.get(), rArg.data(), rVal.data(), rArg.size());

    std::shared_ptr<gsl_interp_accel> uAcc(gsl_interp_accel_alloc(), &gsl_interp_accel_free);

    std::function<double(double)> uF = [uS, uAcc](double dX)
    {
      return gsl_spline_eval(uS.get(), dX, uAcc.get());
    };

    return Function(uF, rArg.front(), rArg.back());
  }
};

// functions from NInterp

cfl::Interp cfl::NInterp::linear()
{
  return Interp(new LinInterp());
}
