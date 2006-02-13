/* Test BD_Shape::map_space_dimensions().
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

#include "PFunction.hh"
#include <string>
#include <ostream>

void
print_function(const PFunction& function,
	       const std::string& intro = "",
	       std::ostream& s = nout) {
  if (!intro.empty())
    s << intro << endl;
  function.print(s);
}

int
main() TRY {
  Variable x(0);
  Variable y(1);

  PFunction function;
  function.insert(0, 1);
  function.insert(1, 0);

  TBD_Shape bd(2);
  bd.add_constraint(x <= 1);
  bd.add_constraint(y <= -1);
  bd.add_constraint(y - x <= 3);

  print_constraints(bd, "*** bd ***");
  print_function(function, "*** function ***");

  bd.map_space_dimensions(function);

  BD_Shape<mpq_class> known_result(2);
  known_result.add_constraint(x <= -1);
  known_result.add_constraint(y <= 1);
  known_result.add_constraint(x - y <= 3);

  int retval = (BD_Shape<mpq_class>(bd) == known_result) ? 0 : 1;

  print_constraints(bd, "*** bd.map_space_dimension(function) ***");

  return retval;
}
CATCH
