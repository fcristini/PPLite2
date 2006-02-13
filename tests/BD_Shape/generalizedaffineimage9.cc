/* Test BD_Shape::generalized_affine_image().
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

int
main() TRY {
  Variable A(0);
  Variable B(1);
  Variable C(2);
  Linear_Expression e1(C);
  Linear_Expression e2(A + 1);

  TBD_Shape bd(3);
  bd.add_constraint(A >= 0);
  bd.add_constraint(A <= 4);
  bd.add_constraint(B <= 5);
  bd.add_constraint(C <= 2);
  bd.add_constraint(C - A <= 2);

  print_constraints(bd, "*** bd ***");

  bd.generalized_affine_image(e1, LESS_THAN_OR_EQUAL, e2);

  BD_Shape<mpq_class> known_result(3);
  known_result.add_constraint(A >= 0);
  known_result.add_constraint(A <= 4);
  known_result.add_constraint(B <= 5);
  known_result.add_constraint(C - A <= 1);

  int retval = (BD_Shape<mpq_class>(bd) == known_result) ? 0 : 1;

  print_constraints(bd, "*** bd.generalized_affine_image(C, "
                        "LESS_THAN_OR_EQUAL, A + 1) ***");

  return retval;
}
CATCH
