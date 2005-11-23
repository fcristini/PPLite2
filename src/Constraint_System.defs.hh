/* Constraint_System class declaration.
   Copyright (C) 2001-2005 Roberto Bagnara <bagnara@cs.unipr.it>

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

The PPL is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#ifndef PPL_Constraint_System_defs_hh
#define PPL_Constraint_System_defs_hh 1

#include "Constraint_System.types.hh"
#include "Linear_Expression.types.hh"
#include "Linear_System.defs.hh"
#include "Generator.types.hh"
#include "Polyhedron.types.hh"
#include "Constraint.types.hh"
#include <iterator>
#include <iosfwd>

namespace Parma_Polyhedra_Library {

namespace IO_Operators {

//! Output operator.
/*!
  \relates Parma_Polyhedra_Library::Constraint_System
  Writes <CODE>true</CODE> if \p cs is empty.  Otherwise, writes on
  \p s the constraints of \p cs, all in one row and separated by ", ".
*/
std::ostream& operator<<(std::ostream& s, const Constraint_System& cs);

} // namespace IO_Operators

// Put it in the namespace here to declare it friend later.
/*! \relates Polyhedron */
bool operator==(const Polyhedron& x, const Polyhedron& y);

} // namespace Parma_Polyhedra_Library


namespace std {

//! Specializes <CODE>std::swap</CODE>.
/*! \relates Parma_Polyhedra_Library::Constraint_System */
void swap(Parma_Polyhedra_Library::Constraint_System& x,
	  Parma_Polyhedra_Library::Constraint_System& y);

} // namespace std

//! A system of constraints.
/*!
    An object of the class Constraint_System is a system of constraints,
    i.e., a multiset of objects of the class Constraint.
    When inserting constraints in a system, space dimensions are
    automatically adjusted so that all the constraints in the system
    are defined on the same vector space.

    \par
    In all the examples it is assumed that variables
    <CODE>x</CODE> and <CODE>y</CODE> are defined as follows:
    \code
  Variable x(0);
  Variable y(1);
    \endcode

    \par Example 1
    The following code builds a system of constraints corresponding to
    a square in \f$\Rset^2\f$:
    \code
  Constraint_System cs;
  cs.insert(x >= 0);
  cs.insert(x <= 3);
  cs.insert(y >= 0);
  cs.insert(y <= 3);
    \endcode
    Note that:
    the constraint system is created with space dimension zero;
    the first and third constraint insertions increase the space
    dimension to \f$1\f$ and \f$2\f$, respectively.

    \par Example 2
    By adding four strict inequalities to the constraint system
    of the previous example, we can remove just the four
    vertices from the square defined above.
    \code
  cs.insert(x + y > 0);
  cs.insert(x + y < 6);
  cs.insert(x - y < 3);
  cs.insert(y - x < 3);
    \endcode

    \par Example 3
    The following code builds a system of constraints corresponding to
    a half-strip in \f$\Rset^2\f$:
    \code
  Constraint_System cs;
  cs.insert(x >= 0);
  cs.insert(x - y <= 0);
  cs.insert(x - y + 1 >= 0);
    \endcode

    \note
    After inserting a multiset of constraints in a constraint system,
    there are no guarantees that an <EM>exact</EM> copy of them
    can be retrieved:
    in general, only an <EM>equivalent</EM> constraint system
    will be available, where original constraints may have been
    reordered, removed (if they are trivial, duplicate or
    implied by other constraints), linearly combined, etc.
*/
class Parma_Polyhedra_Library::Constraint_System : private Linear_System {
public:
  //! Default constructor: builds an empty system of constraints.
  Constraint_System();

  //! Builds the singleton system containing only constraint \p c.
  explicit Constraint_System(const Constraint& c);

  //! Ordinary copy-constructor.
  Constraint_System(const Constraint_System& cs);

  //! Destructor.
  ~Constraint_System();

  //! Assignment operator.
  Constraint_System& operator=(const Constraint_System& y);

  //! Returns the maximum space dimension a Constraint_System can handle.
  static dimension_type max_space_dimension();

  //! Returns the dimension of the vector space enclosing \p *this.
  dimension_type space_dimension() const;

  //! \brief
  //! Returns <CODE>true</CODE> if and only if \p *this
  //! contains one or more strict inequality constraints.
  bool has_strict_inequalities() const;

  //! \brief
  //! Removes all the constraints from the constraint system
  //! and sets its space dimension to 0.
  void clear();

  //! \brief
  //! Inserts in \p *this a copy of the constraint \p c,
  //! increasing the number of space dimensions if needed.
  void insert(const Constraint& c);

  //! \brief
  //! Applies the primal simplex algorithm so as to optimize the value
  //! of the objective function \p expr on the system of constraints.
  /*!
    \return
    A Simplex_Status flag indicating the outcome of the optimization
    attempt (unfeasible, unbounded or solved problem).

    \param expr
    The objective function to be optimized.

    \param kind
    The kind of optimization requested.

    \param ext_n
    On exit, if the problem has been solved, will contain the numerator
    of the optimal value for \p expr.

    \param ext_d
    On exit, if the problem has been solved, will contain the denominator
    of the optimal value for \p expr.

    \param optimizing_point
    On exit, if the problem has been solved, will contain a feasible
    point on which \p expr takes the optimal value.

    \exception std::invalid_argument
    Thrown if the constraint system contains any strict inequality.

    If the optimization problem is unfeasible or unbounded,
    the parameters \p ext_n, \p ext_d and \p optimizing_point
    will be left untouched.
  */
  Simplex_Status primal_simplex(const Linear_Expression& expr,
				Optimization_Kind kind,
				Coefficient& ext_n,
				Coefficient& ext_d,
				Generator& optimizing_point) const;

  //! Checks satisfiability of \p *this using the primal simplex algorithm.
  /*!
    \return
    <CODE>true</CODE> if the constraint system is satisfiable;
    <CODE>false</CODE> otherwise.

    \param feasible_point
    On exit, if the constraint system is satisfiable, will contain a
    feasible point.

    \exception std::invalid_argument
    Thrown if the constraint system contains any strict inequality.

    If the optimization problem is unfeasible, the parameter
    \p feasible_point will be left untouched.
  */
  bool is_satisfiable(Generator& feasible_point) const;

  //! \brief
  //! Returns the singleton system containing only
  //! Constraint::zero_dim_false().
  static const Constraint_System& zero_dim_empty();

  //! An iterator over a system of constraints.
  /*!
    A const_iterator is used to provide read-only access
    to each constraint contained in an object of Constraint_System.

    \par Example
    The following code prints the system of constraints
    defining the polyhedron <CODE>ph</CODE>:
    \code
  const Constraint_System& cs = ph.constraints();
  for (Constraint_System::const_iterator i = cs.begin(),
         cs_end = cs.end(); i != cs_end; ++i)
    cout << *i << endl;
    \endcode
  */
  class const_iterator
    : public std::iterator<std::forward_iterator_tag,
			   Constraint,
			   void,
			   const Constraint*,
			   const Constraint&> {
  public:
    //! Default constructor.
    const_iterator();

    //! Ordinary copy-constructor.
    const_iterator(const const_iterator& y);

    //! Destructor.
    ~const_iterator();

    //! Assignment operator.
    const_iterator& operator=(const const_iterator& y);

    //! Dereference operator.
    const Constraint& operator*() const;

    //! Indirect member selector.
    const Constraint* operator->() const;

    //! Prefix increment operator.
    const_iterator& operator++();

    //! Postfix increment operator.
    const_iterator operator++(int);

    //! \brief
    //! Returns <CODE>true</CODE> if and only if
    //! \p *this and \p y are identical.
    bool operator==(const const_iterator& y) const;

    //! \brief
    //! Returns <CODE>true</CODE> if and only if
    //! \p *this and \p y are different.
    bool operator!=(const const_iterator& y) const;

  private:
    friend class Constraint_System;

    //! The const iterator over the matrix of constraints.
    Linear_System::const_iterator i;

    //! A const pointer to the matrix of constraints.
    const Linear_System* csp;

    //! Constructor.
    const_iterator(const Linear_System::const_iterator& iter,
		   const Constraint_System& csys);

    //! \p *this skips to the next non-trivial constraint.
    void skip_forward();
  };

  //! \brief
  //! Returns the const_iterator pointing to the first constraint,
  //! if \p *this is not empty;
  //! otherwise, returns the past-the-end const_iterator.
  const_iterator begin() const;

  //! Returns the past-the-end const_iterator.
  const_iterator end() const;

  //! Checks if all the invariants are satisfied.
#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
  /*!
    Returns <CODE>true</CODE> if and only if \p *this is a valid
    Linear_System and each row in the system is a valid Constraint.
  */
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
  bool OK() const;

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
  //! \brief
  //! Writes to \p s an ASCII representation of the internal
  //! representation of \p *this.
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
  void ascii_dump(std::ostream& s) const;

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
  //! \brief
  //! Loads from \p s an ASCII representation (as produced by
  //! \ref ascii_dump) and sets \p *this accordingly.
  //! Returns <CODE>true</CODE> if successful, <CODE>false</CODE> otherwise.
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
  bool ascii_load(std::istream& s);

  //! Returns the total size in bytes of the memory occupied by \p *this.
  memory_size_type total_memory_in_bytes() const;

  //! Returns the size in bytes of the memory managed by \p *this.
  memory_size_type external_memory_in_bytes() const;

  //! Swaps \p *this with \p y.
  void swap(Constraint_System& y);

private:
  friend class const_iterator;
  friend class Parma_Polyhedra_Library::Polyhedron;

  friend bool
  Parma_Polyhedra_Library::operator==(const Polyhedron& x,
				      const Polyhedron& y);

  //! Builds an empty system of constraints having the specified topology.
  explicit Constraint_System(Topology topol);

  //! \brief
  //! Builds a system of \p n_rows constraints on a \p n_columns - 1
  //! dimensional space (including the \f$\epsilon\f$ dimension, if
  //! \p topol is <CODE>NOT_NECESSARILY_CLOSED</CODE>).
  Constraint_System(Topology topol,
		    dimension_type n_rows, dimension_type n_columns);

  //! \brief
  //! Adjusts \p *this so that it matches the topology and
  //! the number of space dimensions given as parameters
  //! (adding or removing columns if needed).
  //! Returns <CODE>false</CODE> if and only if \p topol is
  //! equal to <CODE>NECESSARILY_CLOSED</CODE> and \p *this
  //! contains strict inequalities.
  bool adjust_topology_and_space_dimension(Topology topol,
					   dimension_type num_dimensions);

  //! Returns the \p k- th constraint of the system.
  Constraint& operator[](dimension_type k);

  //! Returns a constant reference to the \p k- th constraint of the system.
  const Constraint& operator[](dimension_type k) const;

  //! Returns <CODE>true</CODE> if \p g satisfies all the constraints.
  bool satisfies_all_constraints(const Generator& g) const;

  //! \brief
  //! Substitutes a given column of coefficients by a given
  //! affine expression.
  /*!
    \param v
    Index of the column to which the affine transformation is substituted.

    \param expr
    The numerator of the affine transformation:
    \f$\sum_{i = 0}^{n - 1} a_i x_i + b\f$;

    \param denominator
    The denominator of the affine transformation.

    We want to allow affine transformations
    (see Section \ref Images_and_Preimages_of_Affine_Transfer_Relations)
    having any rational coefficients. Since the coefficients of the
    constraints are integers we must also provide an integer \p
    denominator that will be used as denominator of the affine
    transformation.
    The denominator is required to be a positive integer.

    The affine transformation substitutes the matrix of constraints
    by a new matrix whose elements \f${a'}_{ij}\f$ are built from
    the old one \f$a_{ij}\f$ as follows:
    \f[
      {a'}_{ij} =
        \begin{cases}
          a_{ij} * \mathrm{denominator} + a_{iv} * \mathrm{expr}[j]
            \quad \text{for } j \neq v; \\
          \mathrm{expr}[v] * a_{iv}
            \quad \text{for } j = v.
        \end{cases}
    \f]

    \p expr is a constant parameter and unaltered by this computation.
  */
  void affine_preimage(dimension_type v,
		       const Linear_Expression& expr,
		       Coefficient_traits::const_reference denominator);

  //! Returns the number of equality constraints.
  dimension_type num_equalities() const;

  //! Returns the number of inequality constraints.
  dimension_type num_inequalities() const;

  //! \brief
  //! Applies Gaussian's elimination and back-substitution so as
  //! to provide a partial simplification of the system of constraints.
  /*!
    It is assumed that the system has no pending constraints.
  */
  void simplify();

  //! \brief
  //! Inserts in \p *this a copy of the constraint \p c,
  //! increasing the number of space dimensions if needed.
  //! It is a pending constraint.
  void insert_pending(const Constraint& c);

  //! Adds low-level constraints to the constraint system.
  void add_low_level_constraints();

  //! \brief
  //! Applies the primal simplex algorithm so as to maximize the value
  //! of \p cost_function on the system of constraints.
  /*!
    \return
    A Simplex_Status flag indicating the outcome of the maximization
    attempt (unfeasible, unbounded or solved problem).

    \param cost_function
    The cost function to be maximized. It could be modified
    during the call.

    \param maximizing_point
    On exit, if the problem has been solved, will contain a feasible
    point on which \p cost_function takes the maximal value.

    If the optimization problem is unfeasible or unbounded,
    the parameter \p maximizing_point will be left untouched.
    It is assumed that the constraint system contains
    no strict inequalities.
  */
  Simplex_Status primal_simplex(Linear_Expression& cost_function,
				Generator& maximizing_point) const;
};

// Constraint_System.inlines.hh is not included here on purpose.

#endif // !defined(PPL_Constraint_System_defs_hh)
