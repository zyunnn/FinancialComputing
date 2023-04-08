#ifndef __home6_hpp__
#define __home6_hpp__

/**
 * @file home6.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Homework 6: gaussian conditional expectation.
 * @version 0.1
 * @date 2021-03-16
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "cfl/GaussRollback.hpp"

/**
 * @mainpage Homework 6: conditional expectation for gaussian distribution.
 */

namespace prb
{

  /**
   * @defgroup Home6GaussRollback Gaussian conditional expectation.
   *
   * This module deals with implementation of conditional expectation with respect
   * to one-dimensional gaussian distribution.
   * @{
   */

  /**
   * Explicit finite-difference scheme.
   *
   * @param dP Equals \f$ \tau/(2h^2)\f$, where \f$\tau\f$ is the
   * time step and \f$h\f$ is the state step.
   * @return cfl::GaussRollback
   */
  cfl::GaussRollback expl(double dP = 1. / 3.);

  /**
   * Fully implicit finite-difference scheme.
   *
   * @param dP Equals \f$ \tau/(2h^2)\f$, where \f$\tau\f$ is the
   * time step and \f$h\f$ is the state step.
   * @return cfl::GaussRollback
   */
  cfl::GaussRollback impl(double dP = 1.);

  /**
   * Crank-Nicolson (symmetric) finite-difference scheme.
   *
   * @param dR Equals \f$ \tau/h\f$, where \f$\tau\f$ is the time
   * step and \f$h\f$ is the state step.
   * @return cfl::GaussRollback
   */
  cfl::GaussRollback crankNicolson(double dR = 1.);

  /**
   * Computation of gaussian conditional expectation with radix-2
   * FFT.  The grid needs to have \f$2^n\f$ nodes.
   *
   * @return cfl::GaussRollback
   */
  cfl::GaussRollback fft2();

  /**
   * Computation of gaussian conditional expectation with general
   * FFT. The algorithm runs efficiently if the numbers of nodes is
   * a product of 2,3, and 5.
   *
   * @return cfl::GaussRollback
   */
  cfl::GaussRollback fft();

  /**
   * A wrapper of "fast" scheme with explicit and implicit
   * schemes to improve the performance.
   *
   * @param iExplSteps The number of time steps of explicit scheme
   * used at the beginning to smooth boundary conditions.
   * @param rFast The main (fast) finite-difference scheme.
   * @param iImplSteps The number of time steps of fully implicit
   * scheme used at the end to filter round-off errors.
   * @param dExplP Equals \f$ \tau/(2h^2)\f$, where \f$\tau\f$ is
   * the time step in the explicit scheme and \f$h\f$ is the state
   * step.
   * @param dImplP Equals \f$ \tau/(2h^2)\f$, where \f$\tau\f$ is
   * the time step in the implicit scheme and \f$h\f$ is the state
   * step.
   * @return cfl::GaussRollback
   */
  cfl::GaussRollback chain(unsigned iExplSteps, const cfl::GaussRollback &rFast, unsigned iImplSteps,
                           double dExplP = 1. / 3., double dImplP = 1.);
  /** @} */
}

#endif // of __home6_hpp__
