/* Grid Generator class implementation: inline functions.
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2011 BUGSENG srl (http://bugseng.com)

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
site: http://www.cs.unipr.it/ppl/ . */

#ifndef PPL_Grid_Generator_inlines_hh
#define PPL_Grid_Generator_inlines_hh 1

namespace Parma_Polyhedra_Library {

inline
Grid_Generator::Grid_Generator(Linear_Expression& e, Type type) {
  Linear_Row::swap(e);
  set_flags(Flags(NECESSARILY_CLOSED, (type == LINE
                                       ? LINE_OR_EQUALITY
                                       : RAY_OR_POINT_OR_INEQUALITY)));
  PPL_ASSERT(OK());
}

inline
Grid_Generator::Grid_Generator()
  : Linear_Row() {
  set_flags(Flags(NECESSARILY_CLOSED, LINE_OR_EQUALITY));
}

inline
Grid_Generator::Grid_Generator(const Grid_Generator& g)
  : Linear_Row(g) {
}

inline
Grid_Generator::~Grid_Generator() {
}

inline dimension_type
Grid_Generator::max_space_dimension() {
  return Linear_Row::max_space_dimension() - 1;
}

inline dimension_type
Grid_Generator::space_dimension() const {
  return Linear_Row::space_dimension() - 1;
}

inline Grid_Generator::Type
Grid_Generator::type() const {
  if (is_line())
    return LINE;
  return is_point() ? POINT : PARAMETER;
}

inline bool
Grid_Generator::is_line() const {
  return is_line_or_equality();
}

inline bool
Grid_Generator::is_parameter() const {
  return is_parameter_or_point() && is_line_or_parameter();
}

inline bool
Grid_Generator::is_line_or_parameter() const {
  return (*this)[0] == 0;
}

inline bool
Grid_Generator::is_point() const {
  return !is_line_or_parameter();
}

inline bool
Grid_Generator::is_parameter_or_point() const {
  return is_ray_or_point_or_inequality();
}

inline void
Grid_Generator::set_divisor(Coefficient_traits::const_reference d) {
  PPL_ASSERT(!is_line());
  Linear_Row& x = *this;
  if (is_line_or_parameter())
    x[size() - 1] = d;
  else
    x[0] = d;
}

inline Coefficient_traits::const_reference
Grid_Generator::divisor() const {
  if (is_line())
    throw_invalid_argument("divisor()", "*this is a line");
  const Linear_Row& x = *this;
  if (is_line_or_parameter())
    return x[size() - 1];
  else
    return x[0];
}

inline bool
Grid_Generator::is_equal_at_dimension(dimension_type dim,
				      const Grid_Generator& y) const {
  const Grid_Generator& x = *this;
  return x[dim] * y.divisor() == y[dim] * x.divisor();
}

inline void
Grid_Generator::set_is_line() {
  set_is_line_or_equality();
}

inline void
Grid_Generator::set_is_parameter_or_point() {
  set_is_ray_or_point_or_inequality();
}

inline Grid_Generator&
Grid_Generator::operator=(const Grid_Generator& g) {
  Linear_Row::operator=(g);
  return *this;
}

inline void
Grid_Generator::negate(dimension_type first, dimension_type last) {
  Linear_Row& x = *this;
  for ( ; first < last; ++first)
    neg_assign(x[first]);
}

inline Coefficient_traits::const_reference
Grid_Generator::coefficient(const Variable v) const {
  if (v.space_dimension() > space_dimension())
    throw_dimension_incompatible("coefficient(v)", "v", v);
  return Linear_Row::coefficient(v.id());
}

inline memory_size_type
Grid_Generator::total_memory_in_bytes() const {
  return Linear_Row::total_memory_in_bytes();
}

inline memory_size_type
Grid_Generator::external_memory_in_bytes() const {
  return Linear_Row::external_memory_in_bytes();
}

inline const Grid_Generator&
Grid_Generator::zero_dim_point() {
  PPL_ASSERT(zero_dim_point_p != 0);
  return *zero_dim_point_p;
}

inline void
Grid_Generator::strong_normalize() {
  PPL_ASSERT(!is_parameter());
  Linear_Row::strong_normalize();
}

inline void
Grid_Generator::swap(Grid_Generator& y) {
  Linear_Row::swap(y);
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
  return Grid_Generator::grid_line(e);
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
  return Grid_Generator::grid_point(e, d);
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
