#ifndef __test_all_Black_h__
#define __test_all_Black_h__

/**
 * @file Black.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Testing of Black models.
 * @version 1.0
 * @date 2021-01-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "test/Print.hpp"
#include "cfl/Data.hpp"

namespace test
{
  /**
   * @brief Testing in Black model.
   *
   */
  namespace Black
  {
    /**
     *
     * @defgroup test_all_Black Testing in Black model.
     *
     * This module contains testing functions for
     * the Black model on a single stock.
     *
     * @{
     */

    /**
     * The default interest rate.
     *
     */
    const double c_dYield = 0.07;

    /**
     * The default spot price.
     *
     */
    const double c_dSpot = 100;

    /**
     * The default dividend yield.
     *
     */
    const double c_dDividendYield = 0.02;

    /**
     * The default volatility of spot prices.
     *
     */
    const double c_dSigma = 0.2;

    /**
     * The default mean-reversion rate.
     *
     */
    const double c_dLambda = 0.05;

    /**
     * The default initial time.
     *
     */
    const double c_dInitialTime = 0;

    /**
     * The default maturity.
     *
     */
    const double c_dMaturity = c_dInitialTime + 0.5;

    /**
     * The default notional.
     *
     */
    const double c_dNotional = 100.;

    /**
     * The default interval for relative changes in the initial spot price.
     *
     */
    const double c_dInterval = 0.2;

    /**
     * The default number of values in the output.
     *
     */
    const unsigned c_iPoints = 10;
    /** @} */
  } // namespace Black
} // namespace test

#endif // of __test_all_Black_h__
