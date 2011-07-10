/* Linear_Form class implementation: non-inline template functions.
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

#ifndef PPL_Linear_Form_templates_hh
#define PPL_Linear_Form_templates_hh 1

#include "Linear_Form.defs.hh"
#include "Linear_Expression.defs.hh"
#include "Box.defs.hh"
#include <stdexcept>
#include <iostream>
#include <cmath>

namespace Parma_Polyhedra_Library {

template <typename C>
Linear_Form<C>::Linear_Form(const Variable v)
  : vec() {
  const dimension_type space_dim = v.space_dimension();
  if (space_dim > max_space_dimension())
    throw std::length_error("Linear_Form<C>::"
                            "Linear_Form(v):\n"
                            "v exceeds the maximum allowed "
                            "space dimension.");
  vec.reserve(compute_capacity(space_dim+1, vec_type().max_size()));
  vec.resize(space_dim+1, zero);
  vec[v.space_dimension()] = static_cast<C>(1.0);
}

template <typename C>
Linear_Form<C>::Linear_Form(const Variable v, const Variable w)
  : vec() {
  const dimension_type v_space_dim = v.space_dimension();
  const dimension_type w_space_dim = w.space_dimension();
  const dimension_type space_dim = std::max(v_space_dim, w_space_dim);
  if (space_dim > max_space_dimension())
    throw std::length_error("Linear_Form<C>::"
                            "Linear_Form(v, w):\n"
                            "v or w exceed the maximum allowed "
                            "space dimension.");
  vec.reserve(compute_capacity(space_dim+1, vec_type().max_size()));
  vec.resize(space_dim+1, zero);
  if (v_space_dim != w_space_dim) {
    vec[v_space_dim] = static_cast<C>(1.0);
    vec[w_space_dim] = static_cast<C>(-1.0);
  }
}

template <typename C>
Linear_Form<C>::Linear_Form(const Linear_Expression& e)
  : vec() {
  const dimension_type space_dim = e.space_dimension();
  if (space_dim > max_space_dimension())
    throw std::length_error("Linear_Form<C>::"
                            "Linear_Form(e):\n"
                            "e exceeds the maximum allowed "
                            "space dimension.");
  vec.reserve(compute_capacity(space_dim+1, vec_type().max_size()));
  vec.resize(space_dim+1);
  for (dimension_type i = space_dim; i-- > 0; )
    vec[i+1] = e.coefficient(Variable(i));
  vec[0] = e.inhomogeneous_term();
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>
operator+(const Linear_Form<C>& f1, const Linear_Form<C>& f2) {
  dimension_type f1_size = f1.size();
  dimension_type f2_size = f2.size();
  dimension_type min_size;
  dimension_type max_size;
  const Linear_Form<C>* p_e_max;
  if (f1_size > f2_size) {
    min_size = f2_size;
    max_size = f1_size;
    p_e_max = &f1;
  }
  else {
    min_size = f1_size;
    max_size = f2_size;
    p_e_max = &f2;
  }

  Linear_Form<C> r(max_size, false);
  dimension_type i = max_size;
  while (i > min_size) {
    --i;
    r[i] = p_e_max->vec[i];
  }
  while (i > 0) {
    --i;
    r[i] = f1[i];
    r[i] += f2[i];
  }
  return r;
}

/*! \relates Linear_Form */
template <typename C>
Linear_Form<C>
operator+(const Variable v, const Linear_Form<C>& f) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Form<C>::max_space_dimension())
    throw std::length_error("Linear_Form "
                            "operator+(v, f):\n"
                            "v exceeds the maximum allowed "
                            "space dimension.");
  Linear_Form<C> r(f);
  if (v_space_dim > f.space_dimension())
    r.extend(v_space_dim+1);
  r[v_space_dim] += static_cast<C>(1.0);
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>
operator+(const C& n, const Linear_Form<C>& f) {
  Linear_Form<C> r(f);
  r[0] += n;
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>
operator-(const Linear_Form<C>& f) {
  Linear_Form<C> r(f);
  for (dimension_type i = f.size(); i-- > 0; )
    neg_assign(r[i]);
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>
operator-(const Linear_Form<C>& f1, const Linear_Form<C>& f2) {
  dimension_type f1_size = f1.size();
  dimension_type f2_size = f2.size();
  if (f1_size > f2_size) {
    Linear_Form<C> r(f1_size, false);
    dimension_type i = f1_size;
    while (i > f2_size) {
      --i;
      r[i] = f1[i];
    }
    while (i > 0) {
      --i;
      r[i] = f1[i];
      r[i] -= f2[i];
    }
    return r;
  }
  else {
    Linear_Form<C> r(f2_size, false);
    dimension_type i = f2_size;
    while (i > f1_size) {
      --i;
      r[i].neg_assign(f2[i]);
    }
    while (i > 0) {
      --i;
      r[i] = f1[i];
      r[i] -= f2[i];
    }
    return r;
  }
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>
operator-(const Variable v, const Linear_Form<C>& f) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Form<C>::max_space_dimension())
    throw std::length_error("Linear_Form "
                            "operator-(v, e):\n"
                            "v exceeds the maximum allowed "
                            "space dimension.");
  Linear_Form<C> r(f);
  if (v_space_dim > f.space_dimension())
    r.extend(v_space_dim+1);
  for (dimension_type i = f.size(); i-- > 0; )
    r[i].neg_assign(r[i]);
  r[v_space_dim] += static_cast<C>(1.0);
  return r;
}

/*! \relates Linear_Form */
template <typename C>
Linear_Form<C>
operator-(const Linear_Form<C>& f, const Variable v) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Form<C>::max_space_dimension())
    throw std::length_error("Linear_Form "
                            "operator-(e, v):\n"
                            "v exceeds the maximum allowed "
                            "space dimension.");
  Linear_Form<C> r(f);
  if (v_space_dim > f.space_dimension())
    r.extend(v_space_dim+1);
  r[v_space_dim] -= static_cast<C>(1.0);
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>
operator-(const C& n, const Linear_Form<C>& f) {
  Linear_Form<C> r(f);
  for (dimension_type i = f.size(); i-- > 0; )
    neg_assign(r[i]);
  r[0] += n;
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>
operator*(const C& n,
	       const Linear_Form<C>& f) {
  Linear_Form<C> r(f);
  for (dimension_type i = f.size(); i-- > 0; )
    r[i] *= n;
  return r;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>&
operator+=(Linear_Form<C>& f1, const Linear_Form<C>& f2) {
  dimension_type f1_size = f1.size();
  dimension_type f2_size = f2.size();
  if (f1_size < f2_size)
    f1.extend(f2_size);
  for (dimension_type i = f2_size; i-- > 0; )
    f1[i] += f2[i];
  return f1;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>&
operator+=(Linear_Form<C>& f, const Variable v) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Form<C>::max_space_dimension())
    throw std::length_error("Linear_Form<C>& "
                            "operator+=(e, v):\n"
			    "v exceeds the maximum allowed space dimension.");
  if (v_space_dim > f.space_dimension())
    f.extend(v_space_dim+1);
  f[v_space_dim] += static_cast<C>(1.0);
  return f;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>&
operator-=(Linear_Form<C>& f1, const Linear_Form<C>& f2) {
  dimension_type f1_size = f1.size();
  dimension_type f2_size = f2.size();
  if (f1_size < f2_size)
    f1.extend(f2_size);
  for (dimension_type i = f2_size; i-- > 0; )
    f1[i] -= f2[i];
  return f1;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>&
operator-=(Linear_Form<C>& f, const Variable v) {
  const dimension_type v_space_dim = v.space_dimension();
  if (v_space_dim > Linear_Form<C>::max_space_dimension())
    throw std::length_error("Linear_Form<C>& "
                            "operator-=(e, v):\n"
			    "v exceeds the maximum allowed space dimension.");
  if (v_space_dim > f.space_dimension())
    f.extend(v_space_dim+1);
  f[v_space_dim] -= static_cast<C>(1.0);
  return f;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>&
operator*=(Linear_Form<C>& f, const C& n) {
  dimension_type f_size = f.size();
  for (dimension_type i = f_size; i-- > 0; )
    f[i] *= n;
  return f;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>&
operator/=(Linear_Form<C>& f, const C& n) {
  dimension_type f_size = f.size();
  for (dimension_type i = f_size; i-- > 0; )
    f[i] /= n;
  return f;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>&
operator|=(Linear_Form<C>& f1, const Linear_Form<C>& f2) {
  C zero(0);

  dimension_type f1_size = f1.size();
  dimension_type f2_size = f2.size();

  if (f1_size < f2_size)
    f1.extend(f2_size);

  bool equal = false;
  if (f1 == f2)
    equal = true;

  Linear_Form<C> r1(f1);
  Linear_Form<C> r2(f2);

  bool incomplete = true;

  if (f1 >= zero) {
    if (f2 >= zero) {
      if (!equal) {
        for (dimension_type i = f2_size; i-- > 0; ) {
          if (f1[i] != zero && f2[i] != zero)
	    incomplete = false;
	  r1[i].max(f2[i]);
	  mpz_class t1(f1[i].upper());
	  f1[i] += f2[i];
	  if (f1[i].upper() == t1 && f2[i] != 0)
            f1[i].assign(std::numeric_limits<typename C::boundary_type>::max());
          f1[i].join_assign(r1[i]);
	}
	if (incomplete)
	  for (dimension_type i = f2_size; i-- > 0; )
	    f1[i].join_assign(zero);
      }
      return f1;
    } // f2 >= zero
    else if (f2 < zero) {
      for (dimension_type i = f2_size; i-- > 0; )
	if (f1[i] != zero || f2[i] != zero) {
	  f1[i].assign(f2[i]);
	  f1[i].join_assign(-1);
	}
      return f1;
    } // f2 < zero
    else
      goto completely;
  } // f1 >= zero
  else if (f1 < zero) {
    if (f2 >= zero) {
      for (dimension_type i = f2_size; i-- > 0; )
	if (f1[i] != zero || f2[i] != zero)
	  f1[i].join_assign(-1);
      return f1;
    } // f2 >= zero
    else if (f2 < zero) {
      if (!equal)
	for (dimension_type i = f2_size; i-- > 0; )
	  if (f1[i] != zero || f2[i] != zero) {
	    f1[i].max(f2[i]);
	    f1[i].join_assign(-1);
	  }
      return f1;
    } // f2 < zero
    else
      goto completely;
  } // f1 < zero
  else
    goto completely;

 completely:
  throw std::runtime_error("Linear_Form<C> f1 and Linear_Form<C> f2 "
			   "are not completely less or greater than zero");
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>&
operator&=(Linear_Form<C>& f1, const Linear_Form<C>& f2) {
  C zero(0);
  C one(1);

  dimension_type f1_size = f1.size();
  dimension_type f2_size = f2.size();

  if (f1_size < f2_size)
    f1.extend(f2_size);

  bool equal = false;
  if (f1 == f2)
    equal = true;

  Linear_Form<C> r1(f1);
  Linear_Form<C> r2(f2);

  if (f1 >= zero) {
    if (f2 >= zero) {
      if (!equal)
        for (dimension_type i = f2_size; i-- > 0; ) {
          f1[i].min(f2[i]);
          f1[i].join_assign(zero);
        }
      return f1;
    } // f2 >= zero
    else if (f2 < zero) {
      for (dimension_type i = f2_size; i-- > 0; )
	f1[i].join_assign(zero);
      return f1;
    } // f2 < zero
    else
      goto not_totaly;
  } // f1 >= zero
  else if (f1 < zero) {
    if (f2 >= zero) {
      for (dimension_type i = f2_size; i-- > 0; ) {
	f1[i].assign(f2[i]);
	f1[i].join_assign(zero);
      }
      return f1;
    } // f2 >= zero
    else if (f2 < zero) {
      if (!equal)
	for (dimension_type i = f2_size; i-- > 0; ) {
	  mpz_class t1(r1[i].lower());
	  r1[i] += f2[i];
	  if (r1[i].lower() == t1 && f2[i] != 0)
	    r1[i].assign(std::numeric_limits<typename C::boundary_type>::min());
	  f1[i].min(f2[i]);
	  f1[i].join_assign(r1[i]);
	}
      return f1;
    } // f2 < zero
    else
      goto not_totaly;
  } // f1 < zero
  else
    goto not_totaly;

 not_totaly:
  throw std::runtime_error("Linear_Form<C> f1 and Linear_Form<C> f2 "
			   "are not completely less or greater than zero");
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>&
operator^=(Linear_Form<C>& f1, const Linear_Form<C>& f2) {
  C zero(0);

  dimension_type f1_size = f1.size();
  dimension_type f2_size = f2.size();

  if (f1_size < f2_size)
    f1.extend(f2_size);

  bool equal = false;
  if (f1 == f2)
    equal = true;

  Linear_Form<C> r1(f1);
  Linear_Form<C> r2(f2);
  Linear_Form<C> zero_lf(zero);

  if (f1 >= zero) {
    if (f2 >= zero) {
      if (equal)
        return f1 = Linear_Form<C>(zero);
      else {
        for (dimension_type i = f2_size; i-- > 0; ) {
          mpz_class t1(f1[i].upper());
          f1[i] += f2[i];
          if (f1[i].upper() == t1 && f2[i] != 0)
            f1[i].assign(std::numeric_limits<typename C::boundary_type>::max());
          f1[i].join_assign(zero);
        }
	return f1;
      }
    } // f2 >= zero
    else if (f2 < zero) {
      for (dimension_type i = f2_size; i-- > 0; ) {
	if (f1[i] != zero || f2[i] != zero) {
	  r1[i].neg_assign(f1[i]);
	  mpz_class t1(r1[i].lower());
	  r1[i] += f2[i];
	  if (r1[i].lower() == t1 && f2[i] != 0)
	    r1[i].assign(std::numeric_limits<typename C::boundary_type>::min());
          r1[i].join_assign(-1);
          f1[i].assign(r1[i]);
	}
      }
      return f1;
    } // f2 < zero
    else
      goto not_totaly;
  } // f1 >= zero
  else if (f1 < zero) {
    if (f2 >= zero) {
      for (dimension_type i = f2_size; i-- > 0; ) {
	if (f1[i] != zero && f2[i] != zero) {
	  r2[i].neg_assign(f2[i]);
	  mpz_class t1(f1[i].lower());
	  f1[i] += r2[i];
	  if (f1[i].lower() == t1 && f2[i] != 0)
	    f1[i].assign(std::numeric_limits<typename C::boundary_type>::min());
	  f1[i].join_assign(-1);
	}
      }
      return f1;
    } // f2 >= zero
    else if (f2 < zero) {
      if (equal)
	return f1 = Linear_Form<C>(zero);
      else {
	for (dimension_type i = f2_size; i-- > 0; ) {
	  r1[i].neg_assign(f1[i]);
	  r2[i].neg_assign(f2[i]);
	  mpz_class t1(r1[i].upper());
	  r1[i] += r2[i];
	  if (r1[i].upper() == t1 && r2[i] != 0)
	    r1[i].assign(std::numeric_limits<typename C::boundary_type>::max());
	  r1[i].join_assign(zero);
	  f1[i].assign(r1[i]);
	}
	return f1;
      }
    } // f2 < zero
    else
      goto not_totaly;
  } //  f1 < zero
  else
    goto not_totaly;

 not_totaly:
  throw std::runtime_error("Linear_Form<C> f1 and Linear_Form<C> f2 "
			   "are not completely less or greater than zero");
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>&
operator<<(Linear_Form<C>& f1, const Linear_Form<C>& f2) {
  C zero(0);

  dimension_type f1_size = f1.size();
  dimension_type f2_size = f2.size();

  if (f1_size < f2_size)
    f1.extend(f2_size);

  Linear_Form<C> r1(f1);
  Linear_Form<C> r2(f2);

  if (f1 >= zero) {
    if (f2 >= zero) {
      for (dimension_type i = f2_size; i-- > 0; ) {
        mpz_class t1(f1[i].upper());
        mpz_class t2(f2[i].upper());
        f1[i].join_assign(r1[i].upper()*(int)ldexp(1.0, f2[i].upper()));
        if (f1[i].upper() == t1 && t1 != 0 && t2 != 0)
          f1[i].assign(zero);
        else
          f1[i].join_assign(zero);
      }
      return f1;
    } // f2 >= zero
    else if (f2 < zero) {
      for (dimension_type i = f2_size; i-- > 0; ) {
	r1[i].assign(zero);
	r2[i].neg_assign(f2[i]);
	if (f1[i].upper() != 0 || f2[i].upper() != 0)
	  r1[i].join_assign(f1[i].upper()/(int)ldexp(1.0, r2[i].upper()));
	f1[i].assign(r1[i]);
      }
      return f1;
    } // f2 < zero
    else
      goto not_totaly;
  } // f1 >= zero
  else if (f1 < zero) {
    if (f2 >= zero) {
      for (dimension_type i = f2_size; i-- > 0; ) {
	if (f1[i] != zero || f2[i] != zero) {
	  f1[i].join_assign(r1[i].lower()*(int)ldexp(1.0, f2[i].lower()));
	  if (f1[i].upper() == 0)
	    f1[i].assign(zero);
	  else
	    f1[i].join_assign(zero);
	}
      }
      return f1;
    } // f2 >= zero
    else if (f2 < zero) {
      for (dimension_type i = f2_size; i-- > 0; ) {
	if (f1[i] != zero || f2[i] != zero) {
	  r1[i].assign(zero);
	  r2[i].neg_assign(f2[i]);
	  r1[i].join_assign(f1[i].lower()/ldexp(1.0, r2[i].upper()));
	  if ((int)r1[i].lower() != r1[i].lower())
	    --r1[i].lower();
	  f1[i].assign(r1[i]);
	}
      }
      return f1;
    } // f2 < zero
    else
      goto not_totaly;
  } // f1 < zero
  else
    goto not_totaly;

 not_totaly:
  throw std::runtime_error("Linear_Form<C> f1 and Linear_Form<C> f2 "
			   "are not completely less or greater than zero");
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
Linear_Form<C>&
operator>>(Linear_Form<C>& f1, const Linear_Form<C>& f2) {
  C zero(0);

  dimension_type f1_size = f1.size();
  dimension_type f2_size = f2.size();

  if (f1_size < f2_size)
    f1.extend(f2_size);

  Linear_Form<C> r1(f1);
  Linear_Form<C> r2(f2);

  if (f1 >= zero) {
    if (f2 >= zero) {
      for (dimension_type i = f2_size; i-- > 0; ) {
        r1[i].assign(zero);
        r1[i].join_assign(f1[i].upper()/(int)ldexp(1.0, f2[i].upper()));
        f1[i].assign(r1[i]);
      }
      return f1;
    } // f2 >= zero
    else if (f2 < zero) {
      for (dimension_type i = f2_size; i-- > 0; ) {
	r2[i].neg_assign(f2[i]);
	mpz_class t1(f1[i].upper());
	f1[i].join_assign(r1[i].upper()*(int)ldexp(1.0, r2[i].upper()));
	if (f1[i].upper() == t1 && r2[i].upper() != 0)
	  f1[i].assign(zero);
	else
	  f1[i].join_assign(zero);
      }
      return f1;
    } // f2 < zero
    else
      goto not_totaly;
  } // f1 >= zero
  else if (f1 < zero) {
    if (f2 >= zero) {
      for (dimension_type i = f2_size; i-- > 0; ) {
	if (f1[i] != zero || f2[i] != zero) {
	  r1[i].assign(zero);
	  r1[i].join_assign(f1[i].lower()/ldexp(1.0, f2[i].lower()));
	  if ((int)r1[i].lower() != r1[i].lower())
	    --r1[i].lower();
	  f1[i].assign(r1[i]);
	}
      }
      return f1;
    } // f2 >= zero
    else if (f2 < zero) {
      for (dimension_type i = f2_size; i-- > 0; ) {
	if (f1[i] != zero || f2[i] != zero) {
	  mpz_class t1(f1[i].lower());
	  r2[i].neg_assign(f2[i]);
	  f1[i].join_assign(r1[i].lower()*(int)ldexp(1.0, r2[i].upper()));
	  if (f1[i].lower() == t1 && f2[i].lower() != 0)
	    f1[i].assign(zero);
	  else
	    f1[i].join_assign(zero);
	}
      }
      return f1;
    } // f2 < zero
    else
      goto not_totaly;
  } // f1 < zero
  else
    goto not_totaly;

 not_totaly:
  throw std::runtime_error("Linear_Form<C> f1 and Linear_Form<C> f2 "
			   "are not completely less or greater than zero");
}

/*! \relates Linear_Row */
template <typename C>
inline bool
operator==(const Linear_Form<C>& x, const Linear_Form<C>& y) {
  const dimension_type x_size = x.size();
  const dimension_type y_size = y.size();
  if (x_size >= y_size) {
    for (dimension_type i = y_size; i-- > 0; ) {
      if (x[i] != y[i])
        return false;
    }
    for (dimension_type i = x_size; --i >= y_size; )
      if (x[i] != x.zero)
        return false;
  }
  else {
    for (dimension_type i = x_size; i-- > 0; )
      if (x[i] != y[i])
        return false;

    for (dimension_type i = y_size; --i >= x_size; )
      if (y[i] != x.zero)
        return false;
  }

  return true;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
inline bool
operator>=(Linear_Form<C>& f, const C& n) {
  const dimension_type f_size = f.size();

  for (dimension_type i = f_size; i-- > 0; )
    if (!(f[i] >= n))
      return false;

 return true;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
inline bool
operator>=(const Linear_Form<C>& f, const C& n) {
 const dimension_type f_size = f.size();

 for (dimension_type i = f_size; i-- > 0; )
   if (!(f[i] >= n))
     return false;

 return true;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
inline bool
operator<(Linear_Form<C>& f, const C& n) {
  const dimension_type f_size = f.size();

  for (dimension_type i = f_size; i-- > 0; )
    if (f[i] != n)
      if (f[i] >= n)
	return false;

  return true;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
inline bool
operator<(const Linear_Form<C>& f, const C& n) {
  const dimension_type f_size = f.size();

  for (dimension_type i = f_size; i-- > 0; )
    if (f[i] != n)
      if (f[i] >= n)
	return false;

  return true;
}

template <typename C>
void
Linear_Form<C>::negate() {
  for (dimension_type i = vec.size(); i-- > 0; )
    neg_assign(vec[i]);
  return;
}

template <typename C>
inline memory_size_type
Linear_Form<C>::external_memory_in_bytes() const {
  memory_size_type n = 0;
  for (dimension_type i = size(); i-- > 0; )
    n += vec[i].external_memory_in_bytes();
  n += vec.capacity()*sizeof(C);
  return n;
}

template <typename C>
bool
Linear_Form<C>::OK() const {
  for (dimension_type i = size(); i-- > 0; )
    if (!vec[i].OK())
      return false;
  return true;
}

// Floating point analysis related methods.
template <typename C>
void
Linear_Form<C>::relative_error(
		const Floating_Point_Format analyzed_format,
                Linear_Form& result) const {
  typedef typename C::boundary_type analyzer_format;

  // Get the necessary information on the analyzed's format.
  unsigned int f_base;
  unsigned int f_mantissa_bits;
  switch (analyzed_format) {
    case IEEE754_HALF:
      f_base = float_ieee754_half::BASE;
      f_mantissa_bits = float_ieee754_half::MANTISSA_BITS;
      break;
    case IEEE754_SINGLE:
      f_base = float_ieee754_single::BASE;
      f_mantissa_bits = float_ieee754_single::MANTISSA_BITS;
      break;
    case IEEE754_DOUBLE:
      f_base = float_ieee754_double::BASE;
      f_mantissa_bits = float_ieee754_double::MANTISSA_BITS;
      break;
    case IBM_SINGLE:
      f_base = float_ibm_single::BASE;
      f_mantissa_bits = float_ibm_single::MANTISSA_BITS;
      break;
    case IEEE754_QUAD:
      f_base = float_ieee754_quad::BASE;
      f_mantissa_bits = float_ieee754_quad::MANTISSA_BITS;
      break;
    case INTEL_DOUBLE_EXTENDED:
      f_base = float_intel_double_extended::BASE;
      f_mantissa_bits = float_intel_double_extended::MANTISSA_BITS;
      break;
    default:
      throw std::runtime_error("PPL internal error");
  }

  C error_propagator;
  // We assume that f_base is a power of 2.
  int power = ld2(f_base) * (-f_mantissa_bits);
  analyzer_format lb = -static_cast<analyzer_format>(ldexp(1.0, power));

  error_propagator.build(i_constraint(GREATER_OR_EQUAL, lb),
                         i_constraint(LESS_OR_EQUAL, -lb));

  // Handle the inhomogeneous term.
  const C* current_term = &inhomogeneous_term();
  assert(current_term->is_bounded());

  C current_multiplier(std::max(std::abs(current_term->lower()),
                                std::abs(current_term->upper())));
  Linear_Form current_result_term(current_multiplier);
  current_result_term *= error_propagator;
  result = Linear_Form(current_result_term);

  // Handle the other terms.
  dimension_type dimension = space_dimension();
  for (dimension_type i = 0; i < dimension; ++i) {
    current_term = &coefficient(Variable(i));
    assert(current_term->is_bounded());
    current_multiplier = C(std::max(std::abs(current_term->lower()),
                                    std::abs(current_term->upper())));
    current_result_term = Linear_Form(Variable(i));
    current_result_term *= current_multiplier;
    current_result_term *= error_propagator;
    result += current_result_term;
  }

  return;
}

template <typename C>
template <typename Target>
bool
Linear_Form<C>::intervalize(const Oracle<Target,C>& oracle,
                            C& result) const {
  result = C(inhomogeneous_term());
  dimension_type dimension = space_dimension();
  for (dimension_type i = 0; i < dimension; ++i) {
    C current_addend = coefficient(Variable(i));
    C curr_int;
    if (!oracle.get_interval(i, curr_int))
      return false;
    current_addend *= curr_int;
    result += current_addend;
  }
  return true;
}

/*! \relates Parma_Polyhedra_Library::Linear_Form */
template <typename C>
std::ostream&
IO_Operators::operator<<(std::ostream& s, const Linear_Form<C>& f) {
  const dimension_type num_variables = f.space_dimension();
  bool first = true;
  for (dimension_type v = 0; v < num_variables; ++v) {
    const C& fv = f[v+1];
    if (fv != 0) {
	    if (first) {
        if (fv == -1.0)
          s << "-";
        else if (fv != 1.0)
          s << fv << "*";
        first = false;
      }
      else {
        if (fv == -1.0)
          s << " - ";
        else {
          s << " + ";
          if (fv != 1.0)
            s << fv << "*";
        }
      }
      s << Variable(v);
    }
  }
  // Inhomogeneous term.
  const C& it = f[0];
  if (it != 0) {
    if (!first)
	s << " + ";
    else
      first = false;
    s << it;
  }

  if (first)
    // The null linear form.
    s << Linear_Form<C>::zero;
  return s;
}

PPL_OUTPUT_TEMPLATE_DEFINITIONS(C, Linear_Form<C>)

template <typename C>
C Linear_Form<C>::zero(0.0);

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_Linear_Form_templates_hh)
