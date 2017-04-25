/* Polyhedron class implementation: non-inline template functions.
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2017 BUGSENG srl (http://bugseng.com)

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The PPL is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://bugseng.com/products/ppl/ . */

#ifndef PPL_Polyhedron_templates_hh
#define PPL_Polyhedron_templates_hh 1

#include "Generator_defs.hh"
#include "MIP_Problem_defs.hh"
#include "Linear_Form_defs.hh"
// For static method overflows.
#include <algorithm>
#include <deque>

namespace Parma_Polyhedra_Library {

template <typename Partial_Function>
void
Polyhedron::map_space_dimensions(const Partial_Function& pfunc) {
  if (space_dim == 0) {
    return;
  }
  if (pfunc.has_empty_codomain()) {
    // All dimensions vanish: the polyhedron becomes zero_dimensional.
    if (marked_empty()
        || (has_pending_constraints()
            && !remove_pending_to_obtain_generators())
        || (!generators_are_up_to_date() && !update_generators())) {
      // Removing all dimensions from the empty polyhedron.
      space_dim = 0;
      con_sys.clear();
    }
    else {
      // Removing all dimensions from a non-empty polyhedron.
      set_zero_dim_univ();
    }

    PPL_ASSERT_HEAVY(OK());
    return;
  }

  const dimension_type new_space_dimension = pfunc.max_in_codomain() + 1;

  if (new_space_dimension == space_dim) {
    // The partial function `pfunc' is indeed total and thus specifies
    // a permutation, that is, a renaming of the dimensions.  For
    // maximum efficiency, we will simply permute the columns of the
    // constraint system and/or the generator system.

    std::vector<Variable> cycle;
    cycle.reserve(space_dim);

    // Used to mark elements as soon as they are inserted in a cycle.
    std::deque<bool> visited(space_dim);

    for (dimension_type i = space_dim; i-- > 0; ) {
      if (visited[i]) {
        continue;
      }

      dimension_type j = i;
      do {
        visited[j] = true;
        // The following initialization is only to make the compiler happy.
        dimension_type k = 0;
        if (!pfunc.maps(j, k)) {
          throw_invalid_argument("map_space_dimensions(pfunc)",
                                 " pfunc is inconsistent");
        }
        if (k == j) {
          break;
        }

        cycle.push_back(Variable(j));
        // Go along the cycle.
        j = k;
      } while (!visited[j]);

      // End of cycle.

      // Permute all that is up-to-date.  Notice that the contents of
      // the saturation matrices is unaffected by the permutation of
      // columns: they remain valid, if they were so.
      if (constraints_are_up_to_date()) {
        con_sys.permute_space_dimensions(cycle);
      }

      if (generators_are_up_to_date()) {
        gen_sys.permute_space_dimensions(cycle);
      }

      cycle.clear();
    }

    PPL_ASSERT_HEAVY(OK());
    return;
  }

  // If control gets here, then `pfunc' is not a permutation and some
  // dimensions must be projected away.

  // If there are pending constraints, using `generators()' we process them.
  const Generator_System& old_gensys = generators();

  if (old_gensys.has_no_rows()) {
    // The polyhedron is empty.
    Polyhedron new_polyhedron(topology(), new_space_dimension, EMPTY);
    m_swap(new_polyhedron);
    PPL_ASSERT_HEAVY(OK());
    return;
  }

  // Make a local copy of the partial function.
  std::vector<dimension_type> pfunc_maps(space_dim, not_a_dimension());
  for (dimension_type j = space_dim; j-- > 0; ) {
    dimension_type pfunc_j;
    if (pfunc.maps(j, pfunc_j)) {
      pfunc_maps[j] = pfunc_j;
    }
  }

  Generator_System new_gensys;
  for (Generator_System::const_iterator i = old_gensys.begin(),
         old_gensys_end = old_gensys.end(); i != old_gensys_end; ++i) {
    const Generator& old_g = *i;
    const Generator::expr_type old_e = old_g.expression();
    Linear_Expression expr;
    expr.set_space_dimension(new_space_dimension);
    bool all_zeroes = true;
    for (Generator::expr_type::const_iterator j = old_e.begin(),
          j_end = old_e.end(); j != j_end; ++j) {
      const dimension_type mapped_id = pfunc_maps[j.variable().id()];
      if (mapped_id != not_a_dimension()) {
        add_mul_assign(expr, *j, Variable(mapped_id));
        all_zeroes = false;
      }
    }
    switch (old_g.type()) {
    case Generator::LINE:
      if (!all_zeroes) {
        new_gensys.insert(line(expr));
      }
      break;
    case Generator::RAY:
      if (!all_zeroes) {
        new_gensys.insert(ray(expr));
      }
      break;
    case Generator::POINT:
      // A point in the origin has all zero homogeneous coefficients.
      new_gensys.insert(point(expr, old_g.divisor()));
      break;
    case Generator::CLOSURE_POINT:
      // A closure point in the origin has all zero homogeneous coefficients.
      new_gensys.insert(closure_point(expr, old_g.divisor()));
      break;
    }
  }
  Polyhedron new_polyhedron(topology(), new_gensys);
  m_swap(new_polyhedron);
  PPL_ASSERT_HEAVY(OK(true));
}

template <typename C>
void
Polyhedron::throw_dimension_incompatible(const char* method,
                                         const char* lf_name,
                                         const Linear_Form<C>& lf) const {
  throw_dimension_incompatible(method, lf_name, lf.space_dimension());
}

template <typename Input>
Input&
Polyhedron::check_obj_space_dimension_overflow(Input& input,
                                               const Topology topol,
                                               const char* method,
                                               const char* reason) {
  check_space_dimension_overflow(input.space_dimension(),
                                 max_space_dimension(),
                                 topol, method, reason);
  return input;
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_Polyhedron_templates_hh)
