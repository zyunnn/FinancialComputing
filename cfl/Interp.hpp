#ifndef __cflInterp_hpp__
#define __cflInterp_hpp__

/**
 * @file Interp.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Interpolation of one-dimensional functions.
 * @version 1.0
 * @date 2021-01-12
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <vector>
#include "cfl/Function.hpp"

namespace cfl
{
  /**
   * @ingroup cflNumeric
   *
   * @defgroup cflInterp Interpolation of one-dimensional functions.
   *
   * This module deals with one-dimensional interpolation.
   * @{
   */

  /**
   * @brief  Interface class for numerical interpolation.
   *
   * This is the interface class for one-dimensional interpolation. Its implementation
   * is used to construct concrete class Interp.
   *
   * @see Interp and NInterp
   */
  class IInterp
  {
  public:
    /**
     * Virtual destructor.
     */
    virtual ~IInterp() {}

    /**
     * Interpolation of the data supplied by the vectors of arguments
     * \p rArg and values \p rVal.
     *
     * @param rArg The strictly increasing vector of arguments.
     * @param rVal The vector of values.
     * @return Interpolated function.
     */
    virtual Function interpolate(const std::vector<double> &rArg,
                                 const std::vector<double> &rVal) const = 0;
  };

  /**
   * @brief  Concrete class for one-dimensional interpolation.
   *
   * This is the standard class for one-dimensional interpolation.
   * It is constructed from a new implementation of IInterp.
   *
   * @see IInterp and NInterp
   */
  class Interp
  {
  public:
    /**
     * A constructor.
     * @param pNewP A dynamically allocated implementation of IInterp.
     */
    explicit Interp(IInterp *pNewP = 0);

    /**
     * Returns interpolated function for given arguments and values.
     *
     * @param itArgBegin The iterator to the start of the container of arguments.
     * @param itArgEnd The iterator to the end of the container of arguments.
     * @param itValBegin The iterator to the start of the container of values.
     *
     * @return Interpolated function.
     */
    template <class It1, class It2>
    cfl::Function interpolate(It1 itArgBegin, It1 itArgEnd,
                              It2 itValBegin) const;

  private:
    std::shared_ptr<IInterp> m_uP;
  };

  /**
   * @brief Implementations of one-dimensional interpolations.
   *
   * @see IInterp and Interp
   */
  namespace NInterp
  {
    /**
     * Linear interpolation.
     *
     * @return The engine for linear interpolation.
     */
    cfl::Interp linear();
  } // namespace NInterp
  /** @} */
} // namespace cfl

#include "cfl/Inline/iInterp.hpp"
#endif // of __cflInterp_hpp__
