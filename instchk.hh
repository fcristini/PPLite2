/* Fake declarations to test the validity of the arguments of the
   --enabled-instantiations option defined in configure.ac.
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

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif

#include "gmpxx.h"

namespace Parma_Polyhedra_Library {

class Polyhedron {
public:
  static bool valid_instantiation() {
    return true;
  }
};

class C_Polyhedron {
public:
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

class NNC_Polyhedron {
public:
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

class Grid {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

class Rational_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

class Z_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

#if PPL_SUPPORTED_FLOAT
class Float_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};
#endif // PPL_SUPPORTED_FLOAT

#if PPL_SUPPORTED_DOUBLE
class Double_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};
#endif // PPL_SUPPORTED_DOUBLE

#if PPL_SUPPORTED_LONG_DOUBLE
class Long_Double_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};
#endif // PPL_SUPPORTED_LONG_DOUBLE

class Int8_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

class Int16_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

class Int32_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

class Int64_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

class Uint8_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

class Uint16_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

class Uint32_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

class Uint64_Box {
public:
  static bool valid_instantiation() {
    return true;
  }
  static bool valid_Pointset_Powerset_argument() {
    return true;
  }
  static bool valid_Product_argument() {
    return true;
  }
};

template <typename PSET>
class Pointset_Powerset {
public:
  static bool valid_instantiation() {
    return PSET::valid_Pointset_Powerset_argument();
  }
};

template <typename D1, typename D2>
class Direct_Product {
public:
  static bool valid_instantiation() {
    return D1::valid_Product_argument() && D2::valid_Product_argument();
  }
};

template <typename D1, typename D2>
class Smash_Product {
public:
  static bool valid_instantiation() {
    return D1::valid_Product_argument() && D2::valid_Product_argument();
  }
};

template <typename D1, typename D2>
class Constraints_Product {
public:
  static bool valid_instantiation() {
    return D1::valid_Product_argument() && D2::valid_Product_argument();
  }
};

template <typename D1, typename D2>
class Shape_Preserving_Product {
public:
  static bool valid_instantiation() {
    return D1::valid_Product_argument() && D2::valid_Product_argument();
  }
};

} // namespace Parma_Polyhedra_Library
