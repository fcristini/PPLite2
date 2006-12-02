/* Metaprogramming utilities.
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

#ifndef PPL_meta_programming_hh
#define PPL_meta_programming_hh 1

namespace Parma_Polyhedra_Library {

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  Declares a per-class constant of type <CODE>bool</CODE>, called \p name
  and with value \p value.

  Differently from static constants, \p name needs not (and cannot) be
  defined (for static constants, the need for a further definition is
  mandated by Section 9.4.2/4 of the C++ standard).
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
#define const_bool_nodef(name, value)		\
  enum { name = (value) }

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  Declares a per-class constant of type <CODE>int</CODE>, called \p name
  and with value \p value.

  Differently from static constants, \p name needs not (and cannot) be
  defined (for static constants, the need for a further definition is
  mandated by Section 9.4.2/4 of the C++ standard).
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
#define const_int_nodef(name, value) \
  enum { name = (value) }

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  Declares a per-class constant of type \p type, called \p name
  and with value \p value.  The value of the constant is accessible
  by means of the syntax <CODE>name()</CODE>.

  Differently from static constants, \p name needs not (and cannot) be
  defined (for static constants, the need for a further definition is
  mandated by Section 9.4.2/4 of the C++ standard).
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
#define const_value_nodef(type, name, value)	\
  static type name() {				\
    return value;				\
  }

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  Declares a per-class constant of type \p type, called \p name
  and with value \p value.  A constant reference to the constant
  is accessible by means of the syntax <CODE>name()</CODE>.

  Differently from static constants, \p name needs not (and cannot) be
  defined (for static constants, the need for a further definition is
  mandated by Section 9.4.2/4 of the C++ standard).
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
#define const_ref_nodef(type, name, value)				\
  static const type& name() {						\
    static type name(value);						\
    return name;							\
  }

template <bool>
struct Compile_Time_Check;

template <>
struct Compile_Time_Check<true> { };

#define COMPILE_TIME_CHECK_NAME(suf) compile_time_check_ ## suf
#define COMPILE_TIME_CHECK_AUX(e, suf)					\
  enum { COMPILE_TIME_CHECK_NAME(suf) = sizeof(Parma_Polyhedra_Library::Compile_Time_Check<static_cast<bool>(e)>) }

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  Produces a compilation error if the compile-time constant \p e does
  not evaluate to <CODE>true</CODE>
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
#define COMPILE_TIME_CHECK(e, msg) COMPILE_TIME_CHECK_AUX(e, __LINE__)

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  A class holding a constant called <CODE>value</CODE> that evaluates
  to \p b.
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
template <bool b>
struct Bool {
  enum {
    value = b
  };
};

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  A class holding a constant called <CODE>value</CODE> that evaluates
  to <CODE>true</CODE>.
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
struct True : public Bool<true> {
};

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  A class holding a constant called <CODE>value</CODE> that evaluates
  to <CODE>false</CODE>.
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
struct False : public Bool<false> {
};

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  A class holding a constant called <CODE>value</CODE> that evaluates
  to <CODE>true</CODE> if and only if \p T1 is the same type as \p T2.

  This is the non-specialized case, in which \p T1 and \p T2 can be different.
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
template <typename T1, typename T2>
struct Is_Same : public False {
};

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  A class holding a constant called <CODE>value</CODE> that evaluates
  to <CODE>true</CODE> if and only if \p T1 is the same type as \p T2.

  This is the specialization in which \p T1 and \p T2 are equal.
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
template <typename T>
struct Is_Same<T, T> : public True {
};

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  A class holding a constant called <CODE>value</CODE> that evaluates
  to <CODE>true</CODE> if and only if \p Base is the same type as \p Derived
  or \p Derived is a class derived from \p Base.

  \note
  Care must be taken to use this predicate with template classes.
  Suppose we have
  \code
  template <typename T> struct B;
  template <typename T> struct D : public B<T>;
  \endcode
  Of course, we cannot test if, for some type variable <CODE>U</CODE>,
  we have <CODE>Is_Same_Or_Derived<B<U>, Type>::value == true</CODE>.
  But we can do as follows:
  \code
  struct B_Base {
  };

  template <typename T> struct B : public B_Base;
  \endcode
  This enables us to enquire
  <CODE>Is_Same_Or_Derived<B_Base, Type>::value</CODE>.
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
template <typename Base, typename Derived>
struct Is_Same_Or_Derived {
  //! A class that is constructible from just anything.
  struct Any {
    //! The universal constructor.
    template <typename T>
    Any(const T&);
  };

  //! Overloading with \p Base.
  static char func(const Base&);

  //! Overloading with \p Any.
  static double func(Any);

  //! A function obtaining a const reference to a \p Derived object.
  static const Derived& derived_object();

  COMPILE_TIME_CHECK(sizeof(char) != sizeof(double),
		     "architecture with sizeof(char) == sizeof(double) (!?)");

  enum {
    /*!
      Assuming <CODE>sizeof(char) != sizeof(double)</CODE>, the C++
      overload resolution mechanism guarantees that \p value evaluates
      to <CODE>true</CODE> if and only if \p Base is the same type
      as \p Derived or \p Derived is a class derived from \p Base.
    */
    value = (sizeof(func(derived_object())) == sizeof(char))
  };
};

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  A class that provides a type member called <CODE>type</CODE> equivalent
  to \p T if and only if \p b is <CODE>true</CODE>.

  This is the non-specialized case, in which the <CODE>type</CODE> member
  is not present.
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
template <bool b, typename T = void>
struct Enable_If {
};

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
/*! \brief
  A class that provides a type member called <CODE>type</CODE> equivalent
  to \p T if and only if \p b is <CODE>true</CODE>.

  This is the specialization in which the <CODE>type</CODE> member
  is present.

  \note
  Let <CODE>T</CODE>, <CODE>T1</CODE> and <CODE>T2</CODE> be any type
  expressions and suppose we have some template function
  <CODE>T f(T1, T2)</CODE>.  If we want to declare a specialization
  that is enabled only if some compile-time checkable condition holds,
  we simply declare the specialization by
  \code
  template ...
  typename Enable_If<condition, T>::type
  foo(T1 x, T2 y);
  \endcode
  For all the instantiations of the template parameters that cause
  <CODE>condition</CODE> to evaluate to <CODE>false</CODE>,
  the <CODE>Enable_If<condition, T>::type</CODE> member will not be defined.
  Hence, for that instantiations, the specialization will not be eligible.
*/
#endif // PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
template <typename T>
struct Enable_If<true, T> {
  typedef T type;
};

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_meta_programming_hh)
