/* Test Product<NNC_Polyhedron, Grid>::bounds_from_above() and
   Product<NNC_Polyhedron, Grid>::bounds_from_below()
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
#include "partially_reduced_product_test.hh"

typedef NNC_Polyhedron DOMAIN1;
typedef Grid DOMAIN2;
typedef Domain_Product<DOMAIN1x, DOMAIN2x>::Constraints_Product Product;

namespace {

// Empty.
bool
test01() {
  Product prp(7, EMPTY);

  bool ok = (prp.bounds_from_above(Linear_Expression(0))
             && prp.bounds_from_below(Linear_Expression(0)));

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Zero dimension empty.
bool
test02() {
  Product prp(0, EMPTY);

  bool ok = (prp.bounds_from_above(Linear_Expression(3))
             && prp.bounds_from_below(Linear_Expression(3)));

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Zero dimension universe.
bool
test03() {
  Product prp(0);

  bool ok = (prp.bounds_from_above(Linear_Expression(1))
             && prp.bounds_from_below(Linear_Expression(1)));

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Point.
bool
test04() {
  Variable A(0);
  Variable B(1);

  Product prp(2);
  prp.refine_with_constraint(A == 1);
  prp.refine_with_constraint(3*B == 2);

  Linear_Expression le = A + B;
  bool ok = prp.bounds_from_above(le)
    && prp.bounds_from_below(le);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// only one component is bounded.
bool
test05() {
  Variable A(0);
  Variable B(1);

  Product prp(2);
  prp.refine_with_constraint(A - B >= 1);
  prp.refine_with_constraint(A - B <= 1);
  prp.refine_with_congruence(3*B %= 2);

  Linear_Expression le = A - B;
  bool ok = prp.bounds_from_above(le)
    && prp.bounds_from_below(le);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Line and neither component is bounded.
bool
test06() {
  Variable A(0);
  Variable B(1);

  Product prp(2);
  prp.refine_with_constraint(B == 1);

  Linear_Expression le = 2*A - B;

  bool ok = !prp.bounds_from_above(le)
    && !prp.bounds_from_below(le);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Empty. maximize() and minimize()
bool
test07() {
  Product prp(7, EMPTY);

  Coefficient extr_n;
  Coefficient extr_d;
  bool dummy;

  bool ok = (!prp.maximize(Linear_Expression(0), extr_n, extr_d, dummy));

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Zero dimension empty.
bool
test08() {
  Product prp(0, EMPTY);

  Coefficient extr_n;
  Coefficient extr_d;
  bool dummy;
  Generator pnt(point());

  bool ok = !prp.maximize(Linear_Expression(0), extr_n, extr_d, dummy)
    && !prp.maximize(Linear_Expression(0), extr_n, extr_d, dummy, pnt);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Zero dimension universe.
bool
test09() {
  Product prp(0);

  Coefficient extr_n, extr_d;
  bool dummy;
  Generator pnt(point());

  bool ok = prp.maximize(Linear_Expression(0), extr_n, extr_d, dummy)
    && prp.maximize(Linear_Expression(0), extr_n, extr_d, dummy, pnt);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Point.
bool
test10() {
  Variable A(0);
  Variable B(1);

  Product prp(2);
  prp.refine_with_constraint(A == 1);
  prp.refine_with_constraint(3*B == 2);

  Linear_Expression le = A + B;

  Coefficient max_n;
  Coefficient max_d;
  Coefficient min_n;
  Coefficient min_d;
  Generator pnt_max(point());
  Generator pnt_min(point());
  Generator known_pnt(point(3*A + 2*B, 3));
  bool max;
  bool min;

  bool ok = prp.maximize(le, max_n, max_d, max)
    && prp.minimize(le, min_n, min_d, min)
    && prp.maximize(le, max_n, max_d, max, pnt_max)
    && prp.minimize(le, min_n, min_d, min, pnt_min);

  ok = ok
    && max && min && max_n == 5 && max_d == 3 && min_n == 5 && min_d == 3
    && pnt_max == known_pnt && pnt_min == known_pnt;

  print_generator(pnt_max, "*** max point ***");
  print_generator(pnt_min, "*** min point ***");

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// only one component is bounded.
bool
test11() {
  Variable A(0);
  Variable B(1);

  Product prp(2);
  prp.refine_with_constraint(A - B >= 1);
  prp.refine_with_constraint(A - B <= 1);
  prp.refine_with_congruence(3*B %= 2);
;
  Linear_Expression le = A - B;

  Coefficient max_n;
  Coefficient max_d;
  Coefficient min_n;
  Coefficient min_d;
  Generator pnt_max(point());
  Generator pnt_min(point());
  bool max;
  bool min;

  bool ok = prp.maximize(le, max_n, max_d, max)
    && prp.minimize(le, min_n, min_d, min)
    && prp.maximize(le, max_n, max_d, max, pnt_max)
    && prp.minimize(le, min_n, min_d, min, pnt_min);

  ok = ok
    && max && min && max_n == 1 && max_d == 1 && min_n == 1 && min_d == 1
    && pnt_max == pnt_min;

  print_generator(pnt_max, "*** maximum point ***");

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Line and neither component is bounded.
bool
test12() {
  Variable A(0);
  Variable B(1);

  Product prp(2);
  prp.refine_with_constraint(B == 1);

  Linear_Expression le = 2*A - B;

  Coefficient max_n;
  Coefficient max_d;
  Coefficient min_n;
  Coefficient min_d;
  Generator pnt_max(point());
  Generator pnt_min(point());
  bool max;
  bool min;

  bool ok = !prp.maximize(le, max_n, max_d, max)
    && !prp.minimize(le, min_n, min_d, min)
    && !prp.maximize(le, max_n, max_d, max, pnt_max)
    && !prp.minimize(le, min_n, min_d, min, pnt_min);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// only one component is strictly bounded.
bool
test13() {
  Variable A(0);
  Variable B(1);

  Product prp(2);

#if NNC_Poly_Class
  prp.refine_with_constraint(A - B > 0);
  prp.refine_with_constraint(A - B < 1);
#else
  prp.refine_with_constraint(A - B >= 0);
  prp.refine_with_constraint(A - B <= 1);
#endif
  prp.refine_with_congruence(3*B %= 2);

  Linear_Expression le = A - B;

  Coefficient max_n;
  Coefficient max_d;
  Coefficient min_n;
  Coefficient min_d;
  Generator pnt_max(point());
  Generator pnt_min(point());

  bool max;
  bool min;

  bool ok = prp.maximize(le, max_n, max_d, max)
    && prp.minimize(le, min_n, min_d, min)
    && prp.maximize(le, max_n, max_d, max, pnt_max)
    && prp.minimize(le, min_n, min_d, min, pnt_min);

#if NNC_Poly_Class
  ok = ok && !max && !min;
#else
  ok = ok && max && min;
#endif

  ok = ok && max_n == 1 && max_d == 1 && min_n == 0 && min_d == 1;

  print_generator(pnt_max, "*** maximum point ***");

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Non-empty product. bounded_affine_image/3
bool
test14() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product prp(3);
  prp.refine_with_congruence((A ==  0) / 0);
  prp.refine_with_congruence((B ==  0) / 0);
  prp.refine_with_congruence((C == -2) / 0);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  prp.bounded_affine_image(A, 7-B, B+3);

  Product known_prp(3);
  known_prp.refine_with_constraint(C == -2);
  known_prp.refine_with_constraint(B == 0);
  known_prp.refine_with_constraint(A <= 3);
  known_prp.refine_with_constraint(A - B >= 7);

  bool ok = (prp == known_prp);

  print_congruences(prp,
     "*** prp.bounded_affine_image(A, 7-B, B+3) congruences ***");
  print_constraints(prp,
     "*** prp.bounded_affine_image(A, 7-B, B+3) constraints ***");

  return ok;
}

// Empty product component. bounded_affine_image/3
bool
test15() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product prp(3);
  prp.refine_with_constraint(A ==  0);
  prp.refine_with_constraint(A ==  1);
  prp.refine_with_constraint(C == -2);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  prp.bounded_affine_image(A, 7-B, B+3);

  Product known_prp(3, EMPTY);

  bool ok = (prp == known_prp);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Non-empty product. bounded_affine_preimage/3
bool
test16() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product prp(3);
  prp.refine_with_congruence((A ==  0) / 0);
  prp.refine_with_congruence((B ==  0) / 0);
  prp.refine_with_congruence((C == -2) / 0);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  prp.bounded_affine_preimage(A, 7-B, B+3);

  Constraint_System cs;
  cs.insert(C == -2);
  cs.insert(B == 0);
  cs.insert(C >= 3);

  Product known_prp(3);
  known_prp.refine_with_constraints(cs);

  bool ok = (prp == known_prp);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

// Empty product. bounded_affine_preimage/3
bool
test17() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product prp(3);
  prp.refine_with_constraint(A ==  0);
  prp.refine_with_constraint(A ==  1);
  prp.refine_with_constraint(C == -2);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  prp.bounded_affine_preimage(A, 7-B, B+3);

  Product known_prp(3, EMPTY);

  bool ok = (prp == known_prp);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");

  return ok;
}

typedef Domain_Product<NNC_Polyhedron, Grid>::Direct_Product NNCPoly_Grid;

// Copy constructor.
bool
test19() {
  Variable A(0);

  const Constraint_System cs(A >= 0);

  NNCPoly_Grid src(1);
  src.refine_with_constraints(cs);

  NNCPoly_Grid prp(src, POLYNOMIAL_COMPLEXITY);

  NNCPoly_Grid prp1(src);

  NNCPoly_Grid known_prp(1);
  known_prp.refine_with_constraint(A >= 0);

  bool ok = (prp == known_prp && prp1 == known_prp);

  print_congruences(prp, "*** prp congruences ***");
  print_constraints(prp, "*** prp constraints ***");
  print_congruences(prp1, "*** prp1 congruences ***");
  print_constraints(prp1, "*** prp1 constraints ***");

  return ok && prp.OK();
}

// max_space_dimension().
bool
test22() {
  dimension_type msd1 = NNC_Polyhedron::max_space_dimension();
  nout << "NNCPolyhedron max space dimension = "
       << msd1 << endl;
  dimension_type msd2 = Grid::max_space_dimension();
  nout << "Grid max space dimension = "
       << msd2 << endl;
  dimension_type msd = NNCPoly_Grid::max_space_dimension();
  bool ok = (msd <= msd1 && msd <= msd2);

  nout << "NNCPoly_Grid max space dimension = "
       << msd << endl << endl;

  return ok;
}

// Attempt to construct a product with too many dimensions.
bool
test23() {
  try {
    // This is an invalid use of the constructor of a product:
    // it is illegal to (try to) build a product with a dimension
    // greater than max_space_dimension().
    NNCPoly_Grid pg(NNCPoly_Grid::max_space_dimension() + 2);

    // It is an error if the exception is not thrown.
  }
  catch (std::length_error& e) {
    nout << "length_error: " << e.what() << endl << endl;
    return true;
  }
  catch (...) {
    // It is an error if the wrong exception is thrown.
  }
  return false;
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
  DO_TEST(test08);
  DO_TEST(test09);
  DO_TEST(test10);
  DO_TEST(test11);
  DO_TEST(test12);
  DO_TEST(test13);
  DO_TEST(test14);
  DO_TEST(test15);
  DO_TEST(test16);
  DO_TEST(test17);
  DO_TEST(test19);
  DO_TEST(test22);
  DO_TEST(test23);
END_MAIN
