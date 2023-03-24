#ifndef __cfl_Root_hpp__
#define __cfl_Root_hpp__

/**
 * @file Root.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Root finding with bracketing algorithm.
 * @version 1.0
 * @date 2022-02-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <vector>
#include <valarray>
#include "cfl/Function.hpp"

namespace cfl
{
  /**
   * @ingroup cflNumeric
   *
   * @defgroup cflRoot Root finding with bracketing algorithm.
   *
   * This module deals with bracketing algorithms for one-dimensional
   * root finding. These algorithms only require the computation of
   * function values.
   *
   * @{
   */
  /**
   * @brief Interface class for one-dimensional root finding with
   * bracketing algorithm.
   *
   * This is the abstract class for one-dimensional root finding with
   * bracketing algorithm. Its implementations are used to construct
   * concrete class Root.
   *
   * @see Root
   */
  class IRoot
  {
  public:
    /**
     * Virtual destructor.
     */
    virtual ~IRoot() {}

    /**
     * Returns the result of the one-dimensional root finding. We
     * supply the initial interval \a [dL,dR] for the search.
     *
     * @param rF The input function.
     * @param dL The left point of the search.
     * @param dR The right point of the search.
     * @return The argument \a dX such that \a rF(dX) is zero with the
     * accuracy defined by the search algorithm.
     */
    virtual double find(const cfl::Function &rF, double dL, double dR) const = 0;
  };

  /**
   * @brief Concrete class for one-dimensional root finding.
   *
   * This is the standard class for one-dimensional root finding. It
   * is implemented by a new instance of IRoot.
   *
   * @see  IRoot
   */
  class Root
  {
  public:
    /**
     * Constructs a one-dimensional root finding scheme from
     * an implementation of IRoot.
     *
     * @param pNewP A pointer to a new instance of IRoot.
     */
    explicit Root(IRoot *pNewP = 0);

    /**
     * @copydoc IRoot::find()
     */
    double find(const cfl::Function &rF, double dL, double dR) const;

  private:
    std::shared_ptr<IRoot> m_uP;
  };

  /** @} */
} // namespace cfl

#include "cfl/Inline/iRoot.hpp"
#endif // of __cfl_Root_hpp__
