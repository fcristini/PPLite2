/* Grid Generator class implementation: inline functions.
   Copyright (C) 2001-2005 Roberto Bagnara <bagnara@cs.unipr.it>

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

#ifndef PPL_Grid_Generator_inlines_hh
#define PPL_Grid_Generator_inlines_hh 1

#include "Grid_Generator.defs.hh"

namespace Parma_Polyhedra_Library {

inline void
negate(Grid_Generator& g, dimension_type start, dimension_type end) {
  while (start <= end)
    negate(g[start++]);
}

inline
Grid_Generator::Grid_Generator(Generator g)
  : Generator(Generator::point()) {
  Generator::swap(g);
}

inline dimension_type
Grid_Generator::space_dimension() const {
  return Generator::space_dimension() - 1;
}

inline Grid_Generator::Type
Grid_Generator::type() const {
  switch (Generator::type()) {
  case Generator::POINT:
    return POINT;
  case Generator::RAY:
    return PARAMETER;
  case Generator::LINE:
    return LINE;
  case Generator::CLOSURE_POINT:
  default:
    assert(false);
    return POINT;
  }
}

inline bool
Grid_Generator::is_line() const {
  return Generator::is_line();
}

inline bool
Grid_Generator::is_parameter() const {
  return is_ray();
}

inline bool
Grid_Generator::is_line_or_parameter() const {
  return is_line_or_ray();
}

inline bool
Grid_Generator::is_point() const {
  return Generator::is_point();
}

inline bool
Grid_Generator::is_parameter_or_point() const {
  return is_ray_or_point_or_inequality();
}

inline void
Grid_Generator::set_is_line() {
  Generator::set_is_line();
}

inline void
Grid_Generator::set_is_parameter() {
  Generator::set_is_ray_or_point();
}

inline Grid_Generator&
Grid_Generator::operator=(const Grid_Generator& g) {
  Generator::operator=(g);
  return *this;
}

inline Grid_Generator&
Grid_Generator::operator=(const Generator& g) {
  Generator::operator=(g);
  return *this;
}

inline Coefficient&
Grid_Generator::divisor() {
  if (is_line())
    throw_invalid_argument("divisor()", "*this is a line");
  if (is_line_or_parameter())
    return Generator::operator[](size() - 1);
  return Generator::operator[](0);
}

inline Coefficient_traits::const_reference
Grid_Generator::divisor() const {
  if (is_line())
    throw_invalid_argument("divisor()", "*this is a line");
  if (is_line_or_parameter())
    return Generator::operator[](size() - 1);
  return Generator::operator[](0);
}

inline memory_size_type
Grid_Generator::total_memory_in_bytes() const {
  return Generator::total_memory_in_bytes();
}

inline memory_size_type
Grid_Generator::external_memory_in_bytes() const {
  return Generator::external_memory_in_bytes();
}

inline void
Grid_Generator::strong_normalize() {
  Generator::strong_normalize();
}

inline Topology
Grid_Generator::topology() const {
  return Generator::topology();
}

inline dimension_type
Grid_Generator::size() const {
  return Generator::size();
}

inline void
Grid_Generator::swap(Grid_Generator& y) {
  Generator::swap(y);
}

inline void
Grid_Generator::ascii_dump(std::ostream& s) const {
  Generator::ascii_dump(s);
}

inline bool
Grid_Generator::ascii_load(std::istream& s) {
  return Generator::ascii_load(s);
}

inline Coefficient&
Grid_Generator::operator[](dimension_type k) {
  return Generator::operator[](k);
}

inline Coefficient_traits::const_reference
Grid_Generator::operator[](dimension_type k) const {
  return Generator::operator[](k);
}

/*! \relates Grid_Generator */
inline bool
operator==(const Grid_Generator& x, const Grid_Generator& y) {
  return x.is_equivalent_to(y);
}

/*! \relates Grid_Generator */
inline bool
operator!=(const Grid_Generator& x, const Grid_Generator& y) {
  return !(x == y);
}

/*! \relates Grid_Generator */
inline Grid_Generator
grid_line(const Linear_Expression& e) {
  return Grid_Generator::line(e);
}

/*! \relates Grid_Generator */
inline Grid_Generator
parameter(const Linear_Expression& e,
	  Coefficient_traits::const_reference d) {
  return Grid_Generator::parameter(e, d);
}

/*! \relates Grid_Generator */
inline Grid_Generator
grid_point(const Linear_Expression& e,
	   Coefficient_traits::const_reference d) {
  return Grid_Generator::point(e, d);
}

} // namespace Parma_Polyhedra_Library

namespace std {

/*! \relates Parma_Polyhedra_Library::Grid_Generator */
inline void
swap(Parma_Polyhedra_Library::Grid_Generator& x,
     Parma_Polyhedra_Library::Grid_Generator& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_Grid_Generator_inlines_hh)
