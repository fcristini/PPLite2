/* Test the termination analysis facilities of the PPL.
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>

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
site: http://www.cs.unipr.it/ppl/ . */

#include "ppl_test.hh"

namespace {

bool
test01() {
  Variable xp1(0);
  Variable xp2(1);
  Variable x1(2);
  Variable x2(3);
  C_Polyhedron ph(4);
  ph.add_constraint(x1 >= 2);
  ph.add_constraint(2*xp1 + 1 >= x1);
  ph.add_constraint(2*xp1 <= x1);
  ph.add_constraint(xp2 == x2 + 1);
  ph.add_constraint(xp2 >= 1);

  C_Polyhedron mu_space;
  all_affine_ranking_functions_MS(ph, mu_space);

  print_constraints(mu_space, "*** mu_space ***");

  Variable mu1(0);
  Variable mu2(1);
  Variable mu0(2);
  C_Polyhedron known_result(3);
  known_result.add_constraint(mu1 - mu2 >= 1);
  known_result.add_constraint(mu0 + 2*mu1 >= 0);
  known_result.add_constraint(mu2 >= 0);

  print_constraints(known_result, "*** known_result ***");

  return known_result == mu_space;
}

bool
test02() {
  Variable xp1(0);
  Variable xp2(1);
  Variable x1(2);
  Variable x2(3);
  C_Polyhedron ph(4);
  ph.add_constraint(x1 >= 2);
  ph.add_constraint(2*xp1 + 1 >= x1);
  ph.add_constraint(2*xp1 <= x1);
  ph.add_constraint(xp2 == x2 + 1);
  ph.add_constraint(xp2 >= 1);

  Generator witness(point());
  one_affine_ranking_function_MS(ph, witness);

  print_generator(witness, "*** witness ***");

  Variable mu1(0);
  Variable mu2(1);
  Variable mu0(2);
  Generator known_result(point(0*mu0 + 1*mu1 + 0*mu2));

  print_generator(known_result, "*** known_result ***");

  return known_result == witness;
}

bool
test03() {
  Variable xp1(0);
  Variable xp2(1);
  Variable x1(2);
  Variable x2(3);
  C_Polyhedron ph(4);
  ph.add_constraint(x1 >= 2);
  ph.add_constraint(2*xp1 + 1 >= x1);
  ph.add_constraint(2*xp1 <= x1);
  ph.add_constraint(xp2 == x2 + 1);
  ph.add_constraint(xp2 >= 1);

  return termination_test_MS(ph);
}

bool
test04() {
  Variable xp1(0);
  Variable xp2(1);
  Variable x1(2);
  Variable x2(3);
  C_Polyhedron ph(4);
  ph.add_constraint(x1 >= 2);
  ph.add_constraint(2*xp1 + 1 >= x1);
  ph.add_constraint(2*xp1 <= x1);
  ph.add_constraint(xp2 == x2 + 1);
  ph.add_constraint(xp2 >= 1);

  C_Polyhedron mu_space;
  all_affine_ranking_functions_PR(ph, mu_space);

  print_constraints(mu_space, "*** mu_space ***");

  Variable mu1(0);
  Variable mu2(1);
  Variable mu0(2);
  C_Polyhedron known_result(3);
  known_result.add_constraint(mu1 - mu2 >= 1);
  known_result.add_constraint(mu2 >= 0);
  known_result.add_constraint(2*mu0 + mu1 + 2*mu2 >= 0);

  print_constraints(known_result, "*** known_result ***");

  if (known_result.contains(mu_space))
    std::cout << "->" << endl;
  if (mu_space.contains(known_result))
    std::cout << "<-" << endl;
  return known_result == mu_space;
}

bool
test05() {
  Variable xp1(0);
  Variable xp2(1);
  Variable x1(2);
  Variable x2(3);
  C_Polyhedron ph(4);
  ph.add_constraint(x1 >= 2);
  ph.add_constraint(2*xp1 + 1 >= x1);
  ph.add_constraint(2*xp1 <= x1);
  ph.add_constraint(xp2 == x2 + 1);
  ph.add_constraint(xp2 >= 1);

  Generator witness(point());
  one_affine_ranking_function_PR(ph, witness);

  print_generator(witness, "*** witness ***");

  Variable mu1(0);
  Variable mu2(1);
  Variable mu0(2);
  Generator known_result(point(0*mu0 + 1*mu1 + 0*mu2));

  print_generator(known_result, "*** known_result ***");

  return known_result == witness;
}

bool
test06() {
  Variable xp1(0);
  Variable xp2(1);
  Variable x1(2);
  Variable x2(3);
  C_Polyhedron ph(4);
  ph.add_constraint(x1 >= 2);
  ph.add_constraint(2*xp1 + 1 >= x1);
  ph.add_constraint(2*xp1 <= x1);
  ph.add_constraint(xp2 == x2 + 1);
  ph.add_constraint(xp2 >= 1);

  return termination_test_PR(ph);
}

bool
test07() {
  BD_Shape<int> bds(2);
  return termination_test_MS(bds);
}

bool
test10() {
  Variable xp1(0);
  Variable xp2(1);
  Variable x1(2);
  Variable x2(3);
  C_Polyhedron ph(4);
  ph.add_constraint(xp1 - x1 >= 0);
  ph.add_constraint(-xp1 + x1 >= 0);
  ph.add_constraint(-xp2 + x2 >= 1);
  ph.add_constraint(xp2 >= 0);
  ph.add_constraint(xp1 >= 1);

  return termination_test_MS(ph);
}

bool
test11() {
  Variable xp1(0);
  Variable xp2(1);
  Variable x1(2);
  Variable x2(3);
  C_Polyhedron ph(4);
  ph.add_constraint(xp1 - x1 >= 0);
  ph.add_constraint(-xp1 + x1 >= 0);
  ph.add_constraint(-xp2 + x2 >= 1);
  ph.add_constraint(xp2 >= 0);
  ph.add_constraint(xp1 >= 1);

  return termination_test_PR(ph);
}

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
  DO_TEST(test02);
  DO_TEST(test03);
  //DO_TEST(test04);
  //DO_TEST(test05);
  DO_TEST(test06);
  //DO_TEST(test07);
  DO_TEST(test10);
  DO_TEST_F(test11);
END_MAIN
