/* ConSys class implementation (non-inline functions).
   Copyright (C) 2001-2004 Roberto Bagnara <bagnara@cs.unipr.it>

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

#include <config.h>

#include "ConSys.defs.hh"
#include "ConSys.inlines.hh"

#include "Generator.defs.hh"
#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace PPL = Parma_Polyhedra_Library;

bool
PPL::ConSys::adjust_topology_and_dimension(Topology new_topology,
					   dimension_type new_space_dim) {
  assert(space_dimension() <= new_space_dim);

  if (num_rows() == 0) {
    if (topology() != new_topology)
      if (is_necessarily_closed())
	set_not_necessarily_closed();
      else
	set_necessarily_closed();
    assert(OK());
    return true;
  }

  // Here `num_rows() > 0'.
  const dimension_type old_space_dim = space_dimension();
  const Topology old_topology = topology();
  dimension_type cols_to_be_added = new_space_dim - old_space_dim;

  if (cols_to_be_added > 0)
    if (old_topology != new_topology)
      if (new_topology == NECESSARILY_CLOSED) {
	// A NOT_NECESSARILY_CLOSED constraint system
	// can be converted to a NECESSARILY_CLOSED one
	// only if it does not contain strict inequalities.
	if (has_strict_inequalities())
	  return false;
	// Since there were no strict inequalities,
	// the only constraints that may have a non-zero epsilon coefficient
	// are the eps-leq-one and the eps-geq-zero constraints.
	// If they are present, we erase these rows, so that the
	// epsilon column will only contain zeroes: as a consequence,
	// we just decrement the number of columns to be added.
	ConSys& cs = *this;
	const dimension_type eps_index = old_space_dim + 1;
	dimension_type cs_num_rows = cs.num_rows();
	bool was_sorted = cs.is_sorted();
	if (was_sorted)
	  cs.set_sorted(false);

	// If we have no pending rows, we only check if
	// we must erase some rows.
	if (cs.num_pending_rows() == 0) {
	  for (dimension_type i = cs_num_rows; i-- > 0; )
	    if (cs[i][eps_index] != 0) {
	      --cs_num_rows;
	      std::swap(cs[i], cs[cs_num_rows]);
	    }
	  cs.erase_to_end(cs_num_rows);
	  cs.unset_pending_rows();
	}
	else {
	  // There are pending rows, and we cannot swap them
	  // into the non-pending part of the matrix.
	  // Thus, we first work on the non-pending part as if it was
	  // an independent matrix; then we work on the pending part.
	  const dimension_type old_first_pending = cs.first_pending_row();
	  dimension_type new_first_pending = old_first_pending;
	  for (dimension_type i = new_first_pending; i-- > 0; )
	    if (cs[i][eps_index] != 0) {
	      --new_first_pending;
	      std::swap(cs[i], cs[new_first_pending]);
	    }
	  const dimension_type num_swaps
	    = old_first_pending - new_first_pending;
          cs.set_index_first_pending_row(new_first_pending);
	  // Move the swapped rows to the real end of the matrix.
	  for (dimension_type i = num_swaps; i-- > 0; )
	    std::swap(cs[old_first_pending - i], cs[cs_num_rows - i]);
	  cs_num_rows -= num_swaps;
	  // Now iterate through the pending rows.
	  for (dimension_type i = cs_num_rows; i-- > new_first_pending; )
	    if (cs[i][eps_index] != 0) {
	      --cs_num_rows;
	      std::swap(cs[i], cs[cs_num_rows]);
	    }
	  cs.erase_to_end(cs_num_rows);
	}

	// If `cs' was sorted we sort it again.
	if (was_sorted)
	  cs.sort_rows();
	if (--cols_to_be_added > 0)
	  add_zero_columns(cols_to_be_added);
	set_necessarily_closed();
      }
      else {
	// A NECESSARILY_CLOSED constraint system is converted to
	// a NOT_NECESSARILY_CLOSED one by adding a further column
	// of zeroes for the epsilon coefficients.
	add_zero_columns(++cols_to_be_added);
	set_not_necessarily_closed();
      }
    else {
      // Topologies agree: first add the required zero columns ...
      add_zero_columns(cols_to_be_added);
      // ... and, if needed, move the epsilon coefficients
      // to the new last column.
      if (old_topology == NOT_NECESSARILY_CLOSED)
	swap_columns(old_space_dim + 1, new_space_dim + 1);
    }
  else
    // Here `cols_to_be_added == 0'.
    if (old_topology != new_topology)
      if (new_topology == NECESSARILY_CLOSED) {
	// A NOT_NECESSARILY_CLOSED constraint system
	// can be converted to a NECESSARILY_CLOSED one
	// only if it does not contain strict inequalities.
	if (has_strict_inequalities())
	  return false;
	// We just remove the column of the epsilon coefficients.
	remove_columns(old_space_dim + 1);
	set_necessarily_closed();
      }
      else {
	// We just add the column of the epsilon coefficients.
	add_zero_columns(1);
	set_not_necessarily_closed();
      }
  // We successfully adjusted dimensions and topology.
  assert(OK());
  return true;
}

bool
PPL::ConSys::has_strict_inequalities() const {
  if (is_necessarily_closed())
    return false;
  const ConSys& cs = *this;
  dimension_type eps_index = cs.num_columns() - 1;
  // We verify if the system has strict inequalities
  // also in the pending part.
  for (dimension_type i = num_rows(); i-- > 0; )
    // Optimized type checking: we already know the topology;
    // also, equalities have the epsilon coefficient equal to zero.
    // NOTE: the constraint eps_leq_one should not be considered
    //       a strict inequality.
    if (cs[i][eps_index] < 0 && !cs[i].is_trivial_true())
      return true;
  return false;
}


void
PPL::ConSys::insert(const Constraint& c) {
  // We are sure that the matrix has no pending rows
  // and that the new row is not a pending constraint.
  assert(num_pending_rows() == 0);
  if (topology() == c.topology())
    Matrix::insert(c);
  else
    // `*this' and `c' have different topologies.
    if (is_necessarily_closed()) {
      // Padding the matrix with a columns of zeroes
      // corresponding to the epsilon coefficients.
      add_zero_columns(1);
      set_not_necessarily_closed();
      Matrix::insert(c);
    }
    else {
      // Here `*this' is NNC and `c' is necessarily closed.
      // Copying the constraint adding the epsilon coefficient
      // and the missing dimensions, if any.
      const dimension_type new_size = 2 + std::max(c.space_dimension(),
						   space_dimension());
      Constraint tmp_c(c, new_size);
      tmp_c.set_not_necessarily_closed();
      Matrix::insert(tmp_c);
    }
}

void
PPL::ConSys::insert_pending(const Constraint& c) {
  if (topology() == c.topology())
    Matrix::insert_pending(c);
  else
    // `*this' and `c' have different topologies.
    if (is_necessarily_closed()) {
      // Padding the matrix with a columns of zeroes
      // corresponding to the epsilon coefficients.
      add_zero_columns(1);
      set_not_necessarily_closed();
      Matrix::insert_pending(c);
    }
    else {
      // Here `*this' is NNC and `c' is necessarily closed.
      // Copying the constraint adding the epsilon coefficient
      // and the missing dimensions, if any.
      const dimension_type new_size = 2 + std::max(c.space_dimension(),
						   space_dimension());
      Constraint tmp_c(c, new_size);
      tmp_c.set_not_necessarily_closed();
      Matrix::insert_pending(tmp_c);
    }
}

PPL::dimension_type
PPL::ConSys::num_inequalities() const {
  // We are sure that we call this method only when
  // the matrix has no pending rows.
  assert(num_pending_rows() == 0);
  const ConSys& cs = *this;
  int n = 0;
  // If the Matrix happens to be sorted, take advantage of the fact
  // that inequalities are at the bottom of the system.
  if (is_sorted())
    for (dimension_type i = num_rows(); i > 0 && cs[--i].is_inequality(); )
      ++n;
  else
    for (dimension_type i = num_rows(); i-- > 0 ; )
      if (cs[i].is_inequality())
	++n;
  return n;
}

PPL::dimension_type
PPL::ConSys::num_equalities() const {
  // We are sure that we call this method only when
  // the matrix has no pending rows.
  assert(num_pending_rows() == 0);
  return num_rows() - num_inequalities();
}

void
PPL::ConSys::const_iterator::skip_forward() {
  const Matrix::const_iterator csp_end = csp->end();
  while (i != csp_end && (*this)->is_trivial_true())
    ++i;
}

bool
PPL::ConSys::satisfies_all_constraints(const Generator& g) const {
  assert(g.space_dimension() <= space_dimension());

  // Setting `sp_fp' to the appropriate scalar product operator.
  // This also avoids problems when having _legal_ topology mismatches
  // (which could also cause a mismatch in the number of columns).
  int (*sps_fp)(const Row&, const Row&);
  if (g.is_necessarily_closed())
    sps_fp = PPL::scalar_product_sign;
  else
    sps_fp = PPL::reduced_scalar_product_sign;
  const ConSys& cs = *this;

  if (cs.is_necessarily_closed()) {
    if (g.is_line()) {
      // Lines must saturate all constraints.
      for (dimension_type i = cs.num_rows(); i-- > 0; )
	if (sps_fp(g, cs[i]) != 0)
	  return false;
    }
    else
      // `g' is either a ray, a point or a closure point.
      for (dimension_type i = cs.num_rows(); i-- > 0; ) {
	const Constraint& c = cs[i];
	const int sp_sign = sps_fp(g, c);
	if (c.is_inequality()) {
	  // As `cs' is necessarily closed,
	  // `c' is a non-strict inequality.
	  if (sp_sign < 0)
	    return false;
	}
	else
	  // `c' is an equality.
	  if (sp_sign != 0)
	    return false;
      }
  }
  else
    // `cs' is not necessarily closed.
    switch (g.type()) {

    case Generator::LINE:
      // Lines must saturate all constraints.
      for (dimension_type i = cs.num_rows(); i-- > 0; )
	if (sps_fp(g, cs[i]) != 0)
	  return false;
      break;

    case Generator::POINT:
      // Have to perform the special test
      // when dealing with a strict inequality.
      for (dimension_type i = cs.num_rows(); i-- > 0; ) {
	const Constraint& c = cs[i];
	const int sp_sign = sps_fp(g, c);
	switch (c.type()) {
	case Constraint::EQUALITY:
	  if (sp_sign != 0)
	    return false;
	  break;
	case Constraint::NONSTRICT_INEQUALITY:
	  if (sp_sign < 0)
	    return false;
	  break;
	case Constraint::STRICT_INEQUALITY:
	  if (sp_sign <= 0)
	    return false;
	  break;
	}
      }
      break;

    case Generator::RAY:
      // Intentionally fall through.
    case Generator::CLOSURE_POINT:
      for (dimension_type i = cs.num_rows(); i-- > 0; ) {
	const Constraint& c = cs[i];
	const int sp_sign = sps_fp(g, c);
	if (c.is_inequality()) {
	  // Constraint `c' is either a strict or a non-strict inequality.
	  if (sp_sign < 0)
	    return false;
	}
	else
	  // Constraint `c' is an equality.
	  if (sp_sign != 0)
	    return false;
      }
      break;
    }

  // If we reach this point, `g' satisfies all constraints.
  return true;
}


void
PPL::ConSys::affine_preimage(dimension_type v,
			     const LinExpression& expr,
			     Integer_traits::const_reference denominator) {
  // `v' is the index of a column corresponding to
  // a "user" variable (i.e., it cannot be the inhomogeneous term,
  // nor the epsilon dimension of NNC polyhedra).
  assert(v > 0 && v <= space_dimension());
  assert(expr.space_dimension() <= space_dimension());
  assert(denominator > 0);

  const dimension_type n_columns = num_columns();
  const dimension_type n_rows = num_rows();
  const dimension_type expr_size = expr.size();
  const bool not_invertible = (v >= expr_size || expr[v] == 0);
  ConSys& x = *this;

  if (denominator != 1)
    for (dimension_type i = n_rows; i-- > 0; ) {
      Constraint& row = x[i];
      Integer& row_v = row[v];
      if (row_v != 0) {
	for (dimension_type j = n_columns; j-- > 0; )
	  if (j != v) {
	    Integer& row_j = row[j];
	    row_j *= denominator;
	    if (j < expr_size)
	      add_mul_assign(row_j, row_v, expr[j]);
	  }
	if (not_invertible)
	  row_v = 0;
	else
	  row_v *= expr[v];
      }
    }
  else
    // Here `denominator' == 1: optimized computation
    // only considering columns having indexes < expr_size.
    for (dimension_type i = n_rows; i-- > 0; ) {
      Constraint& row = x[i];
      Integer& row_v = row[v];
      if (row_v != 0) {
	for (dimension_type j = expr_size; j-- > 0; )
	  if (j != v)
	    add_mul_assign(row[j], row_v, expr[j]);
	if (not_invertible)
	  row_v = 0;
	else
	  row_v *= expr[v];
      }
    }
  // Strong normalization also resets the sortedness flag.
  x.strong_normalize();
}

void
PPL::ConSys::ascii_dump(std::ostream& s) const {
  Matrix::ascii_dump(s);
  const char separator = ' ';
  const ConSys& x = *this;
  for (dimension_type i = 0; i < x.num_rows(); ++i) {
    for (dimension_type j = 0; j < x.num_columns(); ++j)
      s << x[i][j] << separator;
    s << separator << separator;
    switch (static_cast<Constraint>(x[i]).type()) {
    case Constraint::EQUALITY:
      s << "=";
      break;
    case Constraint::NONSTRICT_INEQUALITY:
      s << ">=";
      break;
    case Constraint::STRICT_INEQUALITY:
      s << ">";
      break;
    }
    s << std::endl;
  }
}

bool
PPL::ConSys::ascii_load(std::istream& s) {
  if (!Matrix::ascii_load(s))
    return false;

  std::string str;
  ConSys& x = *this;
  for (dimension_type i = 0; i < x.num_rows(); ++i) {
    for (dimension_type j = 0; j < x.num_columns(); ++j)
      if (!(s >> x[i][j]))
	return false;

    if (!(s >> str))
      return false;
    if (str == "=")
      x[i].set_is_equality();
    else
      x[i].set_is_inequality();

    // Checking for equality of actual and declared types.
    switch (static_cast<Constraint>(x[i]).type()) {
    case Constraint::EQUALITY:
      if (str == "=")
	continue;
      break;
    case Constraint::NONSTRICT_INEQUALITY:
      if (str == ">=")
	continue;
      break;
    case Constraint::STRICT_INEQUALITY:
      if (str == ">")
	continue;
      break;
    }
    // Reaching this point means that the input was illegal.
    return false;
  }
  // Check for well-formedness.
  assert(OK());
  return true;
}

bool
PPL::ConSys::OK() const {
  // A ConSys must be a valid Matrix; do not check for
  // strong normalization, since this will be done when
  // checking each individual constraint.
  if (!Matrix::OK(false))
    return false;

  // Checking each constraint in the system.
  for (dimension_type i = num_rows(); i-- > 0; ) {
    const Constraint& c = (*this)[i];
    if (!c.OK())
      return false;
  }

  // All checks passed.
  return true;
}

/*! \relates Parma_Polyhedra_Library::ConSys */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s, const ConSys& cs) {
  ConSys::const_iterator i = cs.begin();
  const ConSys::const_iterator cs_end = cs.end();
  if (i == cs_end)
    s << "true";
  else {
    while (i != cs_end) {
      s << *i++;
      if (i != cs_end)
	s << ", ";
    }
  }
  return s;
}
