#ifndef __home4_hpp__
#define __home4_hpp__

/**
 * @file home4.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Homework 4: least-squares fitting.
 * @version 1.0
 * @date 2021-03-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "cfl/Fit.hpp"

/**
 * @mainpage Homework 4: least-squares fitting.
 */

namespace prb
{
  /**
   * @defgroup Home4Fit Fitting of one-dimensional functions.
   *
   * This module deals with least-squares fitting of one-dimensional
   * functions.
   *
   * @{
   */

  /**
   * Classical least square fit of one-dimensional function with a
   * vector of basis functions \f$(g_j=g_j(x))_{j=0,\dots,M-1}\f$
   * and a free function \f$h=h(x)\f$.  The family of fitting
   * functions has the form:
   * \f[
   *   f(x, \mathbf{c}) = \sum_{j=0}^{M-1} c_j g_j(x) + h(x),
   * \f]
   * where \f$\mathbf{c} = (c_0,\dots,c_{M-1})\f$ is the vector of
   * the fitting coefficients.
   *
   * @param rBasisF The vector of basis functions \f$(g_j=g_j(x))_{j=0,\dots,M-1}\f$.
   * @param rFreeF The free function \f$h=h(x)\f$.
   * @return Linear least square fitting engine.
   */
  cfl::Fit linear(const std::vector<cfl::Function> &rBasisF,
                  const cfl::Function &rFreeF = cfl::Function(0.));
  
  /**
   * Returns  discount curve
   * \f[
   *    d(t) = \exp(-\gamma(t)(t-t_0)), \quad t\geq t_0,
   * \f]
   * by the least-squares fit of yield curve \f$\gamma=\gamma(t)\f$ to
   * continuously compounded market yields with fitting method \p
   * rFit.
   *
   * @param rTimes The maturities of market discount factors.
   * @param rDF The market discount factors.
   * @param dInitialTime  (\f$t_0\f$) The initial time.
   * @param rFit The fitting method.
   * @param rErr The error function of the fit for discount factors.
   *
   * @return The fitted discount curve and its error function. We also
   * obtain the fitted coefficients and their covariance matrix
   * through \p rFit.
   */
  cfl::Function
  discountYieldFit(const std::vector<double> &rTimes, const std::vector<double> &rDF,
                   double dInitialTime, cfl::Fit &rFit, cfl::Function &rErr);

  /**
   * Returns  discount curve
   * \f[
   *    d(t) = \exp(-\gamma(t)(t-t_0)), \quad t\geq t_0,
   * \f]
   * by the least-squares fit of the stationary yield curve in the Hull
   * and White model
   * \f[
   * \gamma(t) = c_0 + c_1 \frac{1-e^{-\lambda (t-t_0)}}{\lambda(t-t_0)},
   * \quad t\geq t_0,
   * \f]
   * to the market yields. Here, \f$c_0\f$ and \f$c_1\f$ are the fitting constants.
   *
   * @param rDiscountTimes The  maturities for market
   * discount factors.
   * @param rDiscountFactors The  market discount factors.
   * @param dLambda (\f$\lambda\geq 0\f$) The mean-reversion rate.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   * @param rErr The error function of the fit for discount factors.
   * @param rParam The fitted coefficients, their covariance matrix, and
   * the total \f$\chi^2\f$ fitting error.
   *
   * @return The fitted discount curve in Hull and White model and its
   * error function. We also obtain the fitted coefficients and their
   * covariance matrix.
   */
  cfl::Function discountHullWhiteFit(const std::vector<double> &rDiscountTimes,
                                     const std::vector<double> &rDiscountFactors,
                                     double dLambda, double dInitialTime,
                                     cfl::Function &rErr, cfl::FitParam &rParam);

  /**
   * Returns the discount curve
   * \f[
   *    d(t) = \exp(-\gamma(t)(t-t_0)), \quad t\geq t_0,
   * \f]
   * by the least-squares fit of Nelson-Siegel yield curve
   * \f[
   *  \gamma(t) = c_0 + c_1 \frac{1-e^{-\lambda(t-t_0)}}{\lambda (t-t_0)} +
   *  c_2 \left(\frac{1-e^{-\lambda(t-t_0)}}{\lambda (t-t_0)}  -
   *     e^{-\lambda (t-t_0)}\right), \quad t\geq t_0,
   * \f]
   * to continuously compounded market yields. Here \f$c_0\f$,
   * \f$c_1\f$, and \f$c_2\f$ are the fitting constants.
   *
   * @param rTimes The maturities of market discount factors.
   * @param rDF The market discount factors.
   * @param dLambda (\f$\lambda\geq 0\f$) The mean-reversion rate.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   * @param rErr The error function of the fit for discount factors.
   * @param rParam The fitted coefficients, their covariance matrix, and
   * the total \f$\chi^2\f$ fitting error.
   *
   * @return The fitted discount curve and its error function. We also
   * obtain the fitted coefficients and their covariance matrix.
   */
  cfl::Function
  discountNelsonSiegelFit(const std::vector<double> &rTimes,
                          const std::vector<double> &rDF,
                          double dLambda, double dInitialTime,
                          cfl::Function &rErr, cfl::FitParam &rParam);

  /**
   * Returns discount curve
   * \f[
   *    d(t) = \exp(-\gamma(t)(t-t_0)), \quad t\geq t_0,
   * \f]
   * by the least-squares fit of Svensson yield curve
   * \f[
   *  \gamma(t) = c_0 + c_1 \frac{1-e^{-\lambda_1(t-t_0)}}{\lambda_1 (t-t_0)} +
   *  c_2 \left(\frac{1-e^{-\lambda_1(t-t_0)}}{\lambda_1 (t-t_0)}  -
   *     e^{-\lambda_1 (t-t_0)}\right) +
   *  c_3 \left(\frac{1-e^{-\lambda_2(t-t_0)}}{\lambda_2 (t-t_0)}  -
   *     e^{-\lambda_2 (t-t_0)}\right) , \quad t\geq t_0,
   * \f]
   * to continuously compounded market yields. Here \f$c_0\f$,
   * \f$c_1\f$, \f$c_2\f$, and \f$c_3\f$ are the fitting constants.
   *
   * @param rTimes The maturities of market discount factors.
   * @param rDF The market discount factors.
   * @param dLambda1 (\f$\lambda_1 \geq 0\f$) The first mean-reversion rate.
   * @param dLambda2 (\f$\lambda_2 \geq 0\f$) The second
   * mean-reversion rate, \f$\lambda_2\not=\lambda_1\f$.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   * @param rErr The error function of the fit for discount factors.
   * @param rParam The fitted coefficients, their covariance matrix, and
   * the total \f$\chi^2\f$ fitting error.
   *
   * @return The fitted discount curve and its error function. We also
   * obtain the fitted coefficients and their covariance matrix.
   */
  cfl::Function
  discountSvenssonFit(const std::vector<double> &rTimes,
                      const std::vector<double> &rDF,
                      double dLambda1, double dLambda2,
                      double dInitialTime, cfl::Function &rErr,
                      cfl::FitParam &rParam);
  /** @} */
}

#endif // of __home4_hpp__
