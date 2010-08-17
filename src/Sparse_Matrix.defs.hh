/* Sparse_Matrix class declaration.
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

#ifndef PPL_Sparse_Matrix_defs_hh
#define PPL_Sparse_Matrix_defs_hh 1

#include "Sparse_Matrix.types.hh"
#include "Sparse_Row.defs.hh"
#include "Unlimited_Sparse_Row.defs.hh"
#include "globals.types.hh"
#include <vector>

//! A sparse matrix of Coefficient.
class Parma_Polyhedra_Library::Sparse_Matrix {

public:
  typedef Sparse_Row_Reference row_reference_type;
  typedef const Unlimited_Sparse_Row& row_const_reference_type;
  typedef const Unlimited_Sparse_Row* row_const_pointer_type;
  typedef Sparse_Row_Reference::iterator row_iterator;
  typedef Sparse_Row_Reference::const_iterator row_const_iterator;
  typedef Unlimited_Sparse_Row::const_iterator const_row_const_iterator;
  typedef Sparse_Row row_copy_type;

  class iterator;
  typedef std::vector<Unlimited_Sparse_Row>::const_iterator const_iterator;

  /*!
    \brief Constructs a square matrix with the given size, filled with
           unstored zeroes.

    This method takes \f$O(n)\f$ time.
  */
  explicit Sparse_Matrix(dimension_type n = 0);

  /*!
    \brief Constructs a matrix with the given dimensions, filled with unstored
           zeroes.

    This method takes \f$O(n)\f$ time, where n is \p num_rows.
  */
  Sparse_Matrix(dimension_type num_rows, dimension_type num_columns);

  //! Swaps (*this) with x.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  void swap(Sparse_Matrix& x);

  //! Returns an iterator pointing to the first row.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  iterator begin();

  //! Returns an iterator pointing after the last row.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  iterator end();

  //! Returns an iterator pointing to the first row.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  const_iterator begin() const;

  //! Returns an iterator pointing after the last row.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  const_iterator end() const;

  //! Returns a reference to the i-th row.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  Sparse_Row_Reference operator[](dimension_type i);

  //! Returns a const reference to the i-th row.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  const Unlimited_Sparse_Row& operator[](dimension_type i) const;

  //! Returns the number of rows in the matrix.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  dimension_type num_rows() const;

  //! Returns the number of columns in the matrix.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  dimension_type num_columns() const;

  //! Removes the i-th from the matrix, shifting other columns to the left.
  /*!
    This operation invalidates existing iterators on rows' elements.

    This method takes \f$O(k + \sum_{j=1}^{r} \log n_j)\f$ expected time, where k
    is the number of stored elements with column index greater than i, r the
    number of rows in this matrix and \f$n_j\f$ the number of stored elements in
    row j.
    A weaker (but simpler) bound is \f$O(r*(c-i+\log c))\f$, where r is the
    number of rows, c is the number of columns and i is the parameter passed
    to this method.
  */
  void remove_column(dimension_type i);

  //! Permutes the columns of the matrix.
  /*!
    This method is provided for compatibilty with Dense_Matrix but it is slow
    and should be avoided if possible.

    \param cycles
    A vector representing the non-trivial cycles of the permutation
    according to which the columns must be rearranged.

    The \p cycles vector contains, one after the other, the
    non-trivial cycles (i.e., the cycles of length greater than one)
    of a permutation of \e non-zero column indexes.  Each cycle is
    terminated by zero.  For example, assuming the matrix has 7
    columns, the permutation \f$ \{ 1 \mapsto 3, 2 \mapsto 4,
    3 \mapsto 6, 4 \mapsto 2, 5 \mapsto 5, 6 \mapsto 1 \}\f$ can be
    represented by the non-trivial cycles \f$(1 3 6)(2 4)\f$ that, in
    turn can be represented by a vector of 6 elements containing 1, 3,
    6, 0, 2, 4, 0.

    This method takes \f$O(k*\sum_{j=1}^{r} \log n_j)\f$ expected time, where k is
    the size of the \p cycles vector, r the number of rows and \f$n_j\f$ the
    number of stored elements in row j.
    A weaker (but simpler) bound is \f$O(k*r*\log c )\f$, where k is the size of
    the \p cycles vector, r is the number of rows and c is the number of
    columns.

    \note
    The first column of the matrix, having index zero, is never involved
    in a permutation.
  */
  void permute_columns(const std::vector<dimension_type>& cycles);

  //! Equivalent to resize(n, n).
  void resize(dimension_type n);

  //! Resizes this matrix to the specified dimensions.
  /*!
    New rows and columns will contain non-stored zeroes.

    This operation invalidates existing iterators.

    Adding n rows takes \f$O(n)\f$ amortized time.

    Adding n columns takes \f$O(1)\f$ time.

    Removing n rows takes \f$O(n+k)\f$ amortized time, where k is the total number
    of stored elements in the removed rows.

    Removing n columns takes \f$O(\sum_{j=1}^{r} k_j*\log n_j)\f$ time, where r
    is the number of rows, \f$k_j\f$ is the number of stored elements in the
    columns of the j-th row that must be removed and \f$n_j\f$ is the number of
    stored elements in the j-th row.
    A weaker (but simpler) bound is \f$O(k*\log c)\f$, where k is the number of
    elements that have to be removed and c is the number of columns.
  */
  void resize(dimension_type num_rows, dimension_type num_columns);

  //! Equivalent to resize(0,0).
  /*!
    Provided for compatibility with Dense_Matrix.
  */
  void clear();

  //! Adds to the matrix \p n rows of zeroes.
  /*!
    Provided for compatibility with Dense_Matrix.

    \param n
    The number of rows to be added: must be strictly positive.

    Turns the \f$r \times c\f$ matrix \f$M\f$ into
    the \f$(r+n) \times c\f$ matrix \f$\genfrac{(}{)}{0pt}{}{M}{0}\f$.

    This operation invalidates existing iterators.

    This method takes \f$O(n)\f$ amortized time.
  */
  void add_zero_rows(dimension_type n);

  //! Adds \p n columns of zeroes to the matrix.
  /*!
    Provided for compatibility with Dense_Matrix.

    \param n
    The number of columns to be added: must be strictly positive.

    Turns the \f$r \times c\f$ matrix \f$M\f$ into
    the \f$r \times (c+n)\f$ matrix \f$(M \, 0)\f$.

    This operation invalidates existing iterators.

    This method takes \f$O(1)\f$ time.
  */
  void add_zero_columns(dimension_type n);

  //! Adds \p n columns of non-stored zeroes to the matrix before column i.
  /*!
    This operation invalidates existing iterators.

    This method takes \f$O(\sum_{j=1}^{r} k_j+\log n_j)\f$ expected time, where r
    is the number of rows, \f$k_j\f$ is the number of stored elements in the
    columns of the j-th row that must be shifted and \f$n_j\f$ is the number of
    stored elements in the j-th row.
    A weaker (but simpler) bound is \f$O(k+r*\log c)\f$ time, where k is the
    number of elements that must be shifted, r is the number of the rows and c
    is the number of the columns.
  */
  void add_zero_columns(dimension_type n, dimension_type i);

  //! Adds \p n rows and \p m columns of zeroes to the matrix.
  /*!
    Provided for compatibility with Dense_Matrix.

    \param n
    The number of rows to be added: must be strictly positive.

    \param m
    The number of columns to be added: must be strictly positive.

    Turns the \f$r \times c\f$ matrix \f$M\f$ into
    the \f$(r+n) \times (c+m)\f$ matrix
    \f$\bigl(\genfrac{}{}{0pt}{}{M}{0} \genfrac{}{}{0pt}{}{0}{0}\bigr)\f$.

    This operation invalidates existing iterators.

    This method takes \f$O(n)\f$ amortized time.
  */
  void add_zero_rows_and_columns(dimension_type n, dimension_type m);

  //! Adds a copy of the row \p x to the matrix.
  /*!
    This operation invalidates existing iterators.

    This method takes \f$O(n)\f$ amortized time.
  */
  void add_row(const Sparse_Row& x);

  //! Adds the row \p x to the matrix.
  /*!
    This operation invalidates existing iterators.

    This method takes \f$O(n)\f$ amortized time.
  */
  void add_row(const Sparse_Row_Reference& x);

  //! Adds a copy of the row \p x to the matrix.
  /*!
    This operation invalidates existing iterators.

    This method takes \f$O(n)\f$ amortized time.
  */
  void add_row(const Unlimited_Sparse_Row& x);

  //! Shrinks the matrix by removing its \p n trailing columns.
  /*!
    This method is provided for compatibility with Dense_Matrix.

    This operation invalidates existing iterators.

    This method takes \f$O(\sum_{j=1}^r k_j*\log n_j)\f$ amortized time, where r
    is the number of rows, \f$k_j\f$ is the number of elements that have to be
    removed from row j and \f$n_j\f$ is the total number of elements stored in
    row j.
    A weaker (but simpler) bound is \f$O(r*n*\log c)\f$, where r is the number of
    rows, c the number of columns and n the parameter passed to this method.
  */
  void remove_trailing_columns(dimension_type n);

  //! Loads the row from an ASCII representation generated using ascii_dump().
  /*!
    This method takes \f$O(n*\log n)\f$ time.
  */
  bool ascii_load(std::istream& s);

  PPL_OUTPUT_DECLARATIONS

  /*! \brief
    Erases from the matrix all the rows but those having
    an index less than \p first_to_erase.

    Provided for compatibility with Dense_Row.
    It is equivalent to resize(first_to_erase,num_columns()).

    This method takes \f$O(n+k)\f$ amortized time, where k is the total number
    of stored elements in the removed rows and n is the number of removed
    rows.
  */
  void erase_to_end(dimension_type first_to_erase);

  //! Returns the total size in bytes of the memory occupied by \p *this.
  /*!
    This method is \f$O(r+k)\f$, where r is the number of rows and k is the number
    of stored elements in the matrix.
  */
  memory_size_type total_memory_in_bytes() const;

  //! Returns the size in bytes of the memory managed by \p *this.
  /*!
    This method is \f$O(r+k)\f$, where r is the number of rows and k is the number
    of stored elements in the matrix.
  */
  memory_size_type external_memory_in_bytes() const;

  //! Checks if all the invariants are satisfied.
  bool OK() const;

private:
  //! The vector that stores the matrix's elements.
  std::vector<Unlimited_Sparse_Row> rows;

  //! The number of columns in this matrix.
  dimension_type num_columns_;
};

//! An iterator over the matrix's rows.
class Parma_Polyhedra_Library::Sparse_Matrix::iterator {

public:
  //! The copy constructor.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  iterator(const iterator&);

  //! Assigns itr into *this.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  iterator& operator=(const iterator& itr);

  //! Compares itr with *this.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  bool operator==(const iterator& itr) const;

  //! Compares itr with *this.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  bool operator!=(const iterator& itr) const;

  //! Returns a reference to the pointed row.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  Sparse_Row_Reference operator*();

  //! Advances to the next row.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  iterator& operator++();

  //! Advances to the next row.
  /*!
    This method takes \f$O(1)\f$ time.
  */
  iterator operator++(int);

private:
  //! The default constructor.
  /*!
    \param size is the number of columns in the matrix.

    This is private so only Sparse_Matrix can access this.

    This method takes \f$O(1)\f$ time.
  */
  iterator(std::vector<Unlimited_Sparse_Row>::iterator,
           dimension_type size);

  //! The wrapped iterator.
  std::vector<Unlimited_Sparse_Row>::iterator itr;

  //! The number of columns in the matrix.
  const dimension_type size_;

  friend class Parma_Polyhedra_Library::Sparse_Matrix;
};

namespace std {

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Specializes <CODE>std::swap</CODE>.
/*! \relates Parma_Polyhedra_Library::Sparse_Matrix */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
void swap(Parma_Polyhedra_Library::Sparse_Matrix& x,
          Parma_Polyhedra_Library::Sparse_Matrix& y);

} // namespace std


#include "Sparse_Matrix.inlines.hh"

#endif // !defined(PPL_Sparse_Matrix_defs_hh)
