#ifndef __cflMacros_hpp__
#define __cflMacros_hpp__

/**
 * @file Macros.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Macros for cfl library.
 * @version 1.0
 * @date 2021-01-12
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <assert.h>
#include <algorithm>

/**
 * @ingroup cflMisc
 *
 * @defgroup cflMacros Macros and constants.
 *
 * This module contains macros and constants for cfl library.
 * @{
 */

/**
 * Checks the validity of input parameters.
 *
 */
#define PRECONDITION assert

/**
 * Checks the validity of parameters in the middle
 * of an implementation.
 *
 */
#define ASSERT assert

/**
 * Checks the validity of output parameters.
 *
 */
#define POSTCONDITION assert
/** @} */

namespace cfl
{
  /**
   * @ingroup cflMacros
   * @{
   *
   * Constant for a tiny but nonzero positive quantity
   * like one millisecond in a year or a smallest safe divider.
   *
   */
  const double EPS = 1E-10;

  /**
   * Constant for the maximal number of iterations in some numerical routines such as root searching.
   *
   */
  const unsigned IMAX = 1000;
  /** @} */
} // namespace cfl

#endif //__cflMacros_hpp__
