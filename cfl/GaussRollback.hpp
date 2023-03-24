#ifndef __cflGaussRollback_hpp__
#define __cflGaussRollback_hpp__

/**
 * @file GaussRollback.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Conditional expectation with respect to gaussian distribution.
 * @version 1.0
 * @date 2021-01-12
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <valarray>
#include <memory>
#include "Macros.hpp"

namespace cfl
{
  /**
   * @ingroup cflNumeric
   *
   * @defgroup cflGaussRollback Gaussian conditional expectation.
   *
   * This module deals with implementation of conditional expectation with respect
   * to one-dimensional gaussian distribution.
   * @{
   */

  /**
   * @brief  Interface class for the operator of conditional
   * expectation with respect to gaussian distribution.
   *
   * An implementation of the interface class IGaussRollback is used
   * to construct concrete class GaussRollback.
   *
   * @see GaussRollback and NGaussRollback
   */
  class IGaussRollback
  {
  public:
    /**
     * Virtual destructor.
     */
    virtual ~IGaussRollback() {}

    /**
     * Virtual constructor.
     * Constructs the numerical scheme that implements the operator of
     * conditional expectation with respect to the gaussian
     * distribution with mean 0 and variance \p dVar on the grid with
     * step \p dH and size \p iSize.
     *
     * @param iSize The number of points on the grid.
     * @param dH The distance between the points on the grid.
     * @param dVar The variance of the gaussian distribution.
     * @return A pointer to new implementation of IGaussRollback.
     */
    virtual IGaussRollback *newObject(unsigned iSize, double dH, double dVar) const = 0;

    /**
     * Implements the operator of conditional expectation with
     * respect to gaussian distribution.
     *
     * @param rValues \em Before \p rollback this array contains the
     * original values of the function.  \em After \p rollback, it
     * contains their conditional expectations with respect to the
     * gaussian distribution.
     */
    virtual void rollback(std::valarray<double> &rValues) const = 0;
  };

  /**
   * @brief Concrete class for the operator of conditional expectation
   * with respect to gaussian distribution.
   *
   * This is the concrete class for numerical implementations of the
   * operator of conditional expectation with respect to gaussian
   * distribution. It is constructed by a dynamically allocated
   * implementation of the interface class IGaussRollback.
   *
   * @see IGaussRollback and NGaussRollback
   */
  class GaussRollback
  {
  public:
    /**
     * Constructs a numerical engine that computes conditional
     * expectations with respect to gaussian distribution.
     *
     * @param pNewP Pointer to new implementation of IGaussRollback.
     */
    explicit GaussRollback(IGaussRollback *pNewP = 0);

    /**
     * Resets the parameters of the current GaussRollback object.
     * Constructs a numerical engine that computes the conditional
     * expectation with respect to the gaussian distribution with mean
     * 0 and variance \p dVar on the grid with step \p dH and size \p
     * iSize.
     *
     * @param iSize The number of points on the grid.
     * @param dH The distance between the points on the grid.
     * @param dVar The variance of the gaussian distribution.
     */
    void assign(unsigned iSize, double dH, double dVar);

    /**
     * @copydoc IGaussRollback::rollback()
     */
    void rollback(std::valarray<double> &rValues) const;

    /**
     * Rollback operator that also computes the first
     * derivatives with respect to the state variable.
     * The first derivatives are computed using the integration by
     * parts formula. In total, rollback runs twice.
     *
     * @param rValues \em Before \p rollback this array contains the
     * original values of the function.  \em After \p rollback, it
     * contains their conditional expectations with respect to the
     * gaussian distribution.
     * @param rDelta Returns the values of the first derivatives of
     * the conditional expectation with respect to the state variable.
     */
    void rollback(std::valarray<double> &rValues, std::valarray<double> &rDelta) const;

    /**
     * Rollback operator that also computes the first and
     * second derivatives with respect to the state variable.
     * The first and second derivatives are computed using the
     * integration by parts formula. In total, the rollback runs 3
     * times.
     *
     * @param rValues \em Before \p rollback this array contains the
     * original values of the function.  \em After \p rollback, it
     * contains their conditional expectations with respect to the
     * gaussian distribution.
     * @param rDelta Returns the values of the first derivatives of
     * the conditional expectation with respect to the state variable.
     * @param rGamma Returns the values of the second derivatives of
     * the conditional expectation with respect to the state variable.
     */
    void rollback(std::valarray<double> &rValues, std::valarray<double> &rDelta,
                  std::valarray<double> &rGamma) const;

    /**
     * Computes the derivative with respect to the standard deviation
     * from the second derivative with respect to the state variable.
     *
     * @param rGammaToVega Before \p vega this parameter represents
     * the second derivative with respect to state variable. After \p
     * vega it is replaced with the first derivative with respect to
     * the standard deviation.
     */
    void vega(std::valarray<double> &rGammaToVega) const;

  private:
    std::shared_ptr<IGaussRollback> m_uP;
    double m_dH, m_dVar;
    unsigned m_iSize;
  }; /** @} */
} // namespace cfl

#include "cfl/Inline/iGaussRollback.hpp"
#endif // of __cflGaussRollback_hpp__
