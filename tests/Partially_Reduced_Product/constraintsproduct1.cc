/* Test Partially_Reduced_Product<>:: Shrink_Using_Congruences_Reduction()
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

using namespace Parma_Polyhedra_Library::IO_Operators;

typedef NNC_Polyhedron Poly;

typedef Domain_Product<Poly, Grid>::Constraints_Product PolyGrid;

namespace {

// Constraints_Reduction with non-strict constraints and
// equality found. Positive coefficients.
bool
test01() {
  Variable A(0);
  Variable B(1);

  PolyGrid cp(2);
  Constraint_System cs;
  cs.insert(3*A >= 7);
  cs.insert(3*A <= 7);
  cp.refine_with_constraints(cs);

  PolyGrid known_cp(2);

  known_cp.refine_with_constraint(3*A == 7);

  bool ok = cp.OK();

  print_congruences(cp, "*** after ok check: cp congruences ***");
  print_constraints(cp, "*** after ok check: cp constraints ***");

  if (ok) {
    ok = ok && cp == known_cp;
    print_congruences(cp, "*** after known_cp check: cp congruences ***");
    print_constraints(cp, "*** after known_cp check: cp constraints ***");
  }

  return ok;
}

// Constraints_Reduction with non-strict constraints and
// equality found. Negative coefficients.
bool
test02() {
  Variable A(0);
  Variable B(1);

  PolyGrid cp(2);
  Constraint_System cs;
  cs.insert(2*A >= -9);
  cs.insert(2*A <= -9);
  cp.refine_with_constraints(cs);

  PolyGrid known_cp(2);

  known_cp.refine_with_constraint(2*A == -9);

  bool ok = cp.OK();

  print_congruences(cp, "*** after ok check: cp congruences ***");
  print_constraints(cp, "*** after ok check: cp constraints ***");

  if (ok) {
    ok = ok && cp == known_cp;

    print_congruences(cp, "*** after known_cp check: cp congruences ***");
    print_constraints(cp, "*** after known_cp check: cp constraints ***");
  }

  return ok;
}

// Constraints_Reduction with strict lower bound and an equality
// is found.
bool
test03() {
  Variable A(0);
  Variable B(1);

  PolyGrid cp(2);
  Constraint_System cs;
  cs.insert(A > 0);
  cs.insert(A <= 0);
  cp.refine_with_constraints(cs);

  PolyGrid known_cp(2, EMPTY);

  bool ok = cp.OK();

  print_congruences(cp, "*** after ok check: cp congruences ***");
  print_constraints(cp, "*** after ok check: cp constraints ***");

  if (ok) {
    ok = ok && cp == known_cp;

    print_congruences(cp, "*** after known_cp check: cp congruences ***");
    print_constraints(cp, "*** after known_cp check: cp constraints ***");
  }

  return ok;
}

// Constraints_Reduction with strict upper bound and an equality
// is found.
bool
test04() {
  Variable A(0);
  Variable B(1);

  PolyGrid cp(2);
  Constraint_System cs;
  cs.insert(A >= 1);
  cs.insert(A < 3);
  cp.refine_with_constraints(cs);
  cp.refine_with_congruence((A %= 1)/ 0);

  PolyGrid known_cp(2);

  known_cp.refine_with_constraint(A == 1);

  bool ok = cp.OK();

  print_congruences(cp, "*** after ok check: cp congruences ***");
  print_constraints(cp, "*** after ok check: cp constraints ***");

  if (ok) {
    ok = ok && cp == known_cp;

    print_congruences(cp, "*** after known_cp check: cp congruences ***");
    print_constraints(cp, "*** after known_cp check: cp constraints ***");
  }

  return ok;
}

// Constraints_Reduction where emptiness is found.
bool
test05() {
  Variable A(0);
  Variable B(1);

  PolyGrid cp(2);
  Constraint_System cs;
  cs.insert(A >= 1);
  cs.insert(A <= 2);
  cp.refine_with_constraints(cs);
  cp.refine_with_congruence((A %= 0)/ 0);

  PolyGrid known_cp(2, EMPTY);

  bool ok = cp.OK();

  print_congruences(cp, "*** after ok check: cp congruences ***");
  print_constraints(cp, "*** after ok check: cp constraints ***");

  if (ok) {
    ok = cp == known_cp;

    print_congruences(cp, "*** after known_cp check: cp congruences ***");
    print_constraints(cp, "*** after known_cp check: cp constraints ***");
  }

  return ok;
}

// Constraints_Reduction where emptiness is found.
bool
test06() {
  Variable A(0);
  Variable B(1);

  PolyGrid cp(2);
  Constraint_System cs;
  cs.insert(A >= 1);
  cs.insert(A <= 1);
  cp.refine_with_constraints(cs);
  cp.refine_with_congruence((A %= 0)/ 2);

  PolyGrid known_cp(2, EMPTY);

  bool ok = cp.OK();

  print_congruences(cp, "*** after ok check: cp congruences ***");
  print_constraints(cp, "*** after ok check: cp constraints ***");

  if (ok) {
    ok = cp == known_cp;

    print_congruences(cp, "*** after known_cp check: cp congruences ***");
    print_constraints(cp, "*** after known_cp check: cp constraints ***");
  }

  return ok;
}

// Constraints_Reduction that calls constraints()
// and hence reduce().
bool
test07() {
  Variable A(0);

  PolyGrid cp(1);
  Constraint_System cs;
  cs.insert(A >= 1);
  cs.insert(A <= 2);
  cp.refine_with_constraints(cs);
  cp.refine_with_congruence((A %= 0)/ 2);

  bool ok = cp.OK();

  Constraint_System cs1 = cp.constraints();

  PolyGrid known_cp(1);
  known_cp.refine_with_constraints(cs1);
  known_cp.refine_with_congruence((A %= 0)/ 2);

  print_congruences(cp, "*** after ok check: cp congruences ***");
  print_constraints(cp, "*** after ok check: cp constraints ***");

  if (ok) {
    ok = (cp == known_cp);
    print_constraints(cp,
                      "*** after known_cp check: cp constraints ***");
    print_congruences(cp,
                      "*** after known_cp check: cp congruences ***");
    if (!ok) {
      print_constraints(known_cp,
                        "*** known_cp constraints ***");
      print_congruences(known_cp,
                        "*** known_cp congruences ***");
    }
  }

  return ok;
}

// space_dimension()
bool
test10() {
  Variable A(0);
  Variable E(4);

  Constraint_System cs;
  cs.insert(A + E <= 9);
  cs.insert(A + E >= 9);

  PolyGrid cp(5);
  cp.refine_with_constraints(cs);

  bool cons_ok = (cp.space_dimension() == 5);

  print_congruences(cp, "*** cp congruences ***");
  print_constraints(cp, "*** cp constraints ***");

  return cons_ok;
}

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
  DO_TEST(test02);
  DO_TEST(test03);
  DO_TEST(test04);
  DO_TEST(test05);
  DO_TEST(test06);
  DO_TEST(test07);
  DO_TEST(test10);
END_MAIN
