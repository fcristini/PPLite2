/* Adds the zero-dim inconsistent constraint to a polyhedron.
   Copyright (C) 2001 Roberto Bagnara <bagnara@cs.unipr.it>

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

#include "ppl_install.hh"
#include "print.hh"
#include "ehandlers.hh"

using namespace std;
using namespace Parma_Polyhedra_Library;

#define NOISY 0

int
main() {
  set_handlers();

  // For const-correctness, making a copy is required.
  ConSys cs1 = ConSys::zero_dim_empty();
  Polyhedron ph1;
  ph1.add_constraints_and_minimize(cs1);

  Polyhedron known_result(0, Polyhedron::EMPTY);

  ConSys cs2;
  cs2.insert(LinExpression::zero() >= 7);
  Polyhedron ph2;
  ph2.add_constraints_and_minimize(cs2);

  ConSys cs3;
  cs3.insert(LinExpression::zero() >= -3);
  Polyhedron ph3;
  ph3.add_constraints_and_minimize(cs3);

  Polyhedron empty_result(0, Polyhedron::EMPTY);
  Polyhedron univ_result;

  int retval = (ph1 == empty_result
		&& ph2 == empty_result
		&& ph3 == univ_result) ? 0 : 1;

#if NOISY
  cout << "*** ph1 ***"
       << endl
       << ph1
       << endl;

  cout << "*** ph2 ***"
       << endl
       << ph2
       << endl;

  cout << "*** ph3 ***"
       << endl
       << ph3
       << endl;

  cout << "*** empty_result ***"
       << endl
       << empty_result
       << endl;

  cout << "*** univ_result ***"
       << endl
       << univ_result
       << endl;
#endif

  return retval;
}
