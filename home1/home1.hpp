#ifndef __home1_hpp__
#define __home1_hpp__

/**
 * @file home1.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Homework 1: data curves for financial models
 * @version 1.0
 * @date 2023-03-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "cfl/Data.hpp"

/**
 * @mainpage Homework 1: data curves for financial models
 */

namespace prb
{
  /**
   * @defgroup Home1Data Data structures.
   *
   * This module constructs input data curves for financial models.
   * @{
   */

  /**
   * Computes cost-of-carry rate curve \f$c=(c(t))_{t\geq t_0}\f$
   * for the Black model:
   * \f[
   * q(t) = \theta \frac{1-e^{-\lambda(t-t_0)}}{\lambda(t-t_0)} +
   * \frac{\sigma^2}2 \frac{1-e^{-2\lambda(t-t_0)}}{2\lambda(t-t_0)},
   * \quad t\geq t_0.
   * \f]
   *
   * @param dTheta (\f$\theta\f$) The drift term.
   * @param dLambda (\f$\lambda\geq 0\f$) The mean reversion level.
   * @param dSigma  (\f$\sigma\geq 0\f$) The volatility.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   *
   * @return The cost-of-carry rate curve in Black model.
   */
  cfl::Function
  carryBlack(double dTheta, double dLambda, double dSigma,
             double dInitialTime);

  /**
   * Computes yield curve \f$\gamma=\gamma(t)\f$ for the Svensson
   * model:
   * \f[
   *  \gamma(t) = c_0 + c_1 \frac{1-e^{-\lambda_1(t-t_0)}}{\lambda_1
   *  (t-t_0)} + c_2 \left(\frac{1-e^{-\lambda_1(t-t_0)}}{\lambda_1
   *  (t-t_0)} - e^{-\lambda_1 (t-t_0)}\right) + c_3
   *  \left(\frac{1-e^{-\lambda_2(t-t_0)}}{\lambda_2 (t-t_0)} -
   *  e^{-\lambda_2 (t-t_0)}\right) , \quad t\geq t_0.
   * \f]
   *
   * @param dC0 (\f$c_0\f$) The first constant
   * @param dC1 (\f$c_1\f$) The second constant.
   * @param dC2 (\f$c_2\f$) The third constant.
   * @param dC3 (\f$c_3\f$) The fourth constant.
   * @param dLambda1 (\f$\lambda_1>0\f$) The first mean-reversion rate.
   * @param dLambda2 (\f$\lambda_2>0\f$) The second mean-reversion
   * rate, \f$\lambda_1\not=\lambda_2\f$.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   *
   * @return The yield curve for the Svensson model.
   */
  cfl::Function
  yieldSvensson(double dC0, double dC1, double dC2, double dC3,
                double dLambda1, double dLambda2, double dInitialTime);

  /**
   * Returns the stationary implied volatility curve for the Black
   * model:
   * \f[
   * \Sigma(t) = \sigma \sqrt{\frac{1 -\exp(-2\lambda
   *   (t-t_0))}{2\lambda (t-t_0)}}, \quad t\geq t_0.
   * \f]
   *
   * @param dSigma (\f$\sigma\geq 0\f$) The short-term volatility.
   * @param dLambda (\f$\lambda\geq 0\f$) The mean-reversion rate.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   *
   * @return The stationary implied volatility curve in Black model.
   */
  cfl::Function
  volatilityBlack(double dSigma, double dLambda, double dInitialTime);

  /**
   * Computes the curve of forward prices for a dividend paying
   * stock. The buyer pays forward price \f$F(t)\f$ at delivery time
   * \f$t\f$ and then receives the stock. If \f$t\f$ is a dividend
   * time, then the buyer gets the dividend paid at \f$t\f$. It costs
   * nothing to enter a forward contract at its issue time \f$t_0\f$.
   *
   * @param dSpot The spot price of the stock.
   * @param rDividendsTimes The dividend times.
   * @param rDividends The dividend payments.
   * @param rDiscount The discount curve.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   *
   * @return The forward price curve for the stock.
   */
  cfl::Function forwardStockDividends(double dSpot,
                                      const std::vector<double> &rDividendsTimes,
                                      const std::vector<double> &rDividends,
                                      const cfl::Function &rDiscount,
                                      double dInitialTime);

  /**
   * Computes the curve of forward prices ("clean" or "dirty") for a
   * coupon bond. The bond pays coupons \f$q\delta t\f$ at times
   * \f$(t_i)_{i=1,\dots,M}\f$ such that
   * \f[
   *     t_0 < t_1 \leq t_0+\delta t, \quad t_{i+1}-t_i= \delta t, \quad
   *     t_M = T.
   * \f]
   * The bond also pays notional \f$N=1\f$ at maturity \f$T\f$. The buyer of
   * the forward contract pays forward price \f$F(t)\f$ at delivery time
   * \f$t\f$ and then receives coupons \f$q\delta t\f$ at payments times
   * \f$t_i>t\f$ and notional \f$N=1\f$ at maturity \f$T\f$.
   *
   * @param dRate  (\f$q\f$) The coupon rate.
   * @param dPeriod  (\f$\delta t\f$) The time interval between payments.
   * @param dMaturity  (\f$T\f$) The maturity.
   * @param rDiscount The discount curve.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   * @param bClean This parameter controls the output. If its value
   * is \p true, then we compute "clean" prices. Otherwise, we
   * compute "dirty" prices that include the accrued interest from
   * the next coupon.
   *
   * @return The forward price ("clean" or "dirty") curve for the coupon
   * bond.
   */
  cfl::Function forwardCouponBond(double dRate, double dPeriod, double dMaturity,
                                  const cfl::Function &rDiscount,
                                  double dInitialTime, bool bClean);

  /**
   * Computes the curve of forward rates. It costs nothing to enter
   * the forward rate agreement (FRA) with maturity \f$t\f$ and period
   * \f$\delta t\f$ as either a borrower or a lender. Forward rate
   * \f$R^f(t,t+\delta t)\f$ is set at issue time \f$t_0\f$. In the
   * contract,
   * 1. At maturity \f$t\f$, the borrower receives notional \f$N\f$.
   * 2. At time \f$t+\delta t\f$, the borrower pays the notional plus
   * the interest computed at the forward rate:
   * \f[
   *    N(1+ R^f(t,t+\delta t)\delta t).
   * \f]
   *
   * @param dPeriod (\f$\delta t\f$)  The rate period.
   * @param rDiscount The discount curve.
   * @return cfl::Function \f$(R^f(t,t+\delta t))_{t\geq t_0}\f$ The
   * curve of forward rates.
   */
  cfl::Function forwardRate(double dPeriod,
                            const cfl::Function &rDiscount);

  /** @} */
}

#endif // of __home1_hpp__
