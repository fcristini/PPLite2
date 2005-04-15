/* Generator_System class implementation (non-inline functions).
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
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#include <config.h>

#include "Generator_System.defs.hh"
#include "Generator_System.inlines.hh"

#include "Constraint.defs.hh"
#include "Grid.defs.hh"		// For virtual_row and mark_virtual.
#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace PPL = Parma_Polyhedra_Library;

bool
PPL::Generator_System::
adjust_topology_and_space_dimension(const Topology new_topology,
				    const dimension_type new_space_dim) {
  assert(space_dimension() <= new_space_dim);

  const dimension_type old_space_dim = space_dimension();
  const Topology old_topology = topology();
  dimension_type cols_to_be_added = new_space_dim - old_space_dim;

  // Dealing with empty constraint systems first.
  if (num_rows() == 0) {
    if (num_columns() == 0)
      if (new_topology == NECESSARILY_CLOSED) {
	add_zero_columns(++cols_to_be_added);
	set_necessarily_closed();
      }
      else {
	cols_to_be_added += 2;
	add_zero_columns(cols_to_be_added);
	set_not_necessarily_closed();
      }
    else
      // Here `num_columns() > 0'.
      if (old_topology != new_topology)
	if (new_topology == NECESSARILY_CLOSED) {
	  switch (cols_to_be_added) {
	  case 0:
	    remove_trailing_columns(1);
	    break;
	  case 1:
	    // Nothing to do.
	    break;
	  default:
	    add_zero_columns(--cols_to_be_added);
	  }
	  set_necessarily_closed();
	}
	else {
	  // Here old_topology == NECESSARILY_CLOSED
	  //  and new_topology == NOT_NECESSARILY_CLOSED.
	  add_zero_columns(++cols_to_be_added);
	  set_not_necessarily_closed();
	}
      else {
	// Here topologies agree.
	if (cols_to_be_added > 0)
	  add_zero_columns(cols_to_be_added);
      }
    assert(OK());
    return true;
  }

  // Here `num_rows() > 0'.
  if (cols_to_be_added > 0)
    if (old_topology != new_topology)
      if (new_topology == NECESSARILY_CLOSED) {
	// A NOT_NECESSARILY_CLOSED generator system
	// can be converted to a NECESSARILY_CLOSED one
	// only if it does not contain closure points.
	// This check has to be performed under the user viewpoint.
	if (has_closure_points())
	  return false;
	// For a correct implementation, we have to remove those
	// closure points that were matching a point (i.e., those
	// that are in the generator system, but are invisible to
	// the user).
	Generator_System& gs = *this;
	dimension_type num_closure_points = 0;
	dimension_type gs_end = gs.num_rows();
	for (dimension_type i = 0; i < gs_end; ) {
	  // All the closure points seen so far have consecutive
	  // indices starting from `i'.
	  if (num_closure_points > 0)
	    // Let next generator have index `i'.
	    std::swap(gs[i], gs[i+num_closure_points]);
	  if (gs[i].is_closure_point()) {
	    ++num_closure_points;
	    --gs_end;
	  }
	  else
	    ++i;
	}
	// We may have identified some closure points.
	if (num_closure_points > 0) {
	  assert(num_closure_points == num_rows() - gs_end);
	  erase_to_end(gs_end);
	}
	// Remove the epsilon column, re-normalize and, after that,
	// add the missing dimensions. This ensures that
	// non-zero epsilon coefficients will be cleared.
	remove_trailing_columns(1);
	set_necessarily_closed();
	normalize();
	add_zero_columns(cols_to_be_added);
      }
      else {
	// A NECESSARILY_CLOSED generator system is converted to
	// a NOT_NECESSARILY_CLOSED one by adding a further column
	// and setting the epsilon coordinate of all points to 1.
	// Note: normalization is preserved.
	add_zero_columns(++cols_to_be_added);
	Generator_System& gs = *this;
	const dimension_type eps_index = new_space_dim + 1;
	for (dimension_type i = num_rows(); i-- > 0; )
	  gs[i][eps_index] = gs[i][0];
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
	// A NOT_NECESSARILY_CLOSED generator system
	// can be converted in to a NECESSARILY_CLOSED one
	// only if it does not contain closure points.
	if (has_closure_points())
	  return false;
	// We just remove the column of the epsilon coefficients.
	remove_trailing_columns(1);
	set_necessarily_closed();
      }
      else {
	// Add the column of the epsilon coefficients
	// and set the epsilon coordinate of all points to 1.
	// Note: normalization is preserved.
	add_zero_columns(1);
	Generator_System& gs = *this;
	const dimension_type eps_index = new_space_dim + 1;
	for (dimension_type i = num_rows(); i-- > 0; )
	  gs[i][eps_index] = gs[i][0];
	set_not_necessarily_closed();
      }
  // We successfully adjusted dimensions and topology.
  assert(OK());
  return true;
}

// TODO: would be worth to avoid adding closure points
// that already are in the system of generators?
// To do this efficiently we could sort the system and
// perform insertions keeping its sortedness.
void
PPL::Generator_System::add_corresponding_closure_points() {
  assert(!is_necessarily_closed());
  // NOTE: we always add (pending) rows at the end of the generator system.
  // Updating `index_first_pending', if needed, is done by the caller.
  Generator_System& gs = *this;
  const dimension_type n_rows = gs.num_rows();
  const dimension_type eps_index = gs.num_columns() - 1;
  for (dimension_type i = n_rows; i-- > 0; ) {
    const Generator& g = gs[i];
    if (g[eps_index] > 0) {
      // `g' is a point: adding the closure point.
      Generator cp = g;
      cp[eps_index] = 0;
      // Enforcing normalization.
      cp.normalize();
      gs.add_pending_row(cp);
    }
  }
  assert(OK());
}


// TODO: would be worth to avoid adding points
// that already are in the system of generators?
// To do this efficiently we could sort the system and
// perform insertions keeping its sortedness.
void
PPL::Generator_System::add_corresponding_points() {
  assert(!is_necessarily_closed());
  // NOTE: we always add (pending) rows at the end of the generator system.
  // Updating `index_first_pending', if needed, is done by the caller.
  Generator_System& gs = *this;
  const dimension_type n_rows = gs.num_rows();
  const dimension_type eps_index = gs.num_columns() - 1;
  for (dimension_type i = 0; i < n_rows; i++) {
    const Generator& g = gs[i];
    if (g[0] > 0 && g[eps_index] == 0) {
      // `g' is a closure point: adding the point.
      // Note: normalization is preserved.
      Generator p = g;
      p[eps_index] = p[0];
      gs.add_pending_row(p);
    }
  }
  assert(OK());
}

bool
PPL::Generator_System::has_closure_points() const {
  if (is_necessarily_closed())
    return false;
  // Adopt the point of view of the user.
  for (Generator_System::const_iterator i = begin(),
	 iend = end(); i != iend; ++i)
    if (i->is_closure_point())
      return true;
  return false;
}

bool
PPL::Generator_System::has_points() const {
  const Generator_System& gs = *this;
  // Avoiding the repeated tests on topology.
  if (is_necessarily_closed())
    for (dimension_type i = num_rows(); i-- > 0; ) {
      if (gs[i][0] != 0)
	return true;
    }
  else {
    // is_necessarily_closed() == false.
    const dimension_type eps_index = gs.num_columns() - 1;
    for (dimension_type i = num_rows(); i-- > 0; )
    if (gs[i][eps_index] != 0)
      return true;
  }
  return false;
}

void
PPL::Generator_System::const_iterator::skip_forward() {
  const Linear_System::const_iterator gsp_end = gsp->end();
  if (i != gsp_end) {
    Linear_System::const_iterator i_next = i;
    ++i_next;
    if (i_next != gsp_end) {
      const Generator& cp = static_cast<const Generator&>(*i);
      const Generator& p = static_cast<const Generator&>(*i_next);
      if (cp.is_closure_point()
	  && p.is_point()
	  && cp.is_matching_closure_point(p))
	i = i_next;
    }
  }
}

void
PPL::Generator_System::insert(const Generator& g) {
  // We are sure that the matrix has no pending rows
  // and that the new row is not a pending generator.
  assert(num_pending_rows() == 0);
  if (topology() == g.topology())
    Linear_System::insert(g);
  else
    // `*this' and `g' have different topologies.
    if (is_necessarily_closed()) {
      // Padding the matrix with the column
      // corresponding to the epsilon coefficients:
      // all points must have epsilon coordinate equal to 1
      // (i.e., the epsilon coefficient is equal to the divisor);
      // rays and lines must have epsilon coefficient equal to 0.
      // Note: normalization is preserved.
      const dimension_type eps_index = num_columns();
      add_zero_columns(1);
      Generator_System& gs = *this;
      for (dimension_type i = num_rows(); i-- > 0; ) {
	Generator& gen = gs[i];
	if (gen[0] != 0)
	  gen[eps_index] = gen[0];
      }
      set_not_necessarily_closed();
      // Inserting the new generator.
      Linear_System::insert(g);
    }
    else {
      // The generator system is NOT necessarily closed:
      // copy the generator, adding the missing dimensions
      // and the epsilon coefficient.
      const dimension_type new_size = 2 + std::max(g.space_dimension(),
						   space_dimension());
      Generator tmp_g(g, new_size);
      // If it was a point, set the epsilon coordinate to 1
      // (i.e., set the coefficient equal to the divisor).
      // Note: normalization is preserved.
      if (tmp_g[0] != 0)
	tmp_g[new_size - 1] = tmp_g[0];
      tmp_g.set_not_necessarily_closed();
      // Inserting the new generator.
      Linear_System::insert(tmp_g);
    }
  assert(OK());
}

void
PPL::Generator_System::insert_pending(const Generator& g) {
  if (topology() == g.topology())
    Linear_System::insert_pending(g);
  else
    // `*this' and `g' have different topologies.
    if (is_necessarily_closed()) {
      // Padding the matrix with the column
      // corresponding to the epsilon coefficients:
      // all points must have epsilon coordinate equal to 1
      // (i.e., the epsilon coefficient is equal to the divisor);
      // rays and lines must have epsilon coefficient equal to 0.
      // Note: normalization is preserved.
      const dimension_type eps_index = num_columns();
      add_zero_columns(1);
      Generator_System& gs = *this;
      for (dimension_type i = num_rows(); i-- > 0; ) {
	Generator& gen = gs[i];
	if (gen[0] != 0)
	  gen[eps_index] = gen[0];
      }
      set_not_necessarily_closed();
      // Inserting the new generator.
      Linear_System::insert_pending(g);
    }
    else {
      // The generator system is NOT necessarily closed:
      // copy the generator, adding the missing dimensions
      // and the epsilon coefficient.
      const dimension_type new_size = 2 + std::max(g.space_dimension(),
						   space_dimension());
      Generator tmp_g(g, new_size);
      // If it was a point, set the epsilon coordinate to 1
      // (i.e., set the coefficient equal to the divisor).
      // Note: normalization is preserved.
      if (tmp_g[0] != 0)
	tmp_g[new_size - 1] = tmp_g[0];
      tmp_g.set_not_necessarily_closed();
      // Inserting the new generator.
      Linear_System::insert_pending(tmp_g);
    }
  assert(OK());
}

PPL::dimension_type
PPL::Generator_System::num_lines() const {
  // We are sure that this method is applied only to a matrix
  // that does not contain pending rows.
  assert(num_pending_rows() == 0);
  const Generator_System& gs = *this;
  dimension_type n = 0;
  // If the Linear_System happens to be sorted, take advantage of the fact
  // that lines are at the top of the system.
  if (is_sorted()) {
    dimension_type nrows = num_rows();
    for (dimension_type i = 0; i < nrows && gs[i].is_line(); ++i)
      ++n;
  }
  else
    for (dimension_type i = num_rows(); i-- > 0 ; )
      if (gs[i].is_line())
	++n;
  return n;
}

PPL::dimension_type
PPL::Generator_System::num_rays() const {
  // We are sure that this method is applied only to a matrix
  // that does not contain pending rows.
  assert(num_pending_rows() == 0);
  const Generator_System& gs = *this;
  dimension_type n = 0;
  // If the Linear_System happens to be sorted, take advantage of the fact
  // that rays and points are at the bottom of the system and
  // rays have the inhomogeneous term equal to zero.
  if (is_sorted()) {
    for (dimension_type i = num_rows(); i != 0 && gs[--i].is_ray_or_point(); )
      if (gs[i][0] == 0)
	++n;
  }
  else
    for (dimension_type i = num_rows(); i-- > 0 ; ) {
      const Generator& g = gs[i];
      if (g.is_ray_or_point() && g[0] == 0)
	++n;
    }
  return n;
}

PPL::Poly_Con_Relation
PPL::Generator_System::relation_with(const Constraint& c) const {
  // Note: this method is not public and it is the responsibility
  // of the caller to actually test for dimension compatibility.
  // We simply assert it.
  assert(space_dimension() >= c.space_dimension());
  // Number of generators: the case of an empty polyhedron
  // has already been filtered out by the caller.
  const dimension_type n_rows = num_rows();
  assert(n_rows > 0);
  const Generator_System& gs = *this;

  // `result' will keep the relation holding between the generators
  // we have seen so far and the constraint `c'.
  Poly_Con_Relation result = Poly_Con_Relation::saturates();

  switch (c.type()) {

  case Constraint::EQUALITY:
    {
      // The hyperplane defined by the equality `c' is included
      // in the set of points satisfying `c' (it is the same set!).
      result = result && Poly_Con_Relation::is_included();
      // The following integer variable will hold the scalar product sign
      // of either the first point or the first non-saturating ray we find.
      // If it is equal to 2, then it means that we haven't found such
      // a generator yet.
      int first_point_or_nonsaturating_ray_sign = 2;

      for (dimension_type i = n_rows; i-- > 0; ) {
	const Generator& g = gs[i];
	const int sp_sign = scalar_product_sign(c, g);
	// Checking whether the generator saturates the equality.
	// If that is the case, then we have to do something only if
	// the generator is a point.
	if (sp_sign == 0) {
	  if (g.is_point())
	    if (first_point_or_nonsaturating_ray_sign == 2)
	      // It is the first time that we find a point and
	      // we have not found a non-saturating ray yet.
	      first_point_or_nonsaturating_ray_sign = 0;
	    else
	      // We already found a point or a non-saturating ray.
	      if (first_point_or_nonsaturating_ray_sign != 0)
		return Poly_Con_Relation::strictly_intersects();
	}
	else
	  // Here we know that sp_sign != 0.
	  switch (g.type()) {

	  case Generator::LINE:
	    // If a line does not saturate `c', then there is a strict
	    // intersection between the points satisfying `c'
	    // and the points generated by `gs'.
	    return Poly_Con_Relation::strictly_intersects();

	  case Generator::RAY:
	    if (first_point_or_nonsaturating_ray_sign == 2) {
	      // It is the first time that we have a non-saturating ray
	      // and we have not found any point yet.
	      first_point_or_nonsaturating_ray_sign = sp_sign;
	      result = Poly_Con_Relation::is_disjoint();
	    }
	    else
	      // We already found a point or a non-saturating ray.
	      if (sp_sign != first_point_or_nonsaturating_ray_sign)
		return Poly_Con_Relation::strictly_intersects();
	    break;

	  case Generator::POINT:
	  case Generator::CLOSURE_POINT:
	    // NOTE: a non-saturating closure point is treated as
	    // a normal point.
	    if (first_point_or_nonsaturating_ray_sign == 2) {
	      // It is the first time that we find a point and
	      // we have not found a non-saturating ray yet.
	      first_point_or_nonsaturating_ray_sign = sp_sign;
	      result = Poly_Con_Relation::is_disjoint();
	    }
	    else
	      // We already found a point or a non-saturating ray.
	      if (sp_sign != first_point_or_nonsaturating_ray_sign)
		return Poly_Con_Relation::strictly_intersects();
	    break;
	  }
      }
    }
    break;

  case Constraint::NONSTRICT_INEQUALITY:
    {
      // The hyperplane implicitly defined by the non-strict inequality `c'
      // is included in the set of points satisfying `c'.
      result = result && Poly_Con_Relation::is_included();
      // The following boolean variable will be set to `false'
      // as soon as either we find (any) point or we find a
      // non-saturating ray.
      bool first_point_or_nonsaturating_ray = true;

      for (dimension_type i = n_rows; i-- > 0; ) {
	const Generator& g = gs[i];
	const int sp_sign = scalar_product_sign(c, g);
	// Checking whether the generator saturates the non-strict
	// inequality. If that is the case, then we have to do something
	// only if the generator is a point.
	if (sp_sign == 0) {
	  if (g.is_point())
	    if (first_point_or_nonsaturating_ray)
	      // It is the first time that we have a point and
	      // we have not found a non-saturating ray yet.
	      first_point_or_nonsaturating_ray = false;
	    else
	      // We already found a point or a non-saturating ray before.
	      if (result == Poly_Con_Relation::is_disjoint())
		// Since g saturates c, we have a strict intersection if
		// none of the generators seen so far are included in `c'.
		return Poly_Con_Relation::strictly_intersects();
	}
	else
	  // Here we know that sp_sign != 0.
	  switch (g.type()) {

	  case Generator::LINE:
	    // If a line does not saturate `c', then there is a strict
	    // intersection between the points satisfying `c' and
	    // the points generated by `gs'.
	    return Poly_Con_Relation::strictly_intersects();

	  case Generator::RAY:
	    if (first_point_or_nonsaturating_ray) {
	      // It is the first time that we have a non-saturating ray
	      // and we have not found any point yet.
	      first_point_or_nonsaturating_ray = false;
	      result = (sp_sign > 0)
		? Poly_Con_Relation::is_included()
		: Poly_Con_Relation::is_disjoint();
	    }
	    else {
	      // We already found a point or a non-saturating ray.
	      if ((sp_sign > 0
		   && result == Poly_Con_Relation::is_disjoint())
		  || (sp_sign < 0
		      && result.implies(Poly_Con_Relation::is_included())))
		// We have a strict intersection if either:
		// - `g' satisfies `c' but none of the generators seen
		//    so far are included in `c'; or
		// - `g' does not satisfy `c' and all the generators
		//    seen so far are included in `c'.
		return Poly_Con_Relation::strictly_intersects();
	      if (sp_sign > 0)
		// Here all the generators seen so far either saturate
		// or are included in `c'.
		// Since `g' does not saturate `c' ...
		result = Poly_Con_Relation::is_included();
	    }
	    break;

	  case Generator::POINT:
	  case Generator::CLOSURE_POINT:
	    // NOTE: a non-saturating closure point is treated as
	    // a normal point.
	    if (first_point_or_nonsaturating_ray) {
	      // It is the first time that we have a point and
	      // we have not found a non-saturating ray yet.
	      // - If point `g' saturates `c', then all the generators
	      //   seen so far saturate `c'.
	      // - If point `g' is included (but does not saturate) `c',
	      //   then all the generators seen so far are included in `c'.
	      // - If point `g' does not satisfy `c', then all the
	      //   generators seen so far are disjoint from `c'.
	      first_point_or_nonsaturating_ray = false;
	      if (sp_sign > 0)
		result = Poly_Con_Relation::is_included();
	      else if (sp_sign < 0)
		result = Poly_Con_Relation::is_disjoint();
	    }
	    else {
	      // We already found a point or a non-saturating ray before.
	      if ((sp_sign > 0
		   && result == Poly_Con_Relation::is_disjoint())
		  || (sp_sign < 0
		      && result.implies(Poly_Con_Relation::is_included())))
		// We have a strict intersection if either:
		// - `g' satisfies or saturates `c' but none of the
		//    generators seen so far are included in `c'; or
		// - `g' does not satisfy `c' and all the generators
		//    seen so far are included in `c'.
		return Poly_Con_Relation::strictly_intersects();
	      if (sp_sign > 0)
		// Here all the generators seen so far either saturate
		// or are included in `c'.
		// Since `g' does not saturate `c' ...
		result = Poly_Con_Relation::is_included();
	    }
	    break;
	  }
      }
    }
    break;

  case Constraint::STRICT_INEQUALITY:
    {
      // The hyperplane implicitly defined by the strict inequality `c'
      // is disjoint from the set of points satisfying `c'.
      result = result && Poly_Con_Relation::is_disjoint();
      // The following boolean variable will be set to `false'
      // as soon as either we find (any) point or we find a
      // non-saturating ray.
      bool first_point_or_nonsaturating_ray = true;
      for (dimension_type i = n_rows; i-- > 0; ) {
	const Generator& g = gs[i];
	// Using the reduced scalar product operator to avoid
	// both topology and num_columns mismatches.
	const int sp_sign = reduced_scalar_product_sign(c, g);
	// Checking whether the generator saturates the strict inequality.
	// If that is the case, then we have to do something
	// only if the generator is a point.
	if (sp_sign == 0) {
	  if (g.is_point())
	    if (first_point_or_nonsaturating_ray)
	      // It is the first time that we have a point and
	      // we have not found a non-saturating ray yet.
	      first_point_or_nonsaturating_ray = false;
	    else
	      // We already found a point or a non-saturating ray before.
	      if (result == Poly_Con_Relation::is_included())
		return Poly_Con_Relation::strictly_intersects();
	}
	else
	  // Here we know that sp_sign != 0.
	  switch (g.type()) {

	  case Generator::LINE:
	    // If a line does not saturate `c', then there is a strict
	    // intersection between the points satisfying `c' and the points
	    // generated by `gs'.
	    return Poly_Con_Relation::strictly_intersects();

	  case Generator::RAY:
	    if (first_point_or_nonsaturating_ray) {
	      // It is the first time that we have a non-saturating ray
	      // and we have not found any point yet.
	      first_point_or_nonsaturating_ray = false;
	      result = (sp_sign > 0)
		? Poly_Con_Relation::is_included()
		: Poly_Con_Relation::is_disjoint();
	    }
	    else {
	      // We already found a point or a non-saturating ray before.
	      if ((sp_sign > 0
		   && result.implies(Poly_Con_Relation::is_disjoint()))
		  ||
		  (sp_sign <= 0
		   && result == Poly_Con_Relation::is_included()))
		return Poly_Con_Relation::strictly_intersects();
	      if (sp_sign < 0)
		// Here all the generators seen so far either saturate
		// or are disjoint from `c'.
		// Since `g' does not saturate `c' ...
		result = Poly_Con_Relation::is_disjoint();
	    }
	    break;

	  case Generator::POINT:
	  case Generator::CLOSURE_POINT:
	    if (first_point_or_nonsaturating_ray) {
	      // It is the first time that we have a point and
	      // we have not found a non-saturating ray yet.
	      // - If point `g' saturates `c', then all the generators
	      //   seen so far saturate `c'.
	      // - If point `g' is included in (but does not saturate) `c',
	      //   then all the generators seen so far are included in `c'.
	      // - If point `g' strictly violates `c', then all the
	      //   generators seen so far are disjoint from `c'.
	      first_point_or_nonsaturating_ray = false;
	      if (sp_sign > 0)
		result = Poly_Con_Relation::is_included();
	      else if (sp_sign < 0)
		result = Poly_Con_Relation::is_disjoint();
	    }
	    else {
	      // We already found a point or a non-saturating ray before.
	      if ((sp_sign > 0
		   && result.implies(Poly_Con_Relation::is_disjoint()))
		  ||
		  (sp_sign <= 0
		   && result == Poly_Con_Relation::is_included()))
		return Poly_Con_Relation::strictly_intersects();
	      if (sp_sign < 0)
		// Here all the generators seen so far either saturate
		// or are disjoint from `c'.
		// Since `g' does not saturate `c' ...
		result = Poly_Con_Relation::is_disjoint();
	    }
	    break;
	  }
      }
    }
    break;
  }
  // We have seen all generators.
  return result;
}


bool
PPL::Generator_System::satisfied_by_all_generators(const Constraint& c) const {
  assert(c.space_dimension() <= space_dimension());

  // Setting `sp_fp' to the appropriate scalar product operator.
  // This also avoids problems when having _legal_ topology mismatches
  // (which could also cause a mismatch in the number of columns).
  int (*sps_fp)(const Linear_Row&, const Linear_Row&);
  if (c.is_necessarily_closed())
    sps_fp = PPL::scalar_product_sign;
  else
    sps_fp = PPL::reduced_scalar_product_sign;

  const Generator_System& gs = *this;
  switch (c.type()) {
  case Constraint::EQUALITY:
    // Equalities must be saturated by all generators.
    for (dimension_type i = gs.num_rows(); i-- > 0; )
      if (sps_fp(c, gs[i]) != 0)
	return false;
    break;
  case Constraint::NONSTRICT_INEQUALITY:
    // Non-strict inequalities must be saturated by lines and
    // satisfied by all the other generators.
    for (dimension_type i = gs.num_rows(); i-- > 0; ) {
      const Generator& g = gs[i];
      const int sp_sign = sps_fp(c, g);
      if (g.is_line()) {
	if (sp_sign != 0)
	  return false;
      }
      else
	// `g' is a ray, point or closure point.
	if (sp_sign < 0)
	  return false;
    }
    break;
  case Constraint::STRICT_INEQUALITY:
    // Strict inequalities must be saturated by lines,
    // satisfied by all generators, and must not be saturated by points.
    for (dimension_type i = gs.num_rows(); i-- > 0; ) {
      const Generator& g = gs[i];
      const int sp_sign = sps_fp(c, g);
      switch (g.type()) {
      case Generator::POINT:
	if (sp_sign <= 0)
	  return false;
	break;
      case Generator::LINE:
	if (sp_sign != 0)
	  return false;
	break;
      default:
	// `g' is a ray or closure point.
	if (sp_sign < 0)
	  return false;
	break;
      }
    }
    break;
  }
  // If we reach this point, `c' is satisfied by all generators.
  return true;
}


void
PPL::Generator_System::affine_image(dimension_type v,
			  const Linear_Expression& expr,
			  Coefficient_traits::const_reference denominator) {
  // `v' is the index of a column corresponding to
  // a "user" variable (i.e., it cannot be the inhomogeneous term,
  // nor the epsilon dimension of NNC polyhedra).
  assert(v > 0 && v <= space_dimension());
  assert(expr.space_dimension() <= space_dimension());
  assert(denominator > 0);

  const dimension_type n_columns = num_columns();
  const dimension_type n_rows = num_rows();
  Generator_System& x = *this;

  // Compute the numerator of the affine transformation and assign it
  // to the column of `*this' indexed by `v'.
  TEMP_INTEGER(numerator);
  for (dimension_type i = n_rows; i-- > 0; ) {
    Generator& row = x[i];
    scalar_product_assign(numerator, expr, row);
    std::swap(numerator, row[v]);
  }

  if (denominator != 1) {
    // Since we want integer elements in the matrix,
    // we multiply by the value of `denominator'
    // all the columns of `*this' having an index different from `v'.
    for (dimension_type i = n_rows; i-- > 0; )
      for (dimension_type j = n_columns; j-- > 0; )
	if (j != v)
	  x[i][j] *= denominator;
  }

  // If the mapping is not invertible we may have transformed
  // valid lines and rays into the origin of the space.
  const bool not_invertible = (v > expr.space_dimension() || expr[v] == 0);
  if (not_invertible)
    x.remove_invalid_lines_and_rays();
  // Strong normalization also resets the sortedness flag.
  x.strong_normalize();
}

void
PPL::Generator_System::ascii_dump(std::ostream& s) const {
  const Generator_System& x = *this;
  dimension_type x_num_rows = x.num_rows();
  dimension_type x_num_columns = x.num_columns();
  s << "topology " << (is_necessarily_closed()
		       ? "NECESSARILY_CLOSED"
		       : "NOT_NECESSARILY_CLOSED")
    << std::endl
    << x_num_rows << " x " << x_num_columns << ' '
    << (x.is_sorted() ? "(sorted)" : "(not_sorted)")
    << std::endl
    << "index_first_pending " << x.first_pending_row()
    << std::endl;
  for (dimension_type i = 0; i < x.num_rows(); ++i) {
    for (dimension_type j = 0; j < x.num_columns(); ++j)
      s << x[i][j] << ' ';
    switch (x[i].type()) {
    case Generator::LINE:
      s << "L";
      break;
    case Generator::RAY:
      s << "R";
      break;
    case Generator::POINT:
      s << "P";
      break;
    case Generator::CLOSURE_POINT:
      s << "C";
      break;
    }
    if (x[i].is_virtual())
      s << " (v)";
    s << std::endl;
  }
}

bool
PPL::Generator_System::ascii_load(std::istream& s) {
  std::string str;
  if (!(s >> str) || str != "topology")
    return false;
  if (!(s >> str))
    return false;
  if (str == "NECESSARILY_CLOSED")
    set_necessarily_closed();
  else {
    if (str != "NOT_NECESSARILY_CLOSED")
      return false;
    set_not_necessarily_closed();
  }

  dimension_type nrows;
  dimension_type ncols;
  if (!(s >> nrows))
    return false;
  if (!(s >> str))
    return false;
  if (!(s >> ncols))
      return false;
  resize_no_copy(nrows, ncols);

  if (!(s >> str) || (str != "(sorted)" && str != "(not_sorted)"))
    return false;
  set_sorted(str == "(sorted)");
  dimension_type index;
  if (!(s >> str) || str != "index_first_pending")
    return false;
  if (!(s >> index))
    return false;
  set_index_first_pending_row(index);

  Generator_System& x = *this;
  for (dimension_type i = 0; i < x.num_rows(); ++i) {
    for (dimension_type j = 0; j < x.num_columns(); ++j)
      if (!(s >> x[i][j]))
	return false;

    if (!(s >> str))
      return false;
    if (str == "L")
      x[i].set_is_line();
    else
      x[i].set_is_ray_or_point();

    if (s >> str) {
      if (str == "(v)") {
	Grid::mark_virtual(x[i]);
	continue;
      }
      return false;
    }

    // Checking for equality of actual and declared types.
    switch (x[i].type()) {
    case Generator::LINE:
      if (str == "L")
	continue;
      break;
    case Generator::RAY:
      if (str == "R")
	continue;
      break;
    case Generator::POINT:
      if (str == "P")
	continue;
      break;
    case Generator::CLOSURE_POINT:
      if (str == "C")
	continue;
      break;
    }
    // Reaching this point means that the input was illegal.
    return false;
  }
  // Checking for well-formedness.
  //assert(OK());   // FIX temp, for grid
  return true;
}

void
PPL::Generator_System::remove_invalid_lines_and_rays() {
  // The origin of the vector space cannot be a valid line/ray.
  // NOTE: the following swaps will mix generators without even trying
  // to preserve sortedness: as a matter of fact, it will almost always
  // be the case that the input generator system is NOT sorted.
  Generator_System& gs = *this;
  dimension_type n_rows = gs.num_rows();
  if (num_pending_rows() == 0) {
    for (dimension_type i = n_rows; i-- > 0; ) {
      Generator& g = gs[i];
      if (g[0] == 0 && g.all_homogeneous_terms_are_zero()) {
	// An invalid line/ray has been found.
	--n_rows;
	std::swap(g, gs[n_rows]);
	gs.set_sorted(false);
      }
    }
    set_index_first_pending_row(n_rows);
  }
  else {
    // If the matrix has some pending rows, we can not
    // swap the "normal" rows with the pending rows. So
    // we must put at the end of the "normal" rows
    // the invalid "normal" rows, put them at the end
    // of the matrix, find the invalid rows in the pending
    // part and then erase the invalid rows that now
    // are in the bottom part of the matrix.
    assert(num_pending_rows() > 0);
    dimension_type first_pending = first_pending_row();
    for (dimension_type i = first_pending; i-- > 0; ) {
      Generator& g = gs[i];
      if (g[0] == 0 && g.all_homogeneous_terms_are_zero()) {
	// An invalid line/ray has been found.
	--first_pending;
	std::swap(g, gs[first_pending]);
	gs.set_sorted(false);
      }
    }
    const dimension_type num_invalid_rows
      = first_pending_row() - first_pending;
    set_index_first_pending_row(first_pending);
    for (dimension_type i = 0; i < num_invalid_rows; ++i)
      std::swap(gs[n_rows - i], gs[first_pending + i]);
    n_rows -= num_invalid_rows;
    for (dimension_type i = n_rows; i-- > first_pending; ) {
      Generator& g = gs[i];
      if (g[0] == 0 && g.all_homogeneous_terms_are_zero()) {
	// An invalid line/ray has been found.
	--n_rows;
	std::swap(g, gs[n_rows]);
	gs.set_sorted(false);
      }
    }
  }
  gs.erase_to_end(n_rows);
}

bool
PPL::Generator_System::OK() const {
  // A Generator_System must be a valid Linear_System; do not check for
  // strong normalization, since this will be done when
  // checking each individual generator.
  if (!Linear_System::OK(false))
    return false;

  // Checking each generator in the system.
  for (dimension_type i = num_rows(); i-- > 0; ) {
    const Generator& g = (*this)[i];
    if (!g.OK())
      return false;
  }

  // All checks passed.
  return true;
}

/*! \relates Parma_Polyhedra_Library::Generator_System */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s, const Generator_System& gs) {
  Generator_System::const_iterator i = gs.begin();
  const Generator_System::const_iterator gs_end = gs.end();
  if (i == gs_end)
    s << "false";
  else
    while (i != gs_end) {
      s << *i++;
      if (Grid::virtual_row(*i))
	s << " (v)";
      if (i != gs_end)
	s << ", ";
    }
  return s;
}
