#ifndef __cflData_hpp__
#define __cflData_hpp__

/**
 * @file Data.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Useful data structures.
 * @version 1.0
 * @date 2021-01-12
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "cfl/Function.hpp"

namespace cfl
{
  /**
   * @defgroup cflCommonElements Common elements of financial models.
   *
   * This module contains common elements of financial models.
   */

  /**
   * @ingroup cflCommonElements
   *
   * @defgroup cflData Data structures.
   *
   * This module contains useful functions and classes that facilitate
   * construction of models and derivatives.
   * @{
   */

  /**
   * @brief  Data structures.
   *
   * This namespace contains useful functions and classes that facilitate
   * construction of models and derivatives.
   */
  namespace Data
  {
    /**
     * Constructs discount curve. The discount factor for maturity
     * \f$t\f$ is given by
     * \f\[
     * D(t) = \exp(-\gamma (t-t_0)),
     * \f\]
     * where \f$\gamma=\f$ \p dYield and \f$t_0 = \f$ \p dInitialTime.
     *
     * @param dYield The constant continuously compounded yield.
     * @param dInitialTime The initial time as year fraction.
     *
     * @return The discount curve as a function of maturity.
     */
    Function discount(double dYield, double dInitialTime);

    /**
     * Constructs discount curve. The discount factor for maturity
     * \f$t\f$ is given by
     * \f\[
     * D(t) = \exp(-\Gamma(t) (t-t_0)),
     * \f\]
     * where \f$\Gamma =\f$ \p rYield (the yield curve) and \f$t_0 = \f$ \p dInitialTime.
     *
     * @param rYield The continuously compounded yield curve.
     * @param dInitialTime The initial time as year fraction.
     *
     * @return The discount curve as function of maturity.
     */
    Function discount(const Function &rYield, double dInitialTime);

    /**
     * Constructs stationary volatility curve. The value of volatility
     * at time \f$t\f$ is given by
     * \f\[
     * V(t) = \sigma \sqrt{\frac{\exp(2\lambda (t-t_0))-1}{2\lambda (t-t_0)}},
     * \f\]
     * where \f$\sigma=\f$ \p dSigma, \f$\lambda=\f$ \p dLambda,
     * and \f$t_0 = \f$ \p dInitialTime.
     *
     * @param dSigma The short-term volatility
     * @param dLambda The mean-reversion coefficient.
     * @param dInitialTime The initial time as year fraction.
     *
     * @return The stationary volatility curve.
     */
    Function volatility(double dSigma, double dLambda, double dInitialTime);

    /**
     * Constructs forward curve for a stock. The forward price at
     * at time \f$t\f$ is given by
     * \f\[
     * F(t) = S(t_0) \exp(c(t-t_0)),
     * \f\]
     * where \f$S(t_0) = \f$ \p dSpot, \f$c=\f$ \p dCostOfCarry,
     * and \f$t_0 = \f$ \p dInitialTime.
     *
     * @param dSpot The spot price.
     * @param dCostOfCarry The cost-of-carry rate.
     * @param dInitialTime The initial time as year fraction.
     *
     * @return The forward curve computed by cost-of-carry formula.
     */
    Function forward(double dSpot, double dCostOfCarry, double dInitialTime);

    /**
     * Constructs forward curve for a stock. The forward price at
     * at time \f$t\f$ is given by
     * \f\[
     * F(t) = S(t_0) \exp(C(t)(t-t_0)),
     * \f\]
     * where \f$S(t_0) = \f$ \p dSpot, \f$C=\f$ \p rCostOfCarry,
     * and \f$t_0 = \f$ \p dInitialTime.
     *
     * @param dSpot The spot price.
     * @param rCostOfCarry The cost-of-carry rate curve.
     * @param dInitialTime The initial time as year fraction.
     *
     * @return The forward curve computed by cost-of-carry formula.
     */
    Function forward(double dSpot, const Function &rCostOfCarry,
                     double dInitialTime);

    /**
     * Constructs forward curve for a stock. The forward price at
     * at time \f$t\f$ is given by
     * \f\[
     * F(t) = S(t_0) \exp(-q(t-t_0))/D(t),
     * \f\]
     * where \f$S(t_0) = \f$ \p dSpot, \f$q=\f$ \p dDividendYield,
     * \f$D(t) = \f$ \p rDiscount, and \f$t_0 = \f$ \p dInitialTime.
     *
     * @param dSpot The spot price.
     * @param dDividendYield The convenenience or dividend rate.
     * @param rDiscount The discount curve.
     * @param dInitialTime The initial time as year fraction.
     *
     * @return The forward curve computed by cost-of-carry formula.
     */
    Function forward(double dSpot, double dDividendYield,
                     const Function &rDiscount, double dInitialTime);

    /**
     * @brief  Cash flow at fixed rate over regular time intervals.
     *
     * This class describes the cash flow which takes place
     * at a given fixed interest rate and at regular time intervals.
     * \code coupon = notional * rate * period \endcode
     *
     * @see Swap
     */
    class CashFlow
    {
    public:
      /**
       * The notional amount.
       */
      double notional;

      /**
       * The fixed interest rate.
       */
      double rate;

      /**
       * The interval between two payments as year fraction.
       */
      double period;

      /**
       * The total number of payments.
       */
      unsigned numberOfPayments;
    };

    /**
     * @brief  Interest rate swap.
     *
     * This class describes the parameters of interest rate
     * swap. One side makes fixed payments according to
     * simple fixed CashFlow and another side makes float payments
     * according to the market (LIBOR) interest rate.
     *
     * @see CashFlow
     */
    class Swap : public CashFlow
    {
    public:
      /**
       * Default constructor.
       */
      Swap(){};

      /**
       * Constructs the interest rate swap from
       * the class CashFlow and determines the side of the
       * contract by \p bPayFloat.
       *
       * @param rCashFlow A constant reference to CashFlow
       * @param bPayFloat A side of the contract. If \p true
       * then we pay float and receive fixed, if  \p false
       * then otherwise.
       */
      Swap(const CashFlow &rCashFlow, bool bPayFloat = true);

      /**
       * The side of the contract. If <code>payFloat = true</code>, then
       * we pay float and receive fixed. If <code>payFloat = false</code>, then
       * we pay fixed and receive float.
       */
      bool payFloat;
    };

    /**
     * The parameters of traded options.
     */
    class Option
    {
    public:
      /**
       * The number of options.
       */
      double number;

      /**
       * The absolute maturity.
       */
      double maturity;

      /**
       * The strike.
       */
      double strike;
    };
  } // namespace Data
  /** @} */
} // namespace cfl

#endif // of __cflData_hpp__
