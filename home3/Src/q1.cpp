#include "home3/home3.hpp"
#include <gsl/gsl_spline.h>

using namespace cfl;
using namespace std;


class SplineInterp : public IInterp 
{
    public:
        SplineInterp(const gsl_interp_type *pT) : m_pT(pT) {}

        Function interpolate(const std::vector<double> &rArg, const std::vector<double> &rVal) const
        {
            PRECONDITION((rArg.size() == rVal.size()) && (rArg.size() >= 2));
            PRECONDITION(std::is_sorted(rArg.begin(), rArg.end(), std::less_equal<double>()));

            std::shared_ptr<gsl_spline> uS(gsl_spline_alloc(m_pT, rArg.size()), &gsl_spline_free);
            gsl_spline_init(uS.get(), rArg.data(), rVal.data(), rArg.size());

            std::shared_ptr<gsl_interp_accel> uAcc(gsl_interp_accel_alloc(), &gsl_interp_accel_free);

            std::function<double(double)> uF = [uS, uAcc](double dX) 
            {
                return gsl_spline_eval(uS.get(), dX, uAcc.get());
            };

            return Function(uF, rArg.front(), rArg.back());
        }
    private:
        const gsl_interp_type *m_pT;
};

cfl::Interp prb::akima() 
{
    return Interp(new SplineInterp(gsl_interp_akima));
}

cfl::Interp prb::steffen() 
{
    return Interp(new SplineInterp(gsl_interp_steffen));
}

cfl::Interp prb::cspline() 
{
    return Interp(new SplineInterp(gsl_interp_cspline));
}
