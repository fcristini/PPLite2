/* Test Pointset_Powerset<PH>::add_disjunct().
        Pointset_Powerset<PH>::drop_disjunct().
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

#include "ppl_test.hh"

namespace {

// Powerset of C polyhedra: add_disjunct().
bool
test01() {
  Variable x(0);
  Constraint_System cs;
  Pointset_Powerset<C_Polyhedron> c_ps(1, EMPTY);

  cs.clear();
  cs.insert(x >= 0);
  cs.insert(x <= 2);
  c_ps.add_disjunct(C_Polyhedron(cs));

  cs.clear();
  cs.insert(x >= 1);
  cs.insert(x <= 3);
  c_ps.add_disjunct(C_Polyhedron(cs));

  c_ps.add_constraint(x == 1);

  Pointset_Powerset<NNC_Polyhedron> nnc_ps(c_ps);

  Pointset_Powerset<C_Polyhedron>::const_iterator c_i = c_ps.begin();
  C_Polyhedron c_phi = c_i->pointset();
  print_constraints(c_phi, "*** c_phi ***");
  Pointset_Powerset<NNC_Polyhedron>::const_iterator nnc_i = nnc_ps.begin();
  NNC_Polyhedron nnc_phi = nnc_i->pointset();
  print_constraints(nnc_phi, "*** nnc_phi ***");

  return c_ps.OK() && nnc_ps.OK();
}

// Powerset of NNC polyhedra: add_disjunct().
bool
test02() {
  Variable x(0);
  Constraint_System cs;
  Pointset_Powerset<NNC_Polyhedron> nnc_ps(1, EMPTY);

  cs.clear();
  cs.insert(x > 0);
  cs.insert(x <= 1);
  nnc_ps.add_disjunct(NNC_Polyhedron(cs));

  cs.clear();
  cs.insert(x >= 0);
  cs.insert(x < 1);
  nnc_ps.add_disjunct(NNC_Polyhedron(cs));

  Pointset_Powerset<C_Polyhedron> c_ps(nnc_ps);

  Pointset_Powerset<C_Polyhedron>::const_iterator c_i = c_ps.begin();
  C_Polyhedron c_phi = c_i->pointset();
  print_constraints(c_phi, "*** c_phi ***");
  Pointset_Powerset<NNC_Polyhedron>::const_iterator nnc_i = nnc_ps.begin();
  NNC_Polyhedron nnc_phi = nnc_i->pointset();
  print_constraints(nnc_phi, "*** nnc_phi ***");

  return nnc_ps.OK() && c_ps.OK();
}

// Powerset of C polyhedra: add_disjunct() and drop_disjunct().
bool
test03() {
  Variable x(0);
  Pointset_Powerset<C_Polyhedron> c_ps(1, EMPTY);
  Constraint_System cs;
  cs.insert(x >= 0);
  cs.insert(x <= 2);
  Constraint_System cs1 = cs;
  c_ps.add_disjunct(C_Polyhedron(cs));
  c_ps.drop_disjunct(c_ps.begin());

  bool ok = c_ps.empty();

  Constraint_System cs2 = cs1;
  c_ps.add_disjunct(C_Polyhedron(cs1));

  cs.insert(x >= 0);
  cs.insert(x <= 3);
  c_ps.add_disjunct(C_Polyhedron(cs));
  c_ps.drop_disjuncts(c_ps.begin(), c_ps.end());

  bool ok1 = c_ps.empty();

  return ok && ok1;
}

// Powerset of C polyhedra: add_disjunct().
bool
test04() {
  Variable x(0);
  Variable y(1);
  Pointset_Powerset<C_Polyhedron> c_ps(2, EMPTY);
  Constraint_System cs;
  cs.insert(x >= 0);
  cs.insert(x <= 2);
  C_Polyhedron ph(2);
  ph.add_constraints(cs);
  c_ps.add_disjunct(ph);

  Constraint_System cs1;
  cs1.insert(y >= 3);
  cs1.insert(y <= 5);
  C_Polyhedron ph1(2);
  ph1.add_constraints(cs1);
  c_ps.add_disjunct(ph1);

  Pointset_Powerset<C_Polyhedron>::const_iterator i = c_ps.begin();
  C_Polyhedron phi = i->pointset();
  i++;
  C_Polyhedron phi1 = i->pointset();

  bool ok = phi.OK() && phi == ph;

  print_constraints(ph, "*** ph ***");
  print_constraints(phi, "*** phi ***");

  bool ok1 = phi1.OK() && phi1 == ph1;

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(phi1, "*** phi1 ***");

  phi.upper_bound_assign(phi1);
  print_constraints(phi, "*** phi ***");

  return ok && ok1;
}

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
  DO_TEST(test02);
  DO_TEST(test03);
  DO_TEST(test04);
END_MAIN
