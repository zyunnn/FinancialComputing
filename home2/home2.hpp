#ifndef __home2_hpp__
#define __home2_hpp__

/**
 * @file home2.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Homework 2: one-dimensional root-finding.
 * @version 1.0
 * @date 2021-03-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "cfl/Root.hpp"
#include "cfl/RootD.hpp"

/**
 * @mainpage Homework 2: one-dimensional root-finding.
 */

namespace prb
{
  /**
   * @defgroup Home2Root Root finding algorithms.
   *
   * This module deals with one-dimensional root finding algorithms.
   * @{
   */

  /**
   * Computes prices ("clean" or "dirty") for a coupon bond. The bond
   * pays coupons \f$q\delta t\f$ at times
   * \f$(t_i)_{i=1,\dots,M}\f$ such that
   * \f[
   *     t_0 < t_1 \leq t_0+\delta t, \quad t_{i+1}-t_i= \delta t, \quad
   *     t_M = T.
   * \f]
   * The bond also pays notional \f$N=1\f$ at maturity \f$T\f$. The dirty or cash
   * price of the bond is given by
   * \f[
   * P^{d}(t_0) = q\delta t \sum_{i=1}^M e^{-\gamma(t_i-t_0)} + e^{-\gamma(T-t_0)}.
   * \f]
   * The clean price has the form:
   * \f[
   * P^{c}(t_0) = P^d(t_0) - A(t_0) = P^d(t_0) - q(t_0-s),
   * \f]
   * where \f$A(t_0)\f$ is the accrued interest and \f$s\f$ is the previous coupon
   * time.
   *
   * @param dRate  \f$q\f$ The coupon rate.
   * @param dPeriod  \f$\delta t\f$ The time interval between payments.
   * @param dMaturity  \f$T\f$ The maturity.
   * @param dYTM \f$\gamma\f$ The continuously compounded yield to maturity.
   * @param dInitialTime \f$t_0\f$ The initial time.
   * @param bClean This parameter controls the output. If its value
   * is \p true, then we compute "clean" prices. Otherwise, we
   * compute "dirty" prices that include the accrued interest from
   * the next coupon.
   *
   * @return The price ("clean" or "dirty") for the coupon bond.
   */
  double couponBond(double dRate, double dPeriod, double dMaturity,
                    double dYTM, double dInitialTime, bool bClean);

  /**
 * Computes the (dollar) duration of a coupon bond. The bond
 * pays coupons \f$q\delta t\f$ at times
 * \f$(t_i)_{i=1,\dots,M}\f$ such that
 * \f[
 *     t_0 < t_1 \leq t_0+\delta t, \quad t_{i+1}-t_i= \delta t, \quad
 *     t_M = T.
 * \f]

 * The bond also pays notional \f$N=1\f$ at maturity \f$T\f$. The
 * duration for the bond at \f$t_0\f$ defined as
 * \f[
 *  D = - P'(\gamma) = - \frac{dP}{d\gamma},
 * \f]
 * where \f$P = P(\gamma)\f$ is the ``dirty'' price of the bond for YTM
 * \f$\gamma\f$.
 *
 * @param dRate  (\f$q\f$) The coupon rate.
 * @param dPeriod  (\f$\delta t\f$) The time interval between payments.
 * @param dMaturity  (\f$T\f$) The maturity.
 * @param dYTM (\f$\gamma\f$) The continuously compounded yield to maturity.
 * @param dInitialTime (\f$t_0\f$) The initial time.
 *
 * @return The price ("clean" or "dirty") for the coupon bond.
 */
  double durationCouponBond(double dRate, double dPeriod, double dMaturity,
                            double dYTM, double dInitialTime);

  /**
   * Computes the continuously compounded YTM for a coupon bond. The
   * coupon bond pays coupons \f$q\delta t\f$ at times
   * \f$(t_i)_{i=1,\dots,M}\f$ such that
   * \f[
   *  t_0<t_1\leq t_0+\delta t, \quad t_{i+1}-t_i = \delta t,\quad
   *  t_M = T.
   * \f]
   * Yield to maturity \f$\gamma\f$ solves the equation:
   * \f[
   * S(t_0) = q\delta t \sum_{i=1}^M e^{-\gamma(t_i-t_0)} + e^{-\gamma(T-t_0)}.
   * \f]
   * We find \f$\gamma\f$ using Newton's gradient descent method.  If
   * \f$\gamma_n\f$ is yield's estimate at step \f$n\f$, then we stop
   * iterations as soon as
   * \f[
   *  |\gamma_{n+1}-\gamma_n|<\epsilon.
   * \f]
   *
   * @param dRate (\f$q\f$) The coupon rate.
   * @param dPeriod (\f$\delta t\f$) The time interval between payments.
   * @param dMaturity (\f$T\f$) The maturity.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   * @param dPrice (\f$S(t_0)\f$) The current price of the coupon bond.
   * @param dYield0 The initial guess of the YTM.
   * @param dErr The absolute error for the YTM.
   *
   * @return The YTM of the coupon bond.
   */
  double yieldTMCouponBond(double dRate, double dPeriod, double dMaturity,
                           double dInitialTime, double dPrice, double dYield0,
                           double dErr);

  /**
   * Computes the continuously compounded YTM for a coupon bond. The
   * coupon bond pays coupons \f$q\delta t\f$ at times
   * \f$(t_i)_{i=1,\dots,M}\f$ such that
   * \f[
   *  t_0<t_1\leq t_0+\delta t, \quad t_{i+1}-t_i = \delta t,\quad
   *  t_M = T.
   * \f]
   * Yield to maturity \f$\gamma\f$ solves the equation:
   * \f[
   * S(t_0) = q\delta t \sum_{i=1}^M e^{-\gamma(t_i-t_0)} + e^{-\gamma(T-t_0)}.
   * \f]
   *
   * @param dRate (\f$q\f$) The coupon rate.
   * @param dPeriod (\f$\delta t\f$) The time interval between payments.
   * @param dMaturity (\f$T\f$) The maturity.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   * @param dPrice (\f$S(t_0)\f$) The current price of the coupon bond.
   * @param dYield0 The initial guess of the YTM.
   * @param rRootD The one-dimensional root finder that relies
   * on the function and its derivative.
   *
   * @return The YTM of the coupon bond.
   */
  double yieldTMCouponBond(double dRate, double dPeriod, double dMaturity,
                           double dInitialTime, double dPrice, double dYield0,
                           const cfl::RootD &rRootD);

  /**
   * The classical bisection algorithm of bracketing the roots of
   * the function.
   *
   * @param dAbsErr The absolute error for the root.
   * @param dRelErr The relative error for the root.
   * @param iMaxSteps The maximal number of iterations.
   * @return cfl::Root The bisection algorithm.
   */
  cfl::Root bisection(double dAbsErr, double dRelErr, unsigned iMaxSteps = cfl::IMAX);

  /**
   * The classical bisection algorithm of bracketing the roots of
   * the function.
   *
   * @param dFuncErr The absolute residual error of the function.
   * @param iMaxSteps The maximal number of iterations.
   * @return cfl::Root The bisection algorithm.
   */
  cfl::Root bisection(double dFuncErr, unsigned iMaxSteps = cfl::IMAX);

  /**
   * The false position algorithm of bracketing the roots of the
   * function.
   *
   * @param dAbsErr The absolute error for the root.
   * @param dRelErr The relative error for the root.
   * @param iMaxSteps The maximal number of iterations.
   * @return cfl::Root The false position algorithm.
   */
  cfl::Root falsepos(double dAbsErr, double dRelErr, unsigned iMaxSteps = cfl::IMAX);

  /**
   * The false position algorithm of bracketing the roots of the
   * function.
   *
   * @param dFuncErr The absolute residual error of the function.
   * @param iMaxSteps The maximal number of iterations.
   * @return cfl::Root The bisection algorithm.
   */
  cfl::Root falsepos(double dFuncErr, unsigned iMaxSteps = cfl::IMAX);

  /**
   * The Brent-Dekker algorithm of bracketing the roots of the
   * function.
   *
   * @param dAbsErr The absolute error for the root.
   * @param dRelErr The relative error for the root.
   * @param iMaxSteps The maximal number of iterations.
   * @return cfl::Root The Brent-Dekker algorithm.
   */
  cfl::Root brent(double dAbsErr, double dRelErr, unsigned iMaxSteps = cfl::IMAX);

  /**
   * The Brent-Dekker algorithm of bracketing the roots of the
   * function.
   *
   * @param dFuncErr The absolute residual error of the function.
   * @param iMaxSteps The maximal number of iterations.
   * @return cfl::Root The Brent-Dekker algorithm.
   */
  cfl::Root brent(double dFuncErr, unsigned iMaxSteps = cfl::IMAX);

  /**
   * Computes the continuously compounded yield to maturity (YTM) for
   * a cash flow using a root bracketing algorithm. Yield to maturity
   * \f$\gamma\f$ solves the equation:
   * \f[
   *   S(t_0) = \sum_{i=1}^M P_ie^{-\gamma(t_i-t_0)},
   * \f]
   * where \f$(P_i)_{i=1,\dots,M}\f$ and \f$(t_i)_{i=1,\dots,M}\f$ are
   * the payments and the payment times, respectively, \f$t_1>t_0\f$.
   *
   * @param rPayments \f$(P_i)\f$ The vector of payments.
   * @param rPaymentTimes \f$(t_i)\f$ The vector of payment times, \f$t_1>t_0\f$.
   * @param dValue \f$S(t_0)\f$ The current value of the payments.
   * @param dInitialTime \f$t_0\f$ The initial time.
   * @param dY0 The lower bound for the YTM.
   * @param dY1 The upper bound for the YTM.
   * @param rRoot The root bracketing algorithm.
   *
   * @return The YTM of the payments.
   */
  double yieldTMCashFlow(const std::vector<double> &rPayments,
                         const std::vector<double> &rPaymentTimes,
                         double dValue, double dInitialTime,
                         double dY0, double dY1, const cfl::Root &rRoot);

  /**
   * Computes the curve of forward yields to maturity for given cash
   * flow. For \f$t\in [t_0,t_M)\f$, the forward yield to maturity
   * \f$\gamma(t)\f$ solves the equation:
   * \f[
   *  F(t) = \sum_{t_i>t} P_ie^{-\gamma(t)(t_i-t)},
   * \f]
   * where \f$F(t)\f$ is the forward price computed at \f$t_0\f$ for
   * delivery at \f$t\f$. In the forward contract, the buyer pays
   * forward price \f$F(t)\f$ at delivery time \f$t\f$ and then receives
   * payments \f$(P_i)\f$ at payments times \f$t_i>t\f$.
   *
   * @param rPayments \f$(P_i)\f$ The vector of payments.
   * @param rPaymentTimes \f$(t_i)\f$ The vector of payment times, \f$t_1>t_0\f$.
   * @param rForward \f$(F(t))\f$ The forward price curve.
   * @param dInitialTime \f$t_0\f$ The initial time.
   * @param dY0 The lower bound for the YTM.
   * @param dY1 The upper bound for the YTM.
   * @param rRoot The root bracketing algorithm.
   *
   * @return The forward price curve of a cash flow.
   */
  cfl::Function forwardYTMCashFlow(const std::vector<double> &rPayments,
                                   const std::vector<double> &rPaymentTimes,
                                   const cfl::Function &rForward,
                                   double dInitialTime, double dY0, double dY1,
                                   const cfl::Root &rRoot);
  /** @} */
}

#endif // of __home2_hpp__
