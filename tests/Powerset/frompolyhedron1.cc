/* Test Pointset_Powerset<PH>::Pointset_Powerset(C_Polyhedron),
        Pointset_Powerset<PH>::Pointset_Powerset(NNC_Polyhedron).
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

// Constructs the powerset of polyhedra from an empty polyhedron.
bool
test01() {
  C_Polyhedron c_ph(0, EMPTY);
  Pointset_Powerset<C_Polyhedron> c_ps(c_ph);

  bool ok = (c_ps.OK() && c_ps.is_empty() && c_ps.space_dimension() == 0);

  NNC_Polyhedron nnc_ph(0, EMPTY);
  Pointset_Powerset<NNC_Polyhedron> nnc_ps(nnc_ph);

  ok = ok
    && (nnc_ps.OK() && nnc_ps.is_empty() && nnc_ps.space_dimension() == 0);

  return ok;
}

// Constructs the powerset of polyhedra from a closed polyhedron.
bool
test02() {
  Variable x(0);
  Variable y(1);
  Variable z(2);
  Variable w(3);

  C_Polyhedron c_ph(4);
  c_ph.add_constraint(x <= 2);
  c_ph.add_constraint(z == 1);
  NNC_Polyhedron nnc_ph(c_ph);

  Pointset_Powerset<C_Polyhedron> c_pps1(c_ph);
  Pointset_Powerset<C_Polyhedron> c_pps2(4, EMPTY);
  c_pps2.add_disjunct(c_ph);

  Pointset_Powerset<NNC_Polyhedron> nnc_pps1(c_ph);
  Pointset_Powerset<NNC_Polyhedron> nnc_pps2(4, EMPTY);
  nnc_pps2.add_disjunct(nnc_ph);

  bool ok = (c_pps1 == c_pps2 && nnc_pps1 == nnc_pps2);

  Pointset_Powerset<C_Polyhedron>::const_iterator c_i = c_pps1.begin();
  C_Polyhedron c_phi = c_i->pointset();
  print_constraints(c_phi, "*** c_phi ***");
  Pointset_Powerset<NNC_Polyhedron>::const_iterator nnc_i = nnc_pps1.begin();
  NNC_Polyhedron nnc_phi = nnc_i->pointset();
  print_constraints(nnc_phi, "*** nnc_phi ***");

  return ok && c_pps1.OK() && nnc_pps1.OK();
}

// Constructs the powerset of polyhedra from an nnc polyhedron.
bool
test03() {
  Variable x(0);
  Variable y(1);
  Variable z(2);
  Variable w(3);

  NNC_Polyhedron nnc_ph(4);
  nnc_ph.add_constraint(x <= 2);
  nnc_ph.add_constraint(z == 1);
  C_Polyhedron c_ph(nnc_ph);

  Pointset_Powerset<C_Polyhedron> c_pps1(nnc_ph);
  Pointset_Powerset<C_Polyhedron> c_pps2(4, EMPTY);
  c_pps2.add_disjunct(c_ph);

  Pointset_Powerset<NNC_Polyhedron> nnc_pps1(nnc_ph);
  Pointset_Powerset<NNC_Polyhedron> nnc_pps2(4, EMPTY);
  nnc_pps2.add_disjunct(nnc_ph);

  bool ok = (c_pps1 == c_pps2 && nnc_pps1 == nnc_pps2);

  Pointset_Powerset<C_Polyhedron>::const_iterator c_i = c_pps1.begin();
  C_Polyhedron c_phi = c_i->pointset();
  print_constraints(c_phi, "*** c_phi ***");
  Pointset_Powerset<NNC_Polyhedron>::const_iterator nnc_i = nnc_pps1.begin();
  NNC_Polyhedron nnc_phi = nnc_i->pointset();
  print_constraints(nnc_phi, "*** nnc_phi ***");

  return ok && c_pps1.OK() && nnc_pps1.OK();
}

// Constructs the powerset of nnc polyhedra from a powerset of
// closed polyhedra.
bool
test04() {
  Variable x(0);
  Variable y(1);

  C_Polyhedron ph(2);
  ph.add_constraint(2*x == 1);
  ph.add_constraint(y >= 0);

  Pointset_Powerset<C_Polyhedron> pps_c(ph);

  Pointset_Powerset<NNC_Polyhedron> pps(pps_c);

  Pointset_Powerset<NNC_Polyhedron> known_pps(2);

  known_pps.add_constraint(2*x == 1);
  known_pps.add_constraint(y >= 0);

  bool ok = (pps == known_pps);

  Pointset_Powerset<NNC_Polyhedron>::const_iterator i = pps.begin();
  NNC_Polyhedron phi = i->pointset();
  print_constraints(phi, "*** phi ***");

  return ok;
}

// Constructs the powerset of nnc polyhedra from a powerset of
// closed polyhedra.
bool
test05() {
  Variable x(0);
  Variable y(1);

  Pointset_Powerset<C_Polyhedron> pps(2);

  pps.add_constraint(x >= 1);
  pps.add_constraint(x <= 1);
  pps.add_constraint(y >= 0);

  Pointset_Powerset<C_Polyhedron> pps1(pps, POLYNOMIAL_COMPLEXITY);

  Pointset_Powerset<C_Polyhedron>::const_iterator i1 = pps.begin();
  C_Polyhedron phi1 = i1->pointset();
  print_constraints(phi1, "*** phi1 ***");

  pps.OK();

  Pointset_Powerset<C_Polyhedron>::const_iterator i = pps.begin();
  C_Polyhedron phi = i->pointset();
  phi.OK();
  print_constraints(phi, "*** phi after ok check ***");

  bool ok = true;

  return ok;
}

// Constructs the powerset of grids from a polyhedron.
bool
test18() {
  Variable x(0);
  Variable y(1);
  Variable z(2);
  Variable w(3);

  C_Polyhedron ph(4);
  ph.add_constraint(x >= 2);
  ph.add_constraint(z >= 1);
  ph.add_constraint(x + z <= 3);
  C_Polyhedron ph1(4);
  ph1.add_constraint(x >= 2);
  ph1.add_constraint(z >= 1);
  ph1.add_constraint(x + z <= 3);

  // With the default complexity, the implied equalities x = 2 and z = 1.
  // are found
  Pointset_Powerset<Grid> pps(ph);
  // With the polynomial complexity, no implied equalities are found.
  Pointset_Powerset<Grid> pps1(ph1, POLYNOMIAL_COMPLEXITY);

  Pointset_Powerset<Grid> known_pps(4);
  known_pps.add_congruence((x %= 2) / 0);
  known_pps.add_congruence((z %= 1) / 0);
  Pointset_Powerset<Grid> known_pps1(4);

  bool ok = (pps == known_pps && pps1 == known_pps1);

  Pointset_Powerset<Grid>::const_iterator i = pps.begin();
  Grid gri = i->pointset();
  print_congruences(gri, "*** gri ***");
  Pointset_Powerset<Grid>::const_iterator i1 = pps1.begin();
  Grid gri1 = i1->pointset();
  print_congruences(gri1, "*** gri1 ***");

  return ok && pps.OK() && pps1.OK();
}

// Constructs the powerset of grids from a polyhedron whose constraints
// are inconsistent (i.e., is empty but not marked as empty).
bool
test19() {
  Variable x(0);
  Variable y(1);
  Variable z(2);
  Variable w(3);

  C_Polyhedron ph(4);
  ph.add_constraint(x >= 2);
  ph.add_constraint(z >= 1);
  ph.add_constraint(x + z <= 2);

  C_Polyhedron ph1(ph);

  // With the default complexity, the built powerset is empty.
  Pointset_Powerset<Grid> pps(ph);
  // With the polynomial complexity, the built powerset is the universe.
  Pointset_Powerset<Grid> pps1(ph1, POLYNOMIAL_COMPLEXITY);

  Pointset_Powerset<Grid> known_pps(4, EMPTY);
  Pointset_Powerset<Grid> known_pps1(4);

  bool ok = (pps == known_pps && pps1 == known_pps1);

  Pointset_Powerset<Grid>::const_iterator i1 = pps1.begin();
  Grid gri1 = i1->pointset();
  print_congruences(gri1, "*** gri1 ***");

  return ok && pps.OK() && pps1.OK();
}

// Constructs the powerset of grids from an empty polyhedron.
bool
test20() {
  Variable x(0);
  Variable y(1);

  NNC_Polyhedron ph(2, EMPTY);

  Pointset_Powerset<Grid> pps(ph);

  Pointset_Powerset<Grid> known_pps(2, EMPTY);

  bool ok = (pps == known_pps);

  return ok;
}

// Constructs the powerset of grids from a powerset of polyhedra.
bool
test21() {
  Variable x(0);
  Variable y(1);

  Constraint_System cs;
  cs.insert(2*x >= 1);
  cs.insert(2*x + y <= 1);
  cs.insert(y >= 0);
  C_Polyhedron ph1(cs);
  C_Polyhedron ph2(cs);

  Pointset_Powerset<C_Polyhedron> pps1_c(ph1, POLYNOMIAL_COMPLEXITY);
  Pointset_Powerset<C_Polyhedron> pps2_c(ph2);

  Pointset_Powerset<Grid> pps1(pps1_c, POLYNOMIAL_COMPLEXITY);
  Pointset_Powerset<Grid> pps2(pps2_c);

  Pointset_Powerset<Grid> known_pps1(2);
  Pointset_Powerset<Grid> known_pps2(2);
  known_pps2.add_constraint(2*x == 1);
  known_pps2.add_constraint(y == 0);

  bool ok = (pps1 == known_pps1 && pps2 == known_pps2);

  Pointset_Powerset<Grid>::const_iterator i1 = pps1.begin();
  Grid gri1 = i1->pointset();
  print_congruences(gri1, "*** gri1 ***");

  Pointset_Powerset<Grid>::const_iterator i2 = pps2.begin();
  Grid gri2 = i2->pointset();
  print_congruences(gri2, "*** gri2 ***");

  return ok;
}

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
  DO_TEST(test02);
  DO_TEST(test03);
  DO_TEST(test04);
  DO_TEST(test05);
  DO_TEST(test18);
  DO_TEST(test19);
  DO_TEST(test20);
  DO_TEST(test21);
END_MAIN
