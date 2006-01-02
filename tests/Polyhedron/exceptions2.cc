/* Test that the right exceptions are thrown in case of incorrect uses.
   Copyright (C) 2001-2006 Roberto Bagnara <bagnara@cs.unipr.it>

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

#include "ppl_test.hh"

using std::invalid_argument;
using std::domain_error;

namespace {

void
error1() {
  Variable x(0);
  Variable y(1);

  Constraint_System cs;
  cs.insert(x - y > 0);
  cs.insert(x >= 0);

  try {
    // This is an invalid use of the constructor of a polyhedron:
    // it is illegal to build a closed polyhedron starting from
    // a system of constraints that contains strict-inequalities.
    C_Polyhedron ph(cs);

    // It is an error if the exception is not thrown.
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    // It is an error if the wrong exception is thrown.
    exit(1);
  }
}

void
error2() {
  Variable x(0);
  Variable y(1);

  Generator_System gs;
  gs.insert(closure_point(2*x + y));
  gs.insert(point(x + y));
  gs.insert(ray(x));
  gs.insert(ray(y));

  try {
    // This is an invalid use of the constructor of a polyhedron:
    // it is illegal to build a closed polyhedron starting from
    // a system of generators that contains closure points.
    C_Polyhedron ph(gs);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error3() {
  Variable x(0);
  Variable y(1);

  C_Polyhedron ph(3);

  try {
    // This is an invalid use of the function add_constraint(c): it is
    // illegal to insert a strict-inequality into a system of
    // constraints of a closed polyhedron.
    ph.add_constraint(x - y > 0);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error4() {
  C_Polyhedron ph(3, EMPTY);

  try {
    // This is an incorrect use of the function add_generator(g): it
    // is illegal to insert a closure-point into a system of
    // generators of a closed polyhedron.
    ph.add_generator(closure_point(Linear_Expression(2)));
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error5() {
  Variable x(0);
  Variable y(1);

  C_Polyhedron ph(3);
  ph.add_constraint(x >= 2);
  ph.add_constraint(y >= 2);

  Constraint_System cs;
  cs.insert(x == y);
  cs.insert(x < 5);

  try {
    // This is an incorrect use of the function
    // add_constraints_and_minimize(cs): it is illegal to add a system of
    // constraints that contains strict-inequalities to a closed polyhedron.
    ph.add_constraints_and_minimize(cs);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error6() {
  Variable x(0);
  Variable y(1);

  C_Polyhedron ph(3);
  Constraint_System cs;
  cs.insert(x > 3);
  cs.insert(x > y);

  try {
    // This is an invalid use of the function add_constraints(cs):
    // it is illegal to add a system of constraints that contains
    // strict-inequalities to a closed polyhedron.
    ph.add_constraints(cs);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error7() {
  Variable x(0);
  Variable y(1);

  C_Polyhedron ph(3);

  Constraint_System cs;
  cs.insert(x > 2);
  cs.insert(x == y);
  NNC_Polyhedron qh(cs);

  try {
    // This is an incorrect use of the method concatenate_assign(): it
    // is illegal to apply this method to a closed polyhedron with a
    // NNC Polyhedron.
    ph.concatenate_assign(qh);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error8() {
  Variable x(0);
  Variable y(1);

  C_Polyhedron ph(3);
  Generator_System gs;
  gs.insert(point());
  gs.insert(closure_point(-x));
  gs.insert(ray(x));
  gs.insert(ray(y));

  try {
    // This is an incorrect use of the function
    // add_generators_and_minimize(gs): it is illegal to add a
    // system of generators that contains closure-points to a closed
    // polyhedron.
    ph.add_generators_and_minimize(gs);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error9() {
  Variable x(0);
  Variable y(1);

  C_Polyhedron ph(3);
  Generator_System gs;
  gs.insert(point(x));
  gs.insert(closure_point());
  gs.insert(ray(x+y));

  try {
    // This is an incorrect use of the function add_generators(gs): it is
    // illegal to add a system of generators that contains closure-points
    // to a closed polyhedron.
    ph.add_generators(gs);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error10() {
  Variable A(0);
  Variable B(1);

  C_Polyhedron ph(2);
  ph.add_constraint(A >= 1);
  ph.add_constraint(B >= 1);

  try {
    // This is an invalid use of the function
    // C_Polyhedron::generalized_affine_image(v, expr, d):
    // `GREATER_THAN' is an illegal relation for necessarily closed
    // polyhedron.
    ph.generalized_affine_image(A + B, GREATER_THAN, A - B);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error11() {
  Variable A(0);
  Variable B(1);

  C_Polyhedron ph1(2);
  ph1.add_constraint(A >= 2);

  NNC_Polyhedron ph2(2);
  ph2.add_constraint(A - B > 0);
  ph2.add_constraint(A >= 0);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");

  try {
    // This is an invalid use of the function
    // `intersection_assign_and_minimize': it is illegal to apply
    // to a closed polyhedron and a non-closed polyhedron.
    ph1.intersection_assign_and_minimize(ph2);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error12() {
  Variable A(0);
  Variable B(1);

  C_Polyhedron ph1(2);
  ph1.add_constraint(B >= 2);

  NNC_Polyhedron ph2(2);
  ph2.add_constraint(A - B > 0);
  ph2.add_constraint(B >= 0);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");

  try {
    // This is an invalid use of the function
    // `intersection_assign': it is illegal to apply this function
    // to a closed polyhedron and a non-closed polyhedron.
    ph1.intersection_assign(ph2);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error13() {
  Variable A(0);
  Variable B(1);

  Generator_System gs1;
  gs1.insert(point());
  gs1.insert(point(3*A));
  C_Polyhedron ph1(gs1);

  Generator_System gs2;
  gs2.insert(point(B));
  gs2.insert(closure_point());
  gs2.insert(closure_point(3*B));
  NNC_Polyhedron ph2(gs2);

  print_generators(ph1, "*** ph1 ***");
  print_generators(ph2, "*** ph2 ***");

   try {
     // This is an invalid use of the function
     // `poly_hull_assign_and_minimize': it is illegal to apply
     // this function to a closed polyhedron and a
     // non-closed polyhedron.
    ph1.poly_hull_assign_and_minimize(ph2);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error14() {
  Variable A(0);
  Variable B(1);

  Generator_System gs1;
  gs1.insert(point());
  gs1.insert(point(3*B));
  C_Polyhedron ph1(gs1);

  Generator_System gs2;
  gs2.insert(point(2*A));
  gs2.insert(closure_point());
  gs2.insert(closure_point(3*A));
  NNC_Polyhedron ph2(gs2);

  print_generators(ph1, "*** ph1 ***");
  print_generators(ph2, "*** ph2 ***");

   try {
    // This is an invalid use of the function
    // `poly_hull_assign': it is illegal to apply this function
    // to a closed polyhedron and a non-closed polyhedron.
    ph1.poly_hull_assign(ph2);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error15() {
  Variable A(0);
  Variable B(1);

  C_Polyhedron ph1(2);
  ph1.add_constraint(A >= 0);
  ph1.add_constraint(A <= 4);
  ph1.add_constraint(B >= 0);
  ph1.add_constraint(B <= 4);

  NNC_Polyhedron ph2(2);
  ph2.add_constraint(A >= 2);
  ph2.add_constraint(A <= 6);
  ph2.add_constraint(B >= 0);
  ph2.add_constraint(B <= 4);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");

  try {
    // This is an invalid use of the function
    // `poly_difference_assign': it is illegal to apply this function
    // to a closed polyhedron and a non-closed polyhedron.
    ph1.poly_difference_assign(ph2);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error16() {
  Variable A(0);
  Variable B(1);

  C_Polyhedron ph1(2);
  ph1.add_constraint(A >= 0);
  ph1.add_constraint(A <= 2);
  ph1.add_constraint(A - B >= 0);

  NNC_Polyhedron ph2(2);
  ph2.add_constraint(A >= 0);
  ph2.add_constraint(A <= 4);
  ph2.add_constraint(A - B >= 0);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");

  try {
    // This is an invalid use of the function
    // `H79_widening_assign': it is illegal to apply this function
    // to a closed polyhedron and a non-closed polyhedron.
    ph2.H79_widening_assign(ph1);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error17() {
  Variable A(0);
  Variable B(1);

  NNC_Polyhedron ph1(2);
  ph1.add_constraint(A >= 0);
  ph1.add_constraint(A <= 2);
  ph1.add_constraint(A - B >= 0);

  C_Polyhedron ph2(2);
  ph2.add_constraint(A >= 0);
  ph2.add_constraint(A <= 4);
  ph2.add_constraint(A - B >= 0);

  Constraint_System cs;
  cs.insert(A <= 8);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");
  print_constraints(cs, "*** cs ***");

  try {
    // This is an invalid use of the function
    // `limited_H79_widening_assign': it is illegal to
    // apply this function to a closed polyhedron and
    // a non-closed polyhedron.
    ph2.limited_H79_extrapolation_assign(ph1, cs);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error18() {
  Variable A(0);
  Variable B(1);

  C_Polyhedron ph1(2);
  ph1.add_constraint(A >= 0);
  ph1.add_constraint(A <= 2);
  ph1.add_constraint(A - B >= 0);

  C_Polyhedron ph2(2);
  ph2.add_constraint(A >= 0);
  ph2.add_constraint(A <= 4);
  ph2.add_constraint(A - B >= 0);

  Constraint_System cs;
  cs.insert(A < 8);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");
  print_constraints(cs, "*** cs ***");

  try {
    // This is an invalid use of the function
    // `limited_H79_extrapolation_assign': it is illegal to
    // apply this function to two closed polyhedra and
    // to a non-closed system of constraints.
    ph2.limited_H79_extrapolation_assign(ph1, cs);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error19() {
  Variable A(0);
  Variable B(1);

  C_Polyhedron ph1(2);
  ph1.add_constraint(A >= 0);
  ph1.add_constraint(B >= 0);
  ph1.add_constraint(A + B <= 1);

  Generator_System gs;
  gs.insert(point(2*A + 2*B));
  gs.insert(ray(A + B));
  NNC_Polyhedron ph2(gs);

  print_generators(ph1, "*** ph1 ***");
  print_generators(ph2, "*** ph2 ***");

 try {
    // This is an invalid use of the function
    // `time_elapse_assign': it is illegal to
    // apply this function to a closed polyhedron and
    // a non-closed polyhedron.
    ph1.time_elapse_assign(ph2);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error20() {
  Variable A(0);

  C_Polyhedron ph1(1);
  ph1.add_constraint(A >= 5);

  NNC_Polyhedron ph2(1);
  ph2.add_constraint(A > 0);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");

  try {
    // This is an invalid use of the Polyhedron::contains(): it is
    // illegal to apply this method to a closed polyhedron and a
    // non-closed polyhedron.
    ph1.contains(ph2);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error21() {
  Variable A(0);
  Variable B(1);

  NNC_Polyhedron ph1(2);
  ph1.add_constraint(A >= 0);
  ph1.add_constraint(A - B > 0);

  const Constraint_System cs = ph1.constraints();

  print_constraints(cs, "*** cs ***");

  try {
    // This is an incorrect use of the function
    // C_Polyhedron::C_Polyhedron(cs): it is illegal to build a
    // closed polyhedron starting from a system of constraints
    // that contains strict inequalities.
    C_Polyhedron ph2(cs);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error22() {
  Variable A(0);

  Generator_System gs1;
  gs1.insert(point(3*A));
  gs1.insert(closure_point(2*A));
  gs1.insert(ray(A));

  NNC_Polyhedron ph1(gs1);

  const Generator_System gs2 = ph1.generators();

  try {
    // This is an incorrect use of the function
    // `C_Polyhedron(const Generator_System)': it is illegal to build
    // a closed polyhedron starting from a constant non-closed
    // system of generators.
    C_Polyhedron ph2(gs2);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error23() {
  NNC_Polyhedron ph(0, EMPTY);

  try {
    // This is an incorrect use of the function
    // `add_generator(g)': it is illegal add a closure point
    // to a zero-dimensional and empty non-closed polyhedron.
    ph.add_generator(closure_point());
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error24() {
  NNC_Polyhedron ph(0, EMPTY);

  print_constraints(ph, "*** ph ***");

  Generator_System gs;
  gs.insert(closure_point());

  try {
    // This is an invalid used of the function
    // `add_generators_and_minimize(gs)': it is illegal to
    // add a system of generators that does not contain points
    // to an empty zero-dimensional polyhedron.
    ph.add_generators_and_minimize(gs);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error25() {
  NNC_Polyhedron ph(0, EMPTY);

  print_constraints(ph, "*** ph ***");

  Generator_System gs;
  gs.insert(closure_point());

  try {
    // This is an invalid used of the function
    // `add_generators(gs)': it is illegal to
    // add a system of generators that does not contain points
    // to an empty zero-dimensional polyhedron.
    ph.add_generators(gs);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error26() {
  Variable A(0);

  NNC_Polyhedron ph1(1);
  ph1.add_constraint(A > 5);

  C_Polyhedron ph2(1);
  ph2.add_constraint(A >= 0);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");

  try {
    // This is an invalid use of Polyhedron::contains():
    // it is illegal to apply this method to a
    // closed polyhedron and a non-closed polyhedron.
    ph2.contains(ph1);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error27() {
  Variable A(0);
  Variable B(1);

  C_Polyhedron ph1(2);
  ph1.add_constraint(A >= 0);
  ph1.add_constraint(A <= 2);
  ph1.add_constraint(A - B >= 0);

  NNC_Polyhedron ph2(2);
  ph2.add_constraint(A >= 0);
  ph2.add_constraint(A <= 4);
  ph2.add_constraint(A - B >= 0);

  Constraint_System cs;
  cs.insert(A < 8);

  print_constraints(ph1, "*** ph1 ***");
  print_constraints(ph2, "*** ph2 ***");
  print_constraints(cs, "*** cs ***");

  try {
    // This is an invalid use of the function
    // `limited_H79_extrapolation_assign': it is illegal to
    // apply this function to a non-closed polyhedron,
    // a non-closed polyhedron and a system of
    // constraints that contains strict inequalities.
    ph2.limited_H79_extrapolation_assign(ph1, cs);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error28() {
  Variable A(0);
  Variable B(1);

  C_Polyhedron ph1(2);
  ph1.add_constraint(A <= 2);
  ph1.add_constraint(B >= 0);
  ph1.add_constraint(A - B >= 0);

  NNC_Polyhedron ph2(2);
  ph2.add_constraint(A < 5);
  ph2.add_constraint(B >= 0);
  ph2.add_constraint(A - B >= 0);

  try {
    // This is an invalid use of the function
    // `BHRZ03_widening_assign': it is illegal to
    // apply this function to a non-closed polyhedron and
    // a non-closed polyhedron.
    ph2.BHRZ03_widening_assign(ph1);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error29() {
  Variable A(0);
  Variable B(1);

  Generator_System gs;
  try {
    // This is an incorrect use of function
    // Generator::closure_point(e, d):
    // it is illegal to use a denominator
    // equal to zero.
    gs.insert(closure_point(A + 2*B, 0));
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error30() {
  Variable A(0);
  Variable B(1);

  NNC_Polyhedron ph1(2);
  ph1.add_constraint(A < 2);
  ph1.add_constraint(B > 0);

  C_Polyhedron ph2;

  try {
    // This is an invalid use of the function
    // `Polyhedron::swap(Polyhedron&)': it is illegal
    // to apply this function to a closed and a
    // not necessarily closed polyhedron.
    ph1.swap(ph2);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error31() {
  Variable A(0);

  C_Polyhedron ph(1);
  ph.add_constraint(A >= 1);

  try {
    // This is an invalid use of the function
    // C_Polyhedron::generalized_affine_image(v, r, expr,d ):
    // `GREATER_THAN' is an illegal relation for necessarily closed
    // polyhedron.
    ph.generalized_affine_image(A, GREATER_THAN, A + 1);
    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error32() {
  Variable A(0);
  LP_Problem lp;
  Constraint_System cs;
  cs.insert(A >= 6);
  cs.insert(A > -6);

  try {
    // This tries to build an invalid LP_Problem object: the feasible
    // region can not be defined using strict inequalities.
    lp.add_constraints(cs);

    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error33() {
  Variable A(0);
  LP_Problem lp;

  try {
    // This tries to build an invalid LP_Problem object: the space dimension
    // of the objective function can not be greater than the space dimension
    // of the feasible region.
    lp.set_objective_function(A);

    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error34() {
  Variable A(0);
  Constraint_System cs;
  cs.insert(A >= 6);
  cs.insert(A <= 0);
  LP_Problem lp(cs, A, MAXIMIZATION);

  try {
    // We cannot extract a feasible point from an unsatisfiable LP_Problem.
    Generator fp = lp.feasible_point();

    exit(1);
  }
  catch (domain_error& e) {
    nout << "domain_error: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error35() {
  Variable A(0);
  Constraint_System cs;
  cs.insert(A >= 6);
  LP_Problem lp(cs, A, MAXIMIZATION);

  try {
    // We cannot extract an optimizing point from an unbounded LP_Problem.
    Generator fp = lp.optimizing_point();

    exit(1);
  }
  catch (domain_error& e) {
    nout << "domain_error: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error36() {
  Variable A(0);
  Variable B(1);
  Constraint_System cs;
  cs.insert(A >= 6);
  LP_Problem lp(cs, A, MAXIMIZATION);
  Generator p = point(A + B);
  Coefficient num;
  Coefficient den;

  try {
    // This tries to evaluate the objective function on a space dimension
    // incompatible generator.
    lp.evaluate_objective_function(p, num, den);

    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

void
error37() {
  Variable A(0);
  Constraint_System cs;
  cs.insert(A >= 6);
  LP_Problem lp(cs, A, MAXIMIZATION);
  Generator r = ray(A);
  Coefficient num;
  Coefficient den;

  try {
    // This tries to evaluate the objective function on a ray.
    lp.evaluate_objective_function(r, num, den);

    exit(1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl << endl;
  }
  catch (...) {
    exit(1);
  }
}

} // namespace

int
main() TRY {
  set_handlers();

  error1();
  error2();
  error3();
  error4();
  error5();
  error6();
  error7();
  error8();
  error9();
  error10();
  error11();
  error12();
  error13();
  error14();
  error15();
  error16();
  error17();
  error18();
  error19();
  error20();
  error21();
  error22();
  error23();
  error24();
  error25();
  error26();
  error27();
  error28();
  error29();
  error30();
  error31();
  error32();
  error33();
  error34();
  error35();
  error36();
  error37();

  return 0;
}
CATCH
