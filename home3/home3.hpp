#ifndef __home3_hpp__
#define __home3_hpp__

/**
 * @file home3.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Homework 3: one-dimensional interpolation.
 * @version 1.0
 * @date 2021-03-16
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "cfl/Interp.hpp"

/**
 * @mainpage Homework 3: one-dimensional interpolation.
 */

namespace prb
{
  /**
   * @defgroup Home3Interp Interpolation of one-dimensional functions.
   *
   * This module deals with one-dimensional interpolation.
   * @{
   */

  /**
   * Cubic spline interpolation.
   *
   * @return The engine for cubic spline interpolation.
   */
  cfl::Interp cspline();

  /**
   * Steffen interpolation produces monotone function between
   * interplation nodes.
   *
   * @return The engine for Steffen interpolation.
   */
  cfl::Interp steffen();

  /**
   * Akima interpolation is a variant of cubic spline with
   * more tolerance to outliers.
   *
   * @return The engine for Akima interpolation.
   */
  cfl::Interp akima();

  /**
   * Computes forward curve
   * \f[
   *   F(t) = S_0 e^{q(t)(t-t_0)}, \quad t\in [t_0,t_M],
   * \f]
   * where the cost-of-carry rate \f$q=q(t)\f$ is obtained by the
   * interpolation of the market cost-of-carry rates with method \p
   * rInterp.
   *
   * @param dSpot (\f$S_0\f$) The spot price of the stock.
   * @param rDeliveryTimes (\f$(t_i)_{i=1,\dots,M}\f$) The delivery
   * times for the market forward prices.
   * @param rForwardPrices The market forward prices.
   * @param dInitialCarryRate (\f$q(t_0)\f$) The initial cost-of-carry rate.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   * @param rInterp The interpolation method for the cost-of-carry rates.
   *
   * @return The forward curve obtained by interpolation of
   * the market cost-of-carry rates with method \p rInterp.
   */
  cfl::Function forwardCarryInterp(double dSpot,
                                   const std::vector<double> &rDeliveryTimes,
                                   const std::vector<double> &rForwardPrices,
                                   double dInitialCarryRate, double dInitialTime,
                                   const cfl::Interp &rInterp);

  /**
   * Computes forward curve
   * \f[
   * F(t) = S_0 e^{q(t)(t-t_0)}, \quad t\in [t_0,t_M],
   * \f]
   * where cost-of-carry rate \f$q=q(t)\f$ is obtained by the Steffen
   * (monotone cubic spline) interpolation of the market cost-of-carry
   * rates. On the first interval \f$[t_0,t_1]\f$, the cost-of-carry
   * rate is constant:
   * \f[
   * q(t) = q(t_1), \quad t\in [t_0,t_1].
   * \f]
   *
   * @param dSpot (\f$S_0\f$) The spot price of the stock.
   * @param rDeliveryTimes (\f$(t_i)_{i=1,\dots,M}\f$) The maturities
   * of the market forward contracts, \f$t_0<t_1\f$.
   * @param rForwardPrices (\f$(F(t_i))_{i=1,\dots,M}\f$) The market
   * forward prices.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   *
   * @return The forward curve obtained by the Steffen interpolation of
   * the market cost-of-carry rates.
   */
  cfl::Function forwardCarrySteffenInterp(double dSpot,
                                          const std::vector<double> &rDeliveryTimes,
                                          const std::vector<double> &rForwardPrices,
                                          double dInitialTime);

  /**
   * Computes implied volatility curve \f$\Sigma = \Sigma(t)\f$ by
   * applying interpolation method \p rInterp to variance curve
   * \f[
   *      V(t) = \Sigma^2(t)(t - t_0), \quad t\geq t_0.
   * \f]
   * The resulting volatility curve is constant on \f$[t_0,t_1]\f$.
   *
   * @param rTimes (\f$(t_i)_{i=1,\dots,M}\f$) The maturities of the
   * market implied volatilities, (\f$t_1>t_0\f$.
   * @param rVols The market implied volatilities.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   * @param rInterp A monotone interpolation method.
   *
   * @return cfl::Function The implied volatility curve obtained by
   * the interpolation of market variances.
   */
  cfl::Function
  volatilityVarInterp(const std::vector<double> &rTimes,
                      const std::vector<double> &rVols,
                      double dInitialTime,
                      const cfl::Interp &rInterp);

  /** @} */
}

#endif // of __home3_hpp__
