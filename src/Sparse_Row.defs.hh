/* Sparse_Row class declaration.
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>

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

#ifndef PPL_Sparse_Row_defs_hh
#define PPL_Sparse_Row_defs_hh 1

#include "Sparse_Row.types.hh"
#include "Unlimited_Sparse_Row.defs.hh"
#include "Coefficient.defs.hh"
#include <list>
#include <vector>

namespace Parma_Polyhedra_Library {

//! A finite sparse sequence of coefficients.
class Sparse_Row {

public:
  //! A const iterator that may skip some zeros in the sequence.
  typedef Unlimited_Sparse_Row::const_iterator const_iterator;

  //! An iterator that may skip some zeros in the sequence.
  typedef Unlimited_Sparse_Row::iterator iterator;

  //! An iterator that may skip some zeros in the sequence.
  //! May be invalidated by apparently unrelated operations, use with care.
  //! See the method documentation for details.
  typedef Unlimited_Sparse_Row::dangerous_iterator dangerous_iterator;

  //! Constructs a row from a std::vector.
  Sparse_Row(const std::vector<Coefficient>& v);

  //! Constructs a row of the specified size.
  Sparse_Row(const dimension_type n=0);

  //! Constructs a row of the specified size from an Unlimited_Sparse_Row.
  Sparse_Row(const Unlimited_Sparse_Row &x,const dimension_type n);

  //! Constructs a Sparse_Row from a Sparse_Row_Reference.
  Sparse_Row(const Sparse_Row_Reference& x);

  //! Assigns a Sparse_Row_Reference to (*this).
  Sparse_Row& operator=(const Sparse_Row_Reference& x);

  //! Swaps (*this) and x.
  void swap(Sparse_Row& x);

  //! Swaps (*this) and x.
  void swap(Sparse_Row_Reference x);

  //! Swaps the i-th element with the j-th element.
  //! Iterators pointing to these elements are invalidated.
  void swap(dimension_type i, dimension_type j);

  //! Swaps the element pointed to by i with the element pointed to by j.
  void swap(iterator i, iterator j);

  //! This method, with this signature, is needed for compatibility with
  //! Dense_Row. It can be called on any row, and it resizes it to \p sz.
  void construct(const dimension_type sz);

  //! This method, with this signature, is needed for compatibility with
  //! Dense_Row. It can be called on any row, and it resizes it to \p sz.
  void construct(const dimension_type sz, const dimension_type capacity);

  //! Resizes the row to the specified size.
  void resize(const dimension_type n);

  //! Provided for compatibility with Dense_Row. It simply calls resize()
  void shrink(dimension_type new_size);

  //! Returns the size of the row.
  dimension_type size() const;

private:
  Unlimited_Sparse_Row row;
  dimension_type size_;

public:
  //! Resets to zero the value pointed to by i.
  //! dangerous_iterator objects equal to i and ++i are invalidated.
  dangerous_iterator reset(dangerous_iterator i);

  //! Resets to zero the values in the range [first,last).
  //! All dangerous_iterator objects in [first,last] are invalidated (note
  //! that last is invalidated, too).
  dangerous_iterator reset(dangerous_iterator first,dangerous_iterator last);

  //! Normalizes the modulo of coefficients so that they are mutually prime.
  /*!
    Computes the Greatest Common Divisor (GCD) among the elements of
    the row and normalizes them by the GCD itself.
  */
  void normalize();

  //! For read-only access it's better to use get(), that avoids allocating
  //! space for zeroes. Both methods are O(n).
  //! If i was not previously stored, or reset(i) was called, this operation
  //! invalidates dangerous_iterator objects equal to the former
  //! lower_bound(i).
  Coefficient& operator[](const dimension_type i);

  //! Equivalent to get(), provided for convenience.
  const Coefficient& operator[](const dimension_type i) const;

  //! Gets the i-th element in the sequence.
  /*!
    This function is O(n).

    This function must not be called before main(), it relies on
    a static variable to work.
  */
  const Coefficient& get(const dimension_type i) const;

  //! A faster equivalent of p1 = &(get(c1)); p1 = &(get(c2));
  void get2(const dimension_type c1,const dimension_type c2,
            const Coefficient*& p1,const Coefficient*& p2) const;

  dangerous_iterator begin();
  dangerous_iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  dangerous_iterator find(const dimension_type c);
  dangerous_iterator lower_bound(const dimension_type c);
  dangerous_iterator upper_bound(const dimension_type c);
  const_iterator find(const dimension_type c) const;
  const_iterator lower_bound(const dimension_type c) const;
  const_iterator upper_bound(const dimension_type c) const;

  //! Equivalent to find_create(i,x,begin()) .
  iterator find_create(const dimension_type i,const Coefficient& x);

  //! Equivalent to (*this)[i]=x , needs itr to point before the added
  //! element. If itr points near the added element, this is faster.
  iterator find_create(const dimension_type i,const Coefficient& x,
                       iterator itr);

  operator Sparse_Row_Reference();
  operator const Unlimited_Sparse_Row&() const;

  PPL_OUTPUT_DECLARATIONS

  bool ascii_load(std::istream& s);

  //! Checks the invariant.
  bool OK() const;
};

class Sparse_Row_Reference {

public:
  //! A const iterator that may skip some zeros in the row.
  typedef Unlimited_Sparse_Row::const_iterator const_iterator;

  //! An iterator that may skip some zeros in the row.
  typedef Unlimited_Sparse_Row::iterator iterator;

  //! An iterator that may skip some zeros in the row.
  //! May be invalidated by apparently unrelated operations, use with care.
  //! See the method documentation for details.
  typedef Unlimited_Sparse_Row::dangerous_iterator dangerous_iterator;

  Sparse_Row_Reference(Unlimited_Sparse_Row& row,const dimension_type size);

  Sparse_Row_Reference& operator=(const Sparse_Row_Reference& x);

  Sparse_Row_Reference& operator=(const Sparse_Row& x);

  //! Swaps this row with the row x. The two rows must have the same size.
  void swap(Sparse_Row_Reference x);

  //! Swaps this row with the row x. The two rows must have the same size.
  void swap(Sparse_Row& x);

  //! Swaps the i-th element with the j-th element.
  //! Iterators pointing to these elements are invalidated.
  void swap(dimension_type i, dimension_type j);

  //! Swaps the element pointed to by i with the element pointed to by j.
  void swap(iterator i, iterator j);

  dimension_type size() const;

  //! Resets to zero the value pointed to by i.
  //! dangerous_iterator objects equal to i and ++i are invalidated.
  dangerous_iterator reset(dangerous_iterator i);

  //! Resets to zero the values in the range [first,last).
  //! All dangerous_iterator objects in [first,last] are invalidated (note
  //! that last is invalidated, too).
  dangerous_iterator reset(dangerous_iterator first,dangerous_iterator last);

  //! Resets to zero the i-th element.
  //! For each dangerous_iterator itr that pointed to i, dangerous_iterator
  //! objects equal to itr and ++itr are invalidated.
  void reset(dimension_type i);

  //! Resets to zero the elements in [i,j).
  //! For each dangerous_iterator i_itr that pointed to i, and j_itr that
  //! pointed to j, dangerous_iterator objects in [i_itr,j_itr] are
  //! invalidated (note that j_itr is invalidated, too).
  void reset(dimension_type i,dimension_type j);

  //! Normalizes the modulo of coefficients so that they are mutually prime.
  /*!
    Computes the Greatest Common Divisor (GCD) among the elements of
    the row and normalizes them by the GCD itself.
  */
  void normalize();

  //! For read-only access it's better to use get(), that avoids allocating
  //! space for zeroes. Both methods are O(n).
  //! If i was not previously stored, or reset(i) was called, this operation
  //! invalidates dangerous_iterator objects equal to the former
  //! lower_bound(i).
  Coefficient& operator[](const dimension_type i);

  //! Equivalent to get(), provided for convenience.
  const Coefficient& operator[](const dimension_type i) const;

  //! Gets the i-th element in the sequence.
  /*!
    This function is O(n).

    This function must not be called before main(), it relies on
    a static variable to work.
  */
  const Coefficient& get(const dimension_type i) const;

  //! A faster equivalent of p1 = &(get(c1)); p1 = &(get(c2));
  void get2(const dimension_type c1,const dimension_type c2,
            const Coefficient*& p1,const Coefficient*& p2) const;

  dangerous_iterator begin();
  dangerous_iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  /*! \brief Executes func on each non-zero element and may execute it on some
             zeros.

      This signature is needed for compatibility with Dense_Row.
      \param func A functor that takes a (Coefficient&) or
                  (const Coefficient&) argument.
      \param n    The logical size of this row (ignored)
  */
  template <typename Func>
  void for_each_nonzero(const Func& func,const dimension_type n);

  /*! \brief Executes func on each non-zero element and may execute it on some
             zeros.

      This signature is needed for compatibility with Dense_Row.
      \param func A functor that takes a (Coefficient&) or
                  (const Coefficient&) argument.
      \param n    The logical size of this row (ignored)
  */
  template <typename Func>
  void for_each_nonzero(const Func& func,const dimension_type n) const;

  dangerous_iterator find(const dimension_type c);
  dangerous_iterator lower_bound(const dimension_type c);
  dangerous_iterator upper_bound(const dimension_type c);
  const_iterator find(const dimension_type c) const;
  const_iterator lower_bound(const dimension_type c) const;
  const_iterator upper_bound(const dimension_type c) const;

  //! Equivalent to find_create(i,x,begin()) .
  iterator find_create(const dimension_type i,const Coefficient& x);

  //! Equivalent to (*this)[i]=x , needs itr to point before the added
  //! element. If itr points near the added element, this is faster.
  iterator find_create(const dimension_type i,const Coefficient& x,
                       iterator itr);

  operator const Unlimited_Sparse_Row&() const;

  //! Checks the invariant.
  bool OK() const;

private:

  /*!
    @c applier_to_data 's @c operator() applies func to the second element of
    its argument.
  */
  template <typename Func>
  class applier_to_data :
    public std::unary_function<std::pair<dimension_type,Coefficient>&,void> {
  public:
    applier_to_data(const Func& func);
    void operator()(std::pair<dimension_type,Coefficient>& x) const;
  private:
    Func f;
  };

  template <typename Func>
  static applier_to_data<Func> apply_to_data(const Func& func);

private:

  Unlimited_Sparse_Row& row;
  const dimension_type size_;
};

} // namespace Parma_Polyhedra_Library

namespace std {

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Specializes <CODE>std::swap</CODE>.
/*! \relates Parma_Polyhedra_Library::Sparse_Row */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
void swap(Parma_Polyhedra_Library::Sparse_Row& x,
          Parma_Polyhedra_Library::Sparse_Row& y);

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Similar to the standard swap, but doesn't need references.
/*! \relates Parma_Polyhedra_Library::Sparse_Row_Reference */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
void swap(Parma_Polyhedra_Library::Sparse_Row_Reference x,
          Parma_Polyhedra_Library::Sparse_Row_Reference y);

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Swaps a Sparse_Row with a Sparse_Row_Reference.
/*! \relates Parma_Polyhedra_Library::Sparse_Row */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
void swap(Parma_Polyhedra_Library::Sparse_Row& x,
          Parma_Polyhedra_Library::Sparse_Row_Reference y);

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Swaps a Sparse_Row_Reference with a Sparse_Row.
/*! \relates Parma_Polyhedra_Library::Sparse_Row_Reference */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
void swap(Parma_Polyhedra_Library::Sparse_Row_Reference x,
          Parma_Polyhedra_Library::Sparse_Row& y);

} // namespace std

#include "Sparse_Row.inlines.hh"

#endif // !defined(PPL_Sparse_Row_defs_hh)