/* Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2017 BUGSENG srl (http://bugseng.com)

This file is free software; as a special exception the author gives
unlimited permission to copy and/or distribute it, with or without
modifications, as long as this notice is preserved.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. */

#ifndef PPL_Coefficient_types_hh
#define PPL_Coefficient_types_hh 1

#ifdef PPL_GMP_INTEGERS
#include "GMP_Integer_types.hh"
#endif

namespace Parma_Polyhedra_Library {

//! An alias for easily naming the type of PPL coefficients.
/*! \ingroup PPL_CXX_interface
  Objects of type Coefficient are used to implement the integral valued
  coefficients occurring in linear expressions, constraints, generators,
  bounding boxes and so on.  Depending on the chosen
  configuration options (see file <CODE>README.configure</CODE>),
  a Coefficient may actually be:
    - The GMP_Integer type, which in turn is an alias for the
      <CODE>mpz_class</CODE> type implemented by the C++ interface
      of the GMP library (this is the default configuration).
*/
typedef PPL_COEFFICIENT_TYPE Coefficient;

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! An alias for easily naming the coefficient traits.
/*! \ingroup PPL_CXX_interface */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
typedef Coefficient_traits_template<Coefficient> Coefficient_traits;

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_Coefficient_types_hh)
