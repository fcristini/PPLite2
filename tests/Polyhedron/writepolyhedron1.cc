/* Test operator<<(std::ostream&, const Polyhedron&).
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

#include "files.hh"
#include <fstream>

using std::fstream;
using std::ios_base;

using namespace IO_Operators;

namespace {

bool
test01() {
  const char* my_file = "writepolyhedron1.dat";
  Variable A(0);
  Variable B(1);
  Variable C(2);

  C_Polyhedron ph(3);
  ph.add_constraint(  A - B       >= 3);
  ph.add_constraint(    - B +   C >= 3);
  ph.add_constraint(  A - B       <= 1);
  ph.add_constraint(  A - B + 3*C >= 3);
  ph.add_constraint(3*A     + 2*C >= 3);

  fstream f;
  open(f, my_file, ios_base::out);
  f << ph << endl;
  close(f);
  // FIXME.
  return true;
}

bool
test02() {
  const char* my_file = "writepolyhedron1.dat";
  NNC_Polyhedron ph1;

  C_Polyhedron ph(ph1.constraints());

  fstream f;
  open(f, my_file, ios_base::out);
  f << ph << endl;
  close(f);
  // FIXME.
  return true;
}

} // namespace

BEGIN_MAIN
  NEW_TEST(test01);
  NEW_TEST(test02);
END_MAIN
