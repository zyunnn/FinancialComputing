#ifndef __cflMultiFunction_hpp__
#define __cflMultiFunction_hpp__

/**
 * @file MultiFunction.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Multi-dimensional function object.
 * @version 1.0
 * @date 2021-01-12
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <cmath>
#include <vector>
#include <valarray>
#include "cfl/Function.hpp"

namespace cfl
{
  /**
   * @ingroup cflFunctionObjects
   *
   * @defgroup cflMultiFunction Multi-dimensional function object.
   *
   * This module deals with multi-dimensional function object.
   * @{
   */

  /**
   * @brief  Interface for multi-dimensional function.
   *
   * Abstract class for multi-dimensional function. Its implementation
   * is used to construct concrete class MultiFunction.
   *
   * @see MultiFunction
   */
  class IMultiFunction
  {
  public:
    /**
     * Virtual destructor.
     */
    virtual ~IMultiFunction(){};

    /**
     * Standard functional operator.
     *
     * @param rX The argument of the function. The size of this array
     * should equal the dimension of the domain.
     * @return The value of the function at \p rX.
     */
    virtual double operator()(const std::valarray<double> &rX) const = 0;

    /**
     * Tests whether an argument belongs to the domain of the function.
     *
     * @param rX The argument of the function. The size of this array
     * should equal the dimension of the domain.
     * @return The function returns \p true if the argument \p dX belongs
     * to its domain and returns \p false otherwise.
     */
    virtual bool belongs(const std::valarray<double> &rX) const = 0;

    /**
     * The dimension of the domain of the function.
     *
     * @return The dimension of the domain of the function.
     */
    virtual unsigned dim() const = 0;
  };

  /**
   * @brief  Concrete class for a multi-dimensional function.
   *
   * The standard class for a multi-dimensional function. It is
   * constructed from a new implementation of IMultiFunction.
   *
   * @see IMultiFunction
   */
  class MultiFunction
  {
  public:
    /**
     * Constructs constant function with value \p dV on the space with
     * dimension \p iDim.
     *
     * @param dV The value of the function.
     * @param iDim The dimension of the domain.
     */
    explicit MultiFunction(double dV = 0., unsigned iDim = 1);

    /**
     * Constructs \p *this from a new implementation of IMultiFunction.
     *
     * @param pNewF The pointer to a new implementation of IMultiFunction.
     */
    explicit MultiFunction(IMultiFunction *pNewF);

    /**
     * Constructs \p MultiFunction from a standard function object of STL.
     * The domain is given by the whole space.
     *
     * @param rF The constant reference to the function object.
     * A copy of \p rF is created inside of \p *this.
     * @param iDim The dimension of the domain.
     */
    explicit MultiFunction(const std::function<double(const std::valarray<double> &)> &rF,
                           unsigned iDim);

    /**
     * Constructs \p MultiFunction from a pair of standard function objects of STL.
     *
     * @param rF The constant reference to the function object.
     * A copy of \p rF is created inside of \p *this.
     * @param rBelongs The constant reference to the domain descriptor.
     * A copy of \p rBelongs is created inside of \p *this.
     * @param iDim The dimension of the domain.
     */
    MultiFunction(const std::function<double(const std::valarray<double> &)> &rF,
                  const std::function<bool(const std::valarray<double> &)> &rBelongs,
                  unsigned iDim);

    /**
     * Assigns to \p *this the constant function with the value \p dV.
     * The dimension of the function does not change. The domain is given by
     * the whole space.
     *
     * @param dV The value of the function.
     * @return Reference to \p *this.
     */
    MultiFunction &operator=(double dV);

    /**
     * Returns the value of the function for given argument.
     *
     * @param rX The argument of the function. The size of this array
     * should equal the dimension of the domain.
     * @return The value of \p *this at \p rX.
     */
    double operator()(const std::valarray<double> &rX) const;

    /**
     * @copydoc IMultiFunction::belongs
     */
    bool belongs(const std::valarray<double> &rX) const;

    /**
     * @copydoc IMultiFunction::dim
     */
    unsigned dim() const;

    /**
     * Replaces \p *this with the sum of \p *this and \p rF.  The new
     * domain of \p *this is the intersection of its old domain
     * with the domain of \p rF.  A copy of \p rF is created
     * inside of \p *this.
     *
     * @param rF Constant reference to the addend. The domain of \p rF
     * should have the same dimension as the domain of \p *this.
     * @return Reference to \p *this.
     */
    MultiFunction &operator+=(const MultiFunction &rF);

    /**
     * Replaces \p *this with the product of \p *this and \p rF.  The
     * new domain of \p *this is the intersection of its old
     * domain with the domain of \p rF.  A copy of \p rF is
     * created inside of \p *this.
     *
     * @param rF Constant reference to the multiplier. The domain of
     * \p rF should have the same dimension as the domain of \p *this.
     * dimension of \p *this.
     * @return Reference to \p *this.
     */
    MultiFunction &operator*=(const MultiFunction &rF);

    /**
     * Replaces \p *this with the difference between \p *this and \p
     * rF.  The new domain of \p *this is the intersection of its
     * old domain with the domain of \p rF.  A copy of \p rF is
     * created inside of \p *this.
     *
     * @param rF Constant reference to the subtrahend. The domain of \p
     * rF should have the same dimension as the domain of \p *this.
     * @return Reference to \p *this.
     */
    MultiFunction &operator-=(const MultiFunction &rF);

    /**
     * Replaces \p *this with the ratio of \p *this and \p rF.  The
     * new domain of \p *this is the intersection of its old
     * domain with the domain of \p rF.  A copy of \p rF is
     * created inside of \p *this.
     *
     * @param rF Constant reference to the divisor.  The domain of \p
     * rF should have the same dimension as the domain of \p *this.
     * @return Reference to \p *this.
     */
    MultiFunction &operator/=(const MultiFunction &rF);

    /**
     * Replaces \p *this with the sum of \p *this and \p dV.
     *
     * @param dV The number to be added to the function.
     * @return Reference to \p *this.
     */
    MultiFunction &operator+=(double dV);

    /**
     * Replaces \p *this with the difference between \p *this and \p
     * dV.
     *
     * @param dV The number to be subtracted from the function.
     * @return Reference to \p *this.
     */
    MultiFunction &operator-=(double dV);

    /**
     * Replaces \p *this with the product of \p *this and \p dV.
     *
     * @param dV The number to be multiplied by the function.
     * @return Reference to \p *this.
     */
    MultiFunction &operator*=(double dV);

    /**
     * Replaces \p *this with the ratio of \p *this and \p dV.
     *
     * @param dV The divisor number.
     * @return Reference to \p *this.
     */
    MultiFunction &operator/=(double dV);

  private:
    std::shared_ptr<IMultiFunction> m_pF;
  };

  /**
   * Returns the composition function \p rOp(rF).
   * The result contains copies of \p rF and \p rOp.
   *
   * @param rF A function.
   * @param rOp A unary operator.
   * @return The composition function \p rF(*this)
   */
  MultiFunction apply(const MultiFunction &rF, const std::function<double(double)> &rOp);

  /**
   * Returns the composition function \p rOp(rF,rG). The result contains
   * copies of \p rF,  \p rG, and \p rOp. The domain of the result is
   * the intersection of the domains of \p rF and \p rG.
   *
   * @param rF First function.
   * @param rG Second function.
   * @param rOp A binary operator.
   * @return The composition function \p rOp(rF,rG).
   */
  MultiFunction apply(const MultiFunction &rF, const MultiFunction &rG,
                      const std::function<double(double, double)> &rOp);

  /**
   * Returns minus \p rF. The result contains copy of \p rF.
   * The domain of the result is the domain of \p rF.
   *
   * @param rF The function whose minus is computed.
   * @return The function given by <code>-rF</code>
   */
  MultiFunction operator-(const MultiFunction &rF);

  /**
   * Returns the sum of \p rF and \p rG.  The result contains
   * copies of \p rF and \p rG.  The domain of the result is
   * the intersection of the domains of \p rF and \p rG.
   *
   * @param rF First addend function.
   * @param rG Second addend function.
   * @return The function given by <code>rF+rG</code>
   */
  MultiFunction
  operator+(const MultiFunction &rF, const MultiFunction &rG);

  /**
   * Returns the sum of \p rF and \p dV.  The result contains a
   * copy of \p rF.  The domain of the result is that of \p rF.
   *
   * @param rF The function-term of the sum.
   * @param dV The number-term of the sum.
   * @return The function given by <code>rF+dV</code>.
   */
  MultiFunction
  operator+(const MultiFunction &rF, double dV);

  /**
   * Returns the  sum of \p dV and \p rF. The result
   * contains a copy of \p rF.  The domain of the
   * result is that of \p rF.
   *
   * @param dV The number-term of the sum.
   * @param rF The function-term of the sum.
   * @return The function given by <code>dV+rF</code>
   */
  MultiFunction
  operator+(double dV, const MultiFunction &rF);

  /**
   * Returns the difference between \p rF and \p rG.  The result
   * contains  copies of \p rF and \p rG.  The domain of the
   * result is the intersection of the domains of \p rF and \p rG.
   *
   * @param rF The minuend function.
   * @param rG The subtrahend function.
   * @return The function given by <code>rF-rG</code>
   */
  MultiFunction
  operator-(const MultiFunction &rF, const MultiFunction &rG);

  /**
   * Returns the difference between \p rF and \p dV.  The result
   * contains a copy of \p rF.  The domain of the result is
   * that of \p rF.
   *
   * @param rF The minuend function.
   * @param dV The subtrahend number.
   * @return The function given by <code>rF-dV</code>.
   */
  MultiFunction
  operator-(const MultiFunction &rF, double dV);

  /**
   * Returns the difference between \p dV and \p rF. The result
   * contains a copy of \p rF. The domain of the result is
   * that of \p rF.
   *
   * @param dV The minuend number.
   * @param rF The subtrahend function.
   * @return The function given by <code>dV-rF</code>
   */
  MultiFunction
  operator-(double dV, const MultiFunction &rF);

  /**
   * Returns the product of \p rF and \p rG.  The result contains
   * copies of \p rF and \p rG.  The domain of the result is the
   * intersection of the domains of \p rF and \p rG.
   *
   * @param rF First multiplier function.
   * @param rG Second multiplier function.
   * @return The function given by <code>rF*rG</code>
   */
  MultiFunction
  operator*(const MultiFunction &rF, const MultiFunction &rG);

  /**
   * Returns the product of \p rF and \p dV.  The result contains a
   * copy of \p rF.  The domain of the result is that of \p
   * rF.
   *
   * @param rF The multiplier function.
   * @param dV The multiplier number.
   * @return The function given by <code>rF*dV</code>.
   */
  MultiFunction
  operator*(const MultiFunction &rF, double dV);

  /**
   * Returns the product of \p dV and \p rF. The result contains a
   * copy of \p rF.  The domain of the result is that of \p
   * rF.
   *
   * @param dV The multiplier number.
   * @param rF The multiplier function.
   * @return The function given by <code>dV*rF</code>
   */
  MultiFunction
  operator*(double dV, const MultiFunction &rF);

  /**
   * Returns the ratio of \p rF and \p rG.  The result contains
   * copies of \p rF and \p rG.  The domain of the result is the
   * intersection of the domains of \p rF and \p rG.
   *
   * @param rF The dividend function.
   * @param rG The divisor function.
   * @return The function given by <code>rF/rG</code>
   */
  MultiFunction
  operator/(const MultiFunction &rF, const MultiFunction &rG);

  /**
   * Returns the ratio of \p rF and \p dV.  The result contains a
   * copy of \p rF.  The domain of the result is that of \p rF.
   *
   * @param rF The dividend function.
   * @param dV The divisor number.
   * @return The function given by <code>rF/dV</code>.
   */
  MultiFunction
  operator/(const MultiFunction &rF, double dV);

  /**
   * Returns the ratio of \p dV and \p rF. The result contains a
   * copy of \p rF.  The domain of the result is that of \p rF.
   *
   * @param dV The dividend number.
   * @param rF The divisor function.
   * @return The function given by <code>dV/rF</code>
   */
  MultiFunction
  operator/(double dV, const MultiFunction &rF);

  /**
   * Returns \p rF in the power \p dV.  The result contains a
   * copy of \p rF.  The domain of the result is that of \p rF.
   *
   * @param rF The function-base.
   * @param dV The number-exponent.
   * @return The function \p rF in the power \p dV.
   */
  MultiFunction pow(const MultiFunction &rF, double dV);

  /**
   * Returns the absolute value of \p rF.  The result contains a
   * copy of \p rF.  The domain of the result is that of \p rF.
   *
   * @param rF The function whose absolute value is computed.
   * @return The absolute value of \p rF.
   */
  MultiFunction abs(const MultiFunction &rF);

  /**
   * Returns the exponent of \p rF.  The result contains copy
   * of \p rF. The domain of the result is that of \p rF.
   *
   * @param rF The function whose exponent is computed.
   * @return The exponent of  \p rF.
   */
  MultiFunction exp(const MultiFunction &rF);

  /**
   * Returns the logarithm of \p rF.  The result contains copy
   * of \p rF. The domain of the result is that of \p rF.
   *
   * @param rF The function whose logarithm is computed.
   * @return The logarithm of  \p rF.
   */
  MultiFunction log(const MultiFunction &rF);

  /**
   * Returns the squire root of \p rF.  The result contains the a
   * copy of \p rF. The domain of the result is that of \p rF.
   *
   * @param rF The function whose square root is computed.
   * @return The square root of  \p rF.
   */
  MultiFunction sqrt(const MultiFunction &rF);

  class Function;

  /**
   * Adapter of a one-dimensional function to a multi-dimensional function.
   *
   * @param rF The constant reference to a one-dimensional function object.
   * @param iDim The dimension of the domain of the result.
   * @param iArg The index of the coordinate used as an argument of
   * the function \p rF to compute the value of the result.
   * @return The function with dimension \p iDim whose value at a
   * vector with size \p iDim equals the value of \p rF at the element
   * of this vector with index \p iArg.
   */
  MultiFunction toMultiFunction(const Function &rF, unsigned iArg,
                                unsigned iDim);

  /**
   * Constrains multi-dimensional function to a domain of smaller dimension.
   *
   * @param rF The input multi-dimensional function.
   * @param rArg The vector of arguments of the flexible coordinates.
   * @param rOtherArg The values of fixed coordinates.
   * @return The restriction of function \p rF on the points where the
   * coordinates with indexes \p rArg are flexible and the other
   * coordinates are fixed and equal \p rOtherArg. The sum of sizes of
   * \p rArg and \p rOtherArg should equal the dimension of \p rF. The
   * dimension of the result equals the the size of rArg.
   */
  MultiFunction toMultiFunction(const MultiFunction &rF,
                                const std::vector<unsigned> &rArg,
                                const std::valarray<double> &rOtherArg);
  /**
   * Returns the restriction of the multi-dimensional function \p rF
   * to the one-dimensional region defined as the intersection of the
   * domain of \p rF with the line where the coordinate with index
   * \p iArg is flexible and all other coordinates equal \p rOtherArg .
   *
   * @param rF Constant reference to a multi-dimensional function object.
   * @param iArg The index of flexible coordinate.
   * @param rOtherArg The values of fixed coordinates.
   * @return A standard one-dimensional function object in the library
   *  representing the restriction of the multi-dimensional function
   *  \p rF to a one-dimensional domain.
   */
  Function toFunction(const MultiFunction &rF,
                      unsigned iArg = 0,
                      const std::valarray<double> &rOtherArg = std::valarray<double>());

  /** @} */
} // namespace cfl

#include "cfl/Inline/iMultiFunction.hpp"
#endif // of __cflMultiFunction_hpp__
