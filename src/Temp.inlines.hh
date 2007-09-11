/* Temp_* class implementation: inline functions.
   Copyright (C) 2001-2007 Roberto Bagnara <bagnara@cs.unipr.it>

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

#ifndef PPL_Temp_inlines_hh
#define PPL_Temp_inlines_hh 1

#include "meta_programming.hh"

namespace Parma_Polyhedra_Library {

template <typename T>
Temp_Item<T>::Temp_Item()
  : item_() {
}

template <typename T>
T&
Temp_Item<T>::item() {
    return item_;
}

template <typename T>
Temp_Item<T>&
Temp_Item<T>::obtain() {
  if (free_list_head != 0) {
    Temp_Item* p = free_list_head;
    free_list_head = free_list_head->next;
    return *p;
  }
  else
    return *new Temp_Item();
}

template <typename T>
void
Temp_Item<T>::release(Temp_Item& p) {
  p.next = free_list_head;
  free_list_head = &p;
}

template <typename T>
Temp_Real_Holder<T>::Temp_Real_Holder(Temp_Item<T>& obj)
  : hold(obj) {
}

template <typename T>
Temp_Real_Holder<T>::~Temp_Real_Holder() {
  Temp_Item<T>::release(hold);
}

template <typename T>
T&
Temp_Real_Holder<T>::item() {
  return hold.item();
}

template <typename T>
Temp_Null_Holder<T>::Temp_Null_Holder() {
}

template <typename T>
T
Temp_Null_Holder<T>::item() {
  return item_;
}

template <typename T>
typename Temp_List<T>::holder_type
Temp_List<T>::obtain_holder() {
  return Temp_Real_Holder<T>(Temp_Item<T>::obtain());
}

template <typename T>
typename Temp_Local<T>::holder_type
Temp_Local<T>::obtain_holder() {
  return Temp_Null_Holder<T>();
}

} // namespace Parma_Polyhedra_Library

#define DIRTY_TEMP(T, id)						\
  typename Dirty_Temp<T>::holder_type holder ## id =			\
    Dirty_Temp<T>::obtain_holder();					\
  typename Dirty_Temp<T>::type id = holder ## id.item()

#define DIRTY_TEMP0(T, id)						\
  Dirty_Temp<T>::holder_type holder ## id =				\
    Dirty_Temp<T>::obtain_holder();					\
  Dirty_Temp<T>::type id = holder ## id.item()

#endif // !defined(PPL_Temp_inlines_hh)
