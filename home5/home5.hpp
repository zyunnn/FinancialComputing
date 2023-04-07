#ifndef __home5_hpp__
#define __home5_hpp__

/**
 * @file home5.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Homework 5: least-squares fitting with B-splines.
 * @version 1.0
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "cfl/Fit.hpp"

/**
 * @mainpage Homework 5: least-squares fitting with B-splines.
 */

namespace prb
{
  /**
   * @defgroup Home5Fit Fitting of one-dimensional functions.
   *
   * This module deals with least-squares fitting of one-dimensional
   * functions.
   *
   * @{
   */

  /**
   * Least squares fitting with basis splines.
   *
   * @param iOrder The order of the fitting spline.
   * @param rBreakpoints The vector of breakpoints.
   * @return Least square fitting engine with basis splines.
   */
  cfl::Fit bspline(unsigned iOrder, const std::vector<double> &rBreakpoints);

  /**
   * Least squares fitting with basis splines and uniform breakpoints.
   *
   * @param iOrder The order of the fitting spline.
   * @param dL The left point of the domain.
   * @param dR The right point of the  domain.
   * @param iBreakpoints The number of breakpoints.
   * @return Least square fitting engine with basis splines.
   */
  cfl::Fit bspline(unsigned iOrder, double dL, double dR, unsigned iBreakpoints);

    /**
   * Returns the forward exchange rate curve in the form:
   * \f[
   * F(t) = S_0 \exp(q(t)(t-t_0)), \quad t\geq t_0,
   * \f]
   * where cost-of-carry rate \f$q=q(t)\f$ is obtained by the
   * least-squares fit of the market cost-of-carry rates with method
   * \p rFit.
   *
   * @param dSpotFX The spot exchange rate.
   * @param rTimes The  maturities for discount factors.
   * @param rDomesticDiscountFactors The  domestic discount factors.
   * @param rForeignDiscountFactors The  foreign discount factors.
   * @param dInitialTime The initial time.
   * @param rFit The fitting method.
   * @param rErr The error function of the fit for forward prices.
   *
   * @return The fitted forward fx curve and its error function. We
   * also obtain the fitted coefficients and their covariance matrix
   * through \p rFit.
   */
  cfl::Function
  forwardFXCarryFit(double dSpotFX, const std::vector<double> &rTimes,
                    const std::vector<double> &rDomesticDiscountFactors,
                    const std::vector<double> &rForeignDiscountFactors,
                    double dInitialTime, cfl::Fit &rFit, cfl::Function &rErr);

   /**
   * Returns  discount curve
   * \f[
   *    d(t) = \exp(-\gamma(t)(t-t_0)), \quad t\geq t_0,
   * \f]
   * by the least-squares fit with method \p rFit of yield curve
   * \f$\gamma=\gamma(t)\f$ to continuously compounded market yields
   * determined by float rates.
   *
   * @param rPeriods The periods of float rates. For example,
   * value 0.25 means 3 month rate.
   * @param rRates The  market float rates.
   * @param dInitialTime The initial time.
   * @param rFit The fitting method.
   * @param rErr The error function of the fit for discount factors.
   *
   * @return The fitted discount curve and its error function. We also
   * obtain the fitted coefficients and their covariance matrix
   * through \p rFit.
   */
  cfl::Function
  discountRateFit(const std::vector<double> &rPeriods,
                  const std::vector<double> &rRates,
                  double dInitialTime, cfl::Fit &rFit,
                  cfl::Function &rErr);
  
  /**
   * Returns discount curve
   * \f[
   *    d(t) = \exp(-\gamma(t)(t-t_0)), \quad t\geq t_0,
   * \f]
   * by the least-squares fit with method \p rFit of the yield curve
   * \f$\gamma = \gamma(t)\f$ to the market yields to maturity
   * determined by the swap rates.
   *
   * @param rSwapRates \f$(R_i)\f$ the vector of swap
   * rates, where \f$R_i\f$ is the market swap rate in the contract with
   * time interval \f$\delta t\f$ and number of payments \f$i\f$.
   * @param dPeriod (\f$\delta t\f$) The time interval between two payments.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   * @param rFit The fitting method.
   * @param rErr The error function of the fit for discount factors.
   *
   * @return The fitted discount curve and its error function. We also
   * obtain the fitted coefficients and their covariance matrix
   * through \p rFit.
   */
  cfl::Function
  discountSwapFit(const std::vector<double> &rSwapRates,
                  double dPeriod, double dInitialTime,
                  cfl::Fit &rFit, cfl::Function &rErr);

  /**
   * Returns discount curve
   * \f[
   *    d(t) = \exp(-\gamma(t)(t-t_0)), \quad t\geq t_0,
   * \f]
   * by approximate least-squares fit of market discount factors. More
   * precisely, yield curve \f$\gamma=\gamma(t)\f$ is the result of
   * the minimization:
   * \f[
   * \sum_{i=1}^{M} w_i(\gamma(t_i) - \gamma_i)^2  \to \min,
   * \f]
   * with method \p rFit and weights
   * \f[
   * w_i = d_i^2 (t_i-t_0)^2, \quad i=1,\dots,M,
   * \f]
   * where \f$\gamma_i\f$ is market's continuously compounded yield
   * for maturity \f$t_i\f$. This expression is the first order
   * approximation to the (non-linear) least-squares fitting of
   * discount curve \f$d=d(t)\f$ to market discount factors
   * \f$(d_i)\f$.
   *
   * @param rDiscountTimes (\f$(t_i)_{i=1}^{M}\f$) The maturities for market
   * discount factors.
   * @param rDiscountFactors (\f$(d_i)_{i=1}^M\f$) The market discount factors.
   * @param dInitialTime (\f$t_0\f$) The initial time.
   * @param rFit The fitting method.
   * @param rErr The error function of the fit for discount factors.
   *
   * @return The fitted discount curve and its error function. We also
   * obtain the fitted coefficients and their covariance matrix
   * through \p rFit.
   */
  cfl::Function discountApproxFit(const std::vector<double> &rDiscountTimes,
                                  const std::vector<double> &rDiscountFactors,
                                  double dInitialTime, cfl::Fit &rFit,
                                  cfl::Function &rErr);

  /** @} */
}

#endif // of __home5_hpp__
