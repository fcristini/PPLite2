/* Test BD_Shape::generalized_affine_image(v, r, e, d): the BDS
   is empty.
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

  TBD_Shape bd(2, EMPTY);

  print_constraints(bd, "*** bd ***");

  bd.generalized_affine_image(A, LESS_THAN_OR_EQUAL, B + 1);

  BD_Shape<mpq_class> known_result(2, EMPTY);

  int retval = (BD_Shape<mpq_class>(bd) == known_result) ? 0 : 1;

  print_constraints(bd, "*** bd.generalized_affine_image"
		    "(A, LESS_THAN_OR_EQUAL, B + 1) ***");

  return retval;
}
CATCH
