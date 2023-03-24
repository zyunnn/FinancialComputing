#ifndef __test_all_HullWhite_h__
#define __test_all_HullWhite_h__

/**
 * @file HullWhite.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Testing of Hull and White models.
 * @version 1.0
 * @date 2021-01-18
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "test/Print.hpp"

namespace test
{
  /**
   * @brief Testing in Hull and White model.
   *
   */
  namespace HullWhite
  {
    /**
     *
     * @defgroup test_all_HW Testing in Hull and White model.
     *
     * This module contains testing functions for the
     * Hull and White model of interest rates.
     *
     * @{
     */

    /**
     * The default interest rate.
     *
     */
    const double c_dYield = 0.07;

    /**
     * The default volatility of short-term interest rate.
     *
     */
    const double c_dHullWhiteSigma = 0.02;

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
     * The default maturity for an option.
     *
     */
    const double c_dMaturity = c_dInitialTime + 1.5;

    /**
     * The default notional.
     *
     */
    const double c_dNotional = 1000.;

    /**
     * The default interval between two payments.
     *
     */
    const double c_dPeriod = 0.25;

    /**
     * The default number of payments.
     *
     */
    const unsigned c_iNumberOfPeriods = 6;

    /**
     * Returns some default vector of exercise times.
     *
     * @return std::vector<double>
     */
    std::vector<double> exerciseTimes();

    /**
     * Returns some default vector of barrier times.
     *
     * @return std::vector<double>
     */
    std::vector<double> barrierTimes();

    /**
     * Returns some default parameters for an interest rate swap.
     *
     * @return cfl::Data::Swap
     */
    cfl::Data::Swap swapParameters();

    /**
     * The interval of initial values for short-term rates.
     *
     */
    const double c_dInterval = 0.2;

    /**
     * The number of points in the output.
     *
     */
    const unsigned c_iPoints = 10;
    /** @} */
  } // namespace HullWhite
} // namespace test

#include "test/Inline/iHullWhite.hpp"
#endif // of __test_all_HullWhite_h__
