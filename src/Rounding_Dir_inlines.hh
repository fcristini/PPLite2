/* Inline functions operating on enum Rounding_Dir values.
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

#ifndef PPL_Rounding_Dir_inlines_hh
#define PPL_Rounding_Dir_inlines_hh 1

#include "assertions.hh"

namespace Parma_Polyhedra_Library {

/*! \ingroup PPL_CXX_interface */
inline Rounding_Dir
operator&(Rounding_Dir x, Rounding_Dir y) {
  const unsigned res = static_cast<unsigned>(x) & static_cast<unsigned>(y);
  return static_cast<Rounding_Dir>(res);
}

/*! \ingroup PPL_CXX_interface */
inline Rounding_Dir
operator|(Rounding_Dir x, Rounding_Dir y) {
  const unsigned res = static_cast<unsigned>(x) | static_cast<unsigned>(y);
  return static_cast<Rounding_Dir>(res);
}

/*! \ingroup PPL_CXX_interface */
inline Rounding_Dir
round_dir(Rounding_Dir dir) {
  return dir & ROUND_DIR_MASK;
}

/*! \ingroup PPL_CXX_interface */
inline bool
round_down(Rounding_Dir dir) {
  return round_dir(dir) == ROUND_DOWN;
}

/*! \ingroup PPL_CXX_interface */
inline bool
round_up(Rounding_Dir dir) {
  return round_dir(dir) == ROUND_UP;
}

/*! \ingroup PPL_CXX_interface */
inline bool
round_ignore(Rounding_Dir dir) {
  return round_dir(dir) == ROUND_IGNORE;
}

/*! \ingroup PPL_CXX_interface */
inline bool
round_not_needed(Rounding_Dir dir) {
  return round_dir(dir) == ROUND_NOT_NEEDED;
}

/*! \ingroup PPL_CXX_interface */
inline bool
round_not_requested(Rounding_Dir dir) {
  return round_dir(dir) == ROUND_IGNORE || round_dir(dir) == ROUND_NOT_NEEDED;
}

/*! \ingroup PPL_CXX_interface */
inline bool
round_direct(Rounding_Dir dir) {
  return round_dir(dir) == ROUND_DIRECT;
}

/*! \ingroup PPL_CXX_interface */
inline bool
round_inverse(Rounding_Dir dir) {
  return round_dir(dir) == ROUND_INVERSE;
}

/*! \ingroup PPL_CXX_interface */
inline bool
round_strict_relation(Rounding_Dir dir) {
  return (dir & ROUND_STRICT_RELATION) == ROUND_STRICT_RELATION;
}

/*! \ingroup PPL_CXX_interface */
inline Rounding_Dir
inverse(Rounding_Dir dir) {
  switch (round_dir(dir)) {
  case ROUND_UP:
    return ROUND_DOWN | (dir & ROUND_STRICT_RELATION);
  case ROUND_DOWN:
    return ROUND_UP | (dir & ROUND_STRICT_RELATION);
  case ROUND_IGNORE:
    return dir;
  default:
    PPL_UNREACHABLE;
    return dir;
  }
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_Rounding_Dir_inlines_hh)
