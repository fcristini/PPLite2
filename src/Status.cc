/* Status class implementation (non-inline functions).
   Copyright (C) 2001, 2002 Roberto Bagnara <bagnara@cs.unipr.it>

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

#include <config.h>

#include "Status.defs.hh"

#include <iostream>
#include <string>
#include <cassert>

namespace PPL = Parma_Polyhedra_Library;

// These are the keywords that indicate the individual assertions.
static const std::string zero_dim_univ = "ZE";
static const std::string empty = "EM";
static const std::string consys_min = "CM";
static const std::string gensys_min = "GM";
static const std::string consys_upd = "CS";
static const std::string gensys_upd = "GS";
static const std::string sat_c = "SC";
static const std::string sat_g = "SG";
static const char yes = '+';
static const char no = '-';
static const char sep = ' ';

void
PPL::Status::ASCII_dump(std::ostream& s) const {
  s << (test_zero_dim_univ() ? yes : no) << zero_dim_univ << sep
    << (test_empty() ? yes : no) << empty << sep
    << sep
    << (test_c_minimized() ? yes : no) << consys_min << sep
    << (test_g_minimized() ? yes : no) << gensys_min << sep
    << sep
    << (test_c_up_to_date() ? yes : no) << consys_upd << sep
    << (test_g_up_to_date() ? yes : no) << gensys_upd << sep
    << sep
    << (test_sat_c_up_to_date() ? yes : no) << sat_c << sep
    << (test_sat_g_up_to_date() ? yes : no) << sat_g << sep;
}

/*!
  Reads a keyword and its associated on/off flag from \p s.
  Returns <CODE>true</CODE> if the operation is successful,
  returns <CODE>false</CODE> otherwise.
  When successful, \p positive is set to <CODE>true</CODE> if the flag
  is on; it is set to <CODE>false</CODE> otherwise.
*/
static bool
get_field(std::istream& s, const std::string& keyword, bool& positive) {
  std::string str;
  if (!(s >> str)
      || (str[0] != yes && str[0] != no)
      || str.substr(1) != keyword)
    return false;
  positive = (str[0] == yes);
  return true;
}

bool
PPL::Status::ASCII_load(std::istream& s) {
  bool positive;

  if (get_field(s, zero_dim_univ, positive))
    return false;
  if (positive)
    set_zero_dim_univ();

  if (get_field(s, empty, positive))
    return false;
  if (positive)
    set_empty();

  if (get_field(s, consys_min, positive))
    return false;
  if (positive)
    set_c_minimized();
  else
    reset_c_minimized();

  if (get_field(s, gensys_min, positive))
    return false;
  if (positive)
    set_g_minimized();
  else
    reset_g_minimized();

  if (get_field(s, consys_upd, positive))
    return false;
  if (positive)
    set_c_up_to_date();
  else
    reset_c_up_to_date();

  if (get_field(s, gensys_upd, positive))
    return false;
  if (positive)
    set_g_up_to_date();
  else
    reset_g_up_to_date();

  if (get_field(s, sat_c, positive))
    return false;
  if (positive)
    set_sat_c_up_to_date();
  else
    reset_sat_c_up_to_date();

  if (get_field(s, sat_g, positive))
    return false;
  if (positive)
    set_sat_g_up_to_date();
  else
    reset_sat_g_up_to_date();

  // Check for well-formedness.
  assert(OK());
  return true;
}

bool
PPL::Status::OK() const {
  if (test_zero_dim_univ())
    // Zero-dim universe is ok.
    return true;

  if (test_empty()) {
    // The empty flag is incompatible with any other one.
    Status copy = *this;
    copy.reset_empty();
    return copy.test_zero_dim_univ();
  }

  if ((test_sat_c_up_to_date() || test_sat_g_up_to_date())
      && !(test_c_up_to_date() && test_g_up_to_date()))
    // If a saturation matrix is up-to-date, constraints and
    // generators have to be both up-to-date.
    return false;

  if (test_c_minimized() && !test_c_up_to_date())
    // If constraints are minimized they must be up-to-date.
    return false;

  if (test_g_minimized() && !test_g_up_to_date())
    // If generators are minimized they must be up-to-date.
    return false;

  // Any other case is ok.
  return true;
}
