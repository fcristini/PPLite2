/* Polyhedron class declaration.
   Copyright (C) 2001 Roberto Bagnara <bagnara@cs.unipr.it>

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
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#ifndef _Polyhedron_defs_hh
#define _Polyhedron_defs_hh 1

#include "ConSys.defs.hh"
#include "GenSys.defs.hh"
#include "SatMatrix.defs.hh"
#include "Status.defs.hh"
#include "Polyhedron.types.hh"

namespace Parma_Polyhedra_Library {
  // Put them in the namespace here to declare them friend later.

  //! @name Polyhedron. 
  //@{
  //! Returns <CODE>true</CODE> if and only if
  //! \p x and \p y are the same polyhedron.
  bool operator ==(const Polyhedron& x, const Polyhedron& y);
  //! Returns <CODE>true</CODE> if and only if
  //! \p x and \p y are different polyhedra.
  bool operator !=(const Polyhedron& x, const Polyhedron& y);
  //! Returns <CODE>true</CODE> if and only if
  //! \p x is strictly contained in \p y.
  bool operator <(const Polyhedron& x, const Polyhedron& y);
  //! Returns <CODE>true</CODE> if and only if
  //! \p x strictly contains \p y.
  bool operator >(const Polyhedron& x, const Polyhedron& y);
  //! Returns <CODE>true</CODE> if and only if
  //! \p x is contained in \p y.
  bool operator <=(const Polyhedron& x, const Polyhedron& y);
  //! Returns <CODE>true</CODE> if and only if
  //!  \p x contains \p y.
  bool operator >=(const Polyhedron& x, const Polyhedron& y);
  //! Output operator.
  std::ostream& operator <<(std::ostream& s, const Polyhedron& p);
  //! Input operator.
  std::istream& operator >>(std::istream& s, Polyhedron& p);
  //@}
}

/*!
  An object of this class is a polyhedron.
  A polyhedron can be rapresented by either a system of constraints 
  or a set of generators (see Minkowski's theorem in definition.dox):
  they can be in the minimal form or not (if they are not minimized,
  redundant constraints or generators can be in the systems).

  We can built a polyhedron starting from a system of constraints, or
  from a set of generators and we can obtain a matrix from the other 
  (i.e. if we have the system of constraint, we can obtain the set 
  of generators, and vice versa).
*/

class Parma_Polyhedra_Library::Polyhedron {
public:
  //! Constructs a universe polyhedron of dimension \p num_dimension.
  explicit Polyhedron(size_t num_dimension);
  //! Constructs zero-dimensional, full polyhedron.
  Polyhedron();
  //! Copy-constructor
  Polyhedron(const Polyhedron& y);
  //! Constructs a polyhedron starting from a system of constraints.
  Polyhedron(ConSys& cs);
  //! Constructs a polyhedron starting from a system of generators.
  Polyhedron(GenSys& gs);
  // Destructor
  ~Polyhedron();

  //! The assignment operator.
  Polyhedron& operator =(const Polyhedron& y);

  //! Returns the dimension of the polyhedron.
  size_t num_dimensions() const;
  //! Intersects \p *this with \p y and assigns the intersection to \p *this.
  void intersection_assign(const Polyhedron& y);
  //! Assigns the convex hull of \p *this and \p y to \p *this.
  void convex_hull_assign(const Polyhedron& y);
  //! Assigns the convex hull of \p *this and \p y to \p *this,
  //! without minimizing the result.
  void convex_hull_assign_lazy(const Polyhedron& y);

  //! Returns the relation between the generators of \p *this 
  //! and the constraint \p con.
  GenSys_Con_Rel poly_satisfies_constraint(const Constraint& con);
  //! Tests the inclusion of a generator in a polyhedron. 
  bool includes(const Generator& gen);

  //! Computes widening between \p *this and \p y and 
  //! assigns the result to \p *this.
  void widening_assign(const Polyhedron& y);
  //! Limits the widening between \p *this and \p y by \p constraints
  //! and assigns the result to \p *this.
  bool limited_widening_assign(const Polyhedron& y, ConSys& constraints);

  //! Returns the system of constraints.
  const ConSys& constraints() const;
  //! Returns the system of generators.
  const GenSys& generators() const;

  //! Insert a new constraints \p c into the system of constraints.
  void insert(const Constraint& c);

  //! Assigns an affine expression to the specified variable.
  void assign_variable(size_t var,
		       std::vector<Integer>& coefficient,
		       Integer& denominator);
  //! Substitute an affine expression to the specified variable.
  void substitute_variable(size_t var,
			   std::vector<Integer>& coefficient,
			   Integer& denominator);

#ifndef NDEBUG
  //! Checks if a polyhedron is allowed.
  bool OK(bool check_satisfiable = true) const;
  // Temporary debug constructor.
  Polyhedron(size_t nblines, size_t nbrays, size_t nbeq);
#endif

private:
  //! Minimizes generators and constraints.
  void minimize() const;
  //! Updates constraints starting from generators and minimizes them.
  void update_constraints() const;
  //! Updates generators starting from constraints and minimizes them.
  bool update_generators() const;
  //! Updates \p sat_c using the updated constraints and generators.
  void update_sat_c() const;
  //! Updates \p sat_g using the updated constraints and generators.
  void update_sat_g() const;
  //! Sorts the matrix of constraints keeping \p sat_g consistent.
  void obtain_sorted_constraints();
  //! Sorts the matrix of generators keeping \p sat_c consistent.
  void obtain_sorted_generators();
  //! Sorts the matrix of constraints and makes \p sat_c consistent.
  void obtain_sorted_constraints_with_sat_c();
  //! Sorts the matrix of generators and makes \p sat_g consistent.
  void obtain_sorted_generators_with_sat_g();

public:
  // Adds new dimensions and embeds the old polyhedron in the new space.
  void add_dimensions_and_embed(size_t add_dim);
  // Adds new dimensions to the polyhedron 
  // and does not embed it in the new space.
  void add_dimensions_and_project(size_t add_dim);
  // Removes the specified dimensions.
  void remove_dimensions(const BitSet& dims_to_remove);
  //! Adds given constraints to the polyhedron and compute a new polyhedron.
  bool add_constraints(ConSys& constraints_to_add);
  //! Adds given constraints to the polyhedron without minimizing. 
  void add_constraints_lazy(ConSys& constraints_to_add);
  //! Adds given generators to the existing ones.
  void add_generators(GenSys& generators_to_add);
  //! Returns <CODE>true</CODE> if the polyhedron is empty.
  bool check_empty() const;
  //! Returns <CODE>true</CODE> if \p *this is a universe polyhedron.
  bool check_universe() const;

  friend bool Parma_Polyhedra_Library::operator <=(const Polyhedron& x,
						   const Polyhedron& y);

  //! Raw read/write operators.
  //@{
  friend std::ostream&
  Parma_Polyhedra_Library::operator <<(std::ostream& s, const Polyhedron& p);

  friend std::istream&
  Parma_Polyhedra_Library::operator >>(std::istream& s, Polyhedron& p);
  //@}

  //! Swaps \p *this polyhedron with \p y.
  void swap(Polyhedron& y);

private:
  //! The system of constraints
  ConSys con_sys;
  //! The system of generators
  GenSys gen_sys;
  //! The saturation matrix having constraints on its columns.
  SatMatrix sat_c;
  //! The saturation matrix having generators on its columns.
  SatMatrix sat_g;
  //! The status flags to keep track of the polyhedron's internal state.
  Status status;

public:
  /*! @name Public Verifiers
    Verify if flags of special cases are set.
  */
  //@{
  bool is_empty() const;
  bool is_zero_dim() const;
  //@}

private:
  /*! @name Private Verifiers 
    Verify if individual flags are set.
  */
  //@{
  bool constraints_are_up_to_date() const;
  bool generators_are_up_to_date() const;
  bool constraints_are_minimized() const;
  bool generators_are_minimized() const;
  bool sat_c_is_up_to_date() const;
  bool sat_g_is_up_to_date() const;
  //@}

   
  /*! @name Setters
    Set only the specified flags.
  */
  //@{
  void set_zero_dim();
  void set_empty();
  void set_constraints_up_to_date();
  void set_generators_up_to_date();
  void set_constraints_minimized();
  void set_generators_minimized();
  void set_sat_c_up_to_date();
  void set_sat_g_up_to_date();
  //@}

  /*! @name Cleaners
    Clear only the specified flag.
  */
  //@{
  void clear_empty();
  void clear_constraints_up_to_date();
  void clear_generators_up_to_date();
  void clear_constraints_minimized();
  void clear_generators_minimized();
  void clear_sat_c_up_to_date();
  void clear_sat_g_up_to_date();
//@}

  //! Adds new dimensions to the given matrices.
  static void add_dimensions(Matrix& mat1,
                             Matrix& mat2,
                             SatMatrix& sat1,
                             SatMatrix& sat2,
			     size_t add_dim);

  //! Performs the conversion from constraints to generators and vice versa.
  static size_t conversion(Matrix& entry,
			   size_t start,
			   Matrix& result,
			   SatMatrix& sat,
			   size_t num_lines_or_equalities);

  //! Uses Gauss' elimination method to simplify the result of 
  //! <CODE>conversion()</CODE>.
  static int simplify(Matrix& mat, SatMatrix& sat);

  //! Builds and simplifies constraints from generators (or vice versa).
  static bool minimize(bool con_to_ray, Matrix& source, Matrix& dest,
		       SatMatrix& sat);

  //! Adds given constraints and builds minimized corresponding generators
  //! or vice versa.
  static bool add_and_minimize(bool con_to_ray,
			       Matrix& source1, Matrix& dest, SatMatrix& sat,
			       const Matrix& source2);
};

namespace std {
  /*!
    Specialize std::swap to use the fast swap that is provided
    as a member function instead of using the default algorithm
    (which creates a temporary and uses assignment).
  */
  void swap(Parma_Polyhedra_Library::Polyhedron& x,
	    Parma_Polyhedra_Library::Polyhedron& y);
}

#if !OUTLINE
#include "Polyhedron.inlines.hh"
#endif

#endif
