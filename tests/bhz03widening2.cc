/* Test Polyhedra_Powerset<PH>::BHZ03_widening_assign().
   Copyright (C) 2001-2004 Roberto Bagnara <bagnara@cs.unipr.it>

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

#include "ppl_test.hh"
#include <vector>

using namespace std;
using namespace Parma_Polyhedra_Library;

#ifndef NOISY
#define NOISY 0
#endif

namespace {

Variable A(0);
Variable B(1);

typedef Polyhedra_PowerSet<C_Polyhedron> PSet;

} // namespace

int
main() TRY {
  set_handlers();

  C_Polyhedron p(2);
  C_Polyhedron q(2);
  C_Polyhedron r(2);
  C_Polyhedron s(2);
  p.add_constraint(A >= 1);
  p.add_constraint(B == 0);
  q.add_constraint(A >= 2);
  q.add_constraint(A <= 7);
  q.add_constraint(B == 1);
  r.add_constraint(A >= 3);
  r.add_constraint(A <= 8);
  r.add_constraint(B == 1);
  s.add_constraint(A >= 1);
  s.add_constraint(A <= 6);
  s.add_constraint(B == 1);
  PSet P(2, Polyhedron::EMPTY);
  P.add_disjunct(p);
  P.add_disjunct(q);
  P.add_disjunct(r);
  P.add_disjunct(s);
  PSet Q(2, Polyhedron::EMPTY);
  Q.add_disjunct(p);
  Q.add_disjunct(q);
  Q.add_disjunct(s);

#if NOISY
  using namespace Parma_Polyhedra_Library::IO_Operators;

  cout << "P = " << P << endl
       << "Q = " << Q << endl;
#endif

  PSet oldP = P;
  P.BHZ03_widening_assign(Q, widen_fun(&Polyhedron::H79_widening_assign));
#if NOISY
  cout << "P.BHZ03(Q, H79)" << " = " << P << endl;
#endif

  return (P.semantically_contains(oldP) && P.semantically_contains(Q)) ? 0 : 1;
}
CATCH
