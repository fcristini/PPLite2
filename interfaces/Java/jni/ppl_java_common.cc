/* PPL Java interface common routines implementation.
   Copyright (C) 2001-2009 Roberto Bagnara <bagnara@cs.unipr.it>

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

#include "ppl_java_common.defs.hh"

namespace Parma_Polyhedra_Library {

namespace Interfaces {

namespace Java {

// Define class and field/method ID caches.
Java_Class_Cache cached_classes;
Java_FMID_Cache cached_FMIDs;

Java_Class_Cache::Java_Class_Cache() {
  // Non-PPL classes.
  Boolean = NULL;
  Integer = NULL;
  Long = NULL;
  Iterator = NULL;
  // PPL classes.
  By_Reference = NULL;
  Coefficient = NULL;
  Congruence = NULL;
  Constraint = NULL;
  Generator = NULL;
  Grid_Generator = NULL;
  Generator_Type = NULL;
  Grid_Generator_Type = NULL;
  Constraint_System = NULL;
  Congruence_System = NULL;
  Generator_System = NULL;
  Grid_Generator_System = NULL;
  Linear_Expression = NULL;
  Linear_Expression_Coefficient = NULL;
  Linear_Expression_Difference = NULL;
  Linear_Expression_Sum = NULL;
  Linear_Expression_Times = NULL;
  Linear_Expression_Unary_Minus = NULL;
  Linear_Expression_Variable = NULL;
  MIP_Problem_Status = NULL;
  Optimization_Mode = NULL;
  Pair = NULL;
  Poly_Con_Relation = NULL;
  Poly_Gen_Relation = NULL;
  PPL_Object = NULL;
  Relation_Symbol = NULL;
  Variable = NULL;
  Variables_Set = NULL;
}

void
Java_Class_Cache::init_cache(JNIEnv* env, jclass& field, const char* name) {
  assert(env != NULL);
  if (field != NULL) {
    env->DeleteGlobalRef(field);
  }
  jclass jni_class = env->FindClass(name);
  CHECK_RESULT_ASSERT(env, jni_class);
  field = (jclass) env->NewGlobalRef(jni_class);
  CHECK_RESULT_ASSERT(env, field);
}

void
Java_Class_Cache::init_cache(JNIEnv* env) {
  assert(env != NULL);
  // Non-PPL classes.
  init_cache(env, Boolean, "java/lang/Boolean");
  init_cache(env, Integer, "java/lang/Integer");
  init_cache(env, Long, "java/lang/Long");
  init_cache(env, Iterator, "java/util/Iterator");
  // PPL classes.
  init_cache(env, By_Reference, "parma_polyhedra_library/By_Reference");
  init_cache(env, Coefficient, "parma_polyhedra_library/Coefficient");
  init_cache(env, Congruence, "parma_polyhedra_library/Congruence");
  init_cache(env, Constraint, "parma_polyhedra_library/Constraint");
  init_cache(env, Generator, "parma_polyhedra_library/Generator");
  init_cache(env, Grid_Generator, "parma_polyhedra_library/Grid_Generator");
  init_cache(env, Generator_Type, "parma_polyhedra_library/Generator_Type");
  init_cache(env, Grid_Generator_Type,
             "parma_polyhedra_library/Grid_Generator_Type");
  init_cache(env, Constraint_System,
             "parma_polyhedra_library/Constraint_System");
  init_cache(env, Congruence_System,
             "parma_polyhedra_library/Congruence_System");
  init_cache(env, Generator_System,
             "parma_polyhedra_library/Generator_System");
  init_cache(env, Grid_Generator_System,
             "parma_polyhedra_library/Grid_Generator_System");
  init_cache(env, Linear_Expression,
             "parma_polyhedra_library/Linear_Expression");
  init_cache(env, Linear_Expression_Coefficient,
             "parma_polyhedra_library/Linear_Expression_Coefficient");
  init_cache(env, Linear_Expression_Difference,
             "parma_polyhedra_library/Linear_Expression_Difference");
  init_cache(env, Linear_Expression_Sum,
             "parma_polyhedra_library/Linear_Expression_Sum");
  init_cache(env, Linear_Expression_Times,
             "parma_polyhedra_library/Linear_Expression_Times");
  init_cache(env, Linear_Expression_Unary_Minus,
             "parma_polyhedra_library/Linear_Expression_Unary_Minus");
  init_cache(env, Linear_Expression_Variable,
             "parma_polyhedra_library/Linear_Expression_Variable");
  init_cache(env, MIP_Problem_Status,
             "parma_polyhedra_library/MIP_Problem_Status");
  init_cache(env, Optimization_Mode,
             "parma_polyhedra_library/Optimization_Mode");
  init_cache(env, Pair, "parma_polyhedra_library/Pair");
  init_cache(env, Poly_Con_Relation,
             "parma_polyhedra_library/Poly_Con_Relation");
  init_cache(env, Poly_Gen_Relation,
             "parma_polyhedra_library/Poly_Gen_Relation");
  init_cache(env, PPL_Object, "parma_polyhedra_library/PPL_Object");
  init_cache(env, Relation_Symbol, "parma_polyhedra_library/Relation_Symbol");
  init_cache(env, Variable, "parma_polyhedra_library/Variable");
  init_cache(env, Variables_Set, "parma_polyhedra_library/Variables_Set");
}

void
Java_Class_Cache::clear_cache(JNIEnv* env, jclass& field) {
  assert(env != NULL);
  if (field != NULL) {
    env->DeleteGlobalRef(field);
    field = NULL;
  }
}

void
Java_Class_Cache::clear_cache(JNIEnv* env) {
  assert(env != NULL);
  // Non-PPL classes.
  clear_cache(env, Boolean);
  clear_cache(env, Integer);
  clear_cache(env, Long);
  clear_cache(env, Iterator);
  // PPL classes.
  clear_cache(env, By_Reference);
  clear_cache(env, Coefficient);
  clear_cache(env, Congruence);
  clear_cache(env, Constraint);
  clear_cache(env, Generator);
  clear_cache(env, Grid_Generator);
  clear_cache(env, Generator_Type);
  clear_cache(env, Grid_Generator_Type);
  clear_cache(env, Constraint_System);
  clear_cache(env, Congruence_System);
  clear_cache(env, Generator_System);
  clear_cache(env, Grid_Generator_System);
  clear_cache(env, Linear_Expression);
  clear_cache(env, Linear_Expression_Coefficient);
  clear_cache(env, Linear_Expression_Difference);
  clear_cache(env, Linear_Expression_Sum);
  clear_cache(env, Linear_Expression_Times);
  clear_cache(env, Linear_Expression_Unary_Minus);
  clear_cache(env, Linear_Expression_Variable);
  clear_cache(env, MIP_Problem_Status);
  clear_cache(env, Optimization_Mode);
  clear_cache(env, Pair);
  clear_cache(env, Poly_Con_Relation);
  clear_cache(env, Poly_Gen_Relation);
  clear_cache(env, PPL_Object);
  clear_cache(env, Relation_Symbol);
  clear_cache(env, Variable);
  clear_cache(env, Variables_Set);
}

void
handle_exception(JNIEnv* env, const std::overflow_error& e) {
  jclass newExcCls
    = env->FindClass("parma_polyhedra_library/Overflow_Error_Exception");
  CHECK_RESULT_ASSERT(env, newExcCls);
  jint ret = env->ThrowNew(newExcCls, e.what());
  CHECK_RESULT_ABORT(env, ret);
}

void
handle_exception(JNIEnv* env, const std::invalid_argument& e) {
  jclass newExcCls
    = env->FindClass("parma_polyhedra_library/Invalid_Argument_Exception");
  CHECK_RESULT_ASSERT(env, newExcCls);
  jint ret = env->ThrowNew(newExcCls, e.what());
  CHECK_RESULT_ABORT(env, ret);
}

void
handle_exception(JNIEnv* env, const std::logic_error& e) {
  jclass newExcCls
    = env->FindClass("parma_polyhedra_library/Logic_Error_Exception");
  CHECK_RESULT_ASSERT(env, newExcCls);
  jint ret = env->ThrowNew(newExcCls, e.what());
  CHECK_RESULT_ABORT(env, ret);
}

void
handle_exception(JNIEnv* env, const std::length_error& e) {
  jclass newExcCls
    = env->FindClass("parma_polyhedra_library/Length_Error_Exception");
  CHECK_RESULT_ASSERT(env, newExcCls);
  jint ret = env->ThrowNew(newExcCls, e.what());
  CHECK_RESULT_ABORT(env, ret);
}

void
handle_exception(JNIEnv* env, const std::domain_error& e) {
  jclass newExcCls
    = env->FindClass("parma_polyhedra_library/Domain_Error_Exception");
  CHECK_RESULT_ASSERT(env, newExcCls);
  jint ret = env->ThrowNew(newExcCls, e.what());
  CHECK_RESULT_ABORT(env, ret);
}

void
handle_exception(JNIEnv* env, const std::bad_alloc&) {
  jclass newExcCls
    = env->FindClass("java/lang/RuntimeException");
  CHECK_RESULT_ASSERT(env, newExcCls);
  jint ret = env->ThrowNew(newExcCls, "Out of memory");
  CHECK_RESULT_ABORT(env, ret);
}

void
handle_exception(JNIEnv* env, const std::exception& e) {
  jclass newExcCls = env->FindClass("java/lang/RuntimeException");
  CHECK_RESULT_ASSERT(env, newExcCls);
  jint ret = env->ThrowNew(newExcCls, e.what());
  CHECK_RESULT_ABORT(env, ret);
}

void
handle_exception(JNIEnv* env) {
  jclass newExcCls = env->FindClass("java/lang/RuntimeException");
  CHECK_RESULT_ASSERT(env, newExcCls);
  jint ret = env->ThrowNew(newExcCls, "PPL bug: unknown exception raised");
  CHECK_RESULT_ABORT(env, ret);
}

jobject
build_java_poly_gen_relation(JNIEnv* env, Poly_Gen_Relation& r) {
  jint j_value = 0;
  while (r != Poly_Gen_Relation::nothing()) {
    if (r.implies(Poly_Gen_Relation::subsumes())) {
      j_value += 1;
      r = r - Poly_Gen_Relation::subsumes();
    }
  }
  jobject ret = env->NewObject(cached_classes.Poly_Gen_Relation,
			       cached_FMIDs.Poly_Gen_Relation_init_ID,
                               j_value);
  CHECK_RESULT_THROW(env, ret);
  return ret;
}

jobject
build_java_poly_con_relation(JNIEnv* env, Poly_Con_Relation& r) {
  jint j_value = 0;
  while (r != Poly_Con_Relation::nothing()) {
    if (r.implies(Poly_Con_Relation::is_disjoint())) {
      j_value += 1;
      r = r - Poly_Con_Relation::is_disjoint();
    }
    else if (r.implies(Poly_Con_Relation::strictly_intersects())) {
      j_value += 2;
      r = r - Poly_Con_Relation::strictly_intersects();
    }
    else if (r.implies(Poly_Con_Relation::is_included())) {
      j_value += 4;
      r = r - Poly_Con_Relation::is_included();
    }
    else if (r.implies(Poly_Con_Relation::saturates())) {
      j_value += 8;
      r = r - Poly_Con_Relation::saturates();
    }
  }
  jobject ret = env->NewObject(cached_classes.Poly_Con_Relation,
			       cached_FMIDs.Poly_Con_Relation_init_ID,
                               j_value);
  CHECK_RESULT_THROW(env, ret);
  return ret;
}


Congruence
build_cxx_congruence(JNIEnv* env, jobject j_congruence) {
  jobject j_modulus
    = env->GetObjectField(j_congruence, cached_FMIDs.Congruence_modulus_ID);
  jobject j_lhs
    = env->GetObjectField(j_congruence, cached_FMIDs.Congruence_lhs_ID);
  jobject j_rhs
    = env->GetObjectField(j_congruence, cached_FMIDs.Congruence_rhs_ID);
  PPL_DIRTY_TEMP_COEFFICIENT(ppl_modulus);
  ppl_modulus = build_cxx_coeff(env, j_modulus);
  Linear_Expression lhs = build_cxx_linear_expression(env, j_lhs);
  Linear_Expression rhs = build_cxx_linear_expression(env, j_rhs);
  return (lhs %= rhs) / ppl_modulus;
}

jobject
bool_to_j_boolean(JNIEnv* env, const bool value) {
  jobject ret = env->CallStaticObjectMethod(cached_classes.Boolean,
                                            cached_FMIDs.Boolean_valueOf_ID,
                                            value);
  CHECK_EXCEPTION_ASSERT(env);
  return ret;
}

jobject
j_long_to_j_long_class(JNIEnv* env, jlong jlong_value) {
  jobject ret = env->CallStaticObjectMethod(cached_classes.Long,
                                            cached_FMIDs.Long_valueOf_ID,
                                            jlong_value);
  CHECK_EXCEPTION_THROW(env);
  return ret;
}

jlong
j_long_class_to_j_long(JNIEnv* env, jobject j_long) {
  jlong ret = env->CallLongMethod(j_long, cached_FMIDs.Long_longValue_ID);
  CHECK_EXCEPTION_ASSERT(env);
  return ret;
}

jobject
j_int_to_j_integer(JNIEnv* env, jint jint_value) {
  jobject ret = env->CallStaticObjectMethod(cached_classes.Integer,
                                            cached_FMIDs.Integer_valueOf_ID,
                                            jint_value);
  CHECK_EXCEPTION_THROW(env);
  return ret;
}

jint
j_integer_to_j_int(JNIEnv* env, jobject j_integer) {
  jint ret = env->CallIntMethod(j_integer, cached_FMIDs.Integer_intValue_ID);
  CHECK_EXCEPTION_ASSERT(env);
  return ret;
}

Variables_Set
build_cxx_variables_set(JNIEnv* env, jobject j_v_set) {
  // Get the iterator.
  jobject j_iter
    = env->CallObjectMethod(j_v_set, cached_FMIDs.Variables_Set_iterator_ID);
  CHECK_EXCEPTION_THROW(env);
  // Get method IDs from cache.
  jmethodID has_next_ID = cached_FMIDs.Variables_Set_Iterator_has_next_ID;
  jmethodID next_ID = cached_FMIDs.Variables_Set_Iterator_next_ID;
  // Initialize an empty set of variables.
  Variables_Set v_set;
  jobject j_variable;
  jboolean has_next_value = env->CallBooleanMethod(j_iter, has_next_ID);
  while (has_next_value) {
    j_variable = env->CallObjectMethod(j_iter, next_ID);
    CHECK_EXCEPTION_ASSERT(env);
    v_set.insert(build_cxx_variable(env, j_variable));
    has_next_value = env->CallBooleanMethod(j_iter, has_next_ID);
    CHECK_EXCEPTION_ASSERT(env);
  }
  return v_set;
}

jobject
build_java_variables_set(JNIEnv* env, const Variables_Set& v_set) {
  jobject j_vs = env->NewObject(cached_classes.Variables_Set,
                                cached_FMIDs.Variables_Set_init_ID);
  CHECK_RESULT_THROW(env, j_vs);
  for (Variables_Set::const_iterator v_begin = v_set.begin(),
	 v_end = v_set.end(); v_begin != v_end; ++v_begin) {
    Variable var(*v_begin);
    jobject j_variable = build_java_variable(env, var);
    env->CallBooleanMethod(j_vs,
                           cached_FMIDs.Variables_Set_add_ID,
                           j_variable);
    CHECK_EXCEPTION_THROW(env);
  }
  return j_vs;
}

Relation_Symbol
build_cxx_relsym(JNIEnv* env, jobject j_relsym) {
  jint rel_sym
    = env->CallIntMethod(j_relsym, cached_FMIDs.Relation_Symbol_ordinal_ID);
  CHECK_EXCEPTION_ASSERT(env);
  switch (rel_sym) {
  case 0:
    return LESS_THAN;
  case 1:
    return LESS_OR_EQUAL;
  case 2:
    return EQUAL;
  case 3:
    return GREATER_OR_EQUAL;
  case 4:
    return GREATER_THAN;
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
}

Optimization_Mode
build_cxx_optimization_mode(JNIEnv* env, jobject j_opt_mode) {
  jint opt_mode
    = env->CallIntMethod(j_opt_mode, cached_FMIDs.Optimization_Mode_ordinal_ID);
  CHECK_EXCEPTION_ASSERT(env);
  switch (opt_mode) {
  case 0:
    return MINIMIZATION;
  case 1:
    return MAXIMIZATION;
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
}

jobject
build_java_mip_status(JNIEnv* env, const MIP_Problem_Status& mip_status) {
  jfieldID fID;
  switch (mip_status) {
  case UNFEASIBLE_MIP_PROBLEM:
    fID = cached_FMIDs.MIP_Problem_Status_UNFEASIBLE_MIP_PROBLEM_ID;
    break;
  case UNBOUNDED_MIP_PROBLEM:
    fID = cached_FMIDs.MIP_Problem_Status_UNBOUNDED_MIP_PROBLEM_ID;
    break;
  case OPTIMIZED_MIP_PROBLEM:
    fID = cached_FMIDs.MIP_Problem_Status_OPTIMIZED_MIP_PROBLEM_ID;
    break;
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
  return env->GetStaticObjectField(cached_classes.MIP_Problem_Status, fID);
}

jobject
build_java_optimization_mode(JNIEnv* env, const Optimization_Mode& opt_mode) {
  jfieldID fID;
  switch (opt_mode) {
  case MINIMIZATION:
    fID = cached_FMIDs.Optimization_Mode_MINIMIZATION_ID;
    break;
  case MAXIMIZATION:
    fID = cached_FMIDs.Optimization_Mode_MAXIMIZATION_ID;
    break;
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
  return env->GetStaticObjectField(cached_classes.Optimization_Mode, fID);
}

MIP_Problem::Control_Parameter_Name
build_cxx_control_parameter_name(JNIEnv* env, jobject j_cp_name) {
  jclass cp_name_class = env->GetObjectClass(j_cp_name);
  CHECK_RESULT_ASSERT(env, cp_name_class);
  jmethodID cp_name_ordinal_id
    = env->GetMethodID(cp_name_class, "ordinal", "()I");
  CHECK_RESULT_ASSERT(env, cp_name_ordinal_id);
  jint cp_name = env->CallIntMethod(j_cp_name, cp_name_ordinal_id);
  CHECK_EXCEPTION_ASSERT(env);
  switch (cp_name) {
  case 0:
    return MIP_Problem::PRICING;
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
}

jobject
build_java_control_parameter_name
(JNIEnv* env,const MIP_Problem::Control_Parameter_Name& cp_name) {
  jclass j_cp_name_class
    = env->FindClass("parma_polyhedra_library/Control_Parameter_Name");
  CHECK_RESULT_ASSERT(env, j_cp_name_class);
  jfieldID cp_name_pricing_get_id
    = env->GetStaticFieldID(j_cp_name_class, "PRICING",
			    "Lparma_polyhedra_library/Control_Parameter_Name;");
  CHECK_RESULT_ASSERT(env, cp_name_pricing_get_id);
  switch (cp_name) {
  case MIP_Problem::PRICING:
    return env->GetStaticObjectField(j_cp_name_class,
				     cp_name_pricing_get_id);
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
}

MIP_Problem::Control_Parameter_Value
build_cxx_control_parameter_value(JNIEnv* env, jobject j_cp_value) {
  jclass cp_value_class = env->GetObjectClass(j_cp_value);
  CHECK_RESULT_ASSERT(env, cp_value_class);
  jmethodID cp_value_ordinal_id
    = env->GetMethodID(cp_value_class, "ordinal", "()I");
  CHECK_RESULT_ASSERT(env, cp_value_ordinal_id);
  jint cp_value = env->CallIntMethod(j_cp_value, cp_value_ordinal_id);
  CHECK_EXCEPTION_ASSERT(env);
  switch (cp_value) {
  case 0:
    return MIP_Problem::PRICING_STEEPEST_EDGE_FLOAT;
  case 1:
    return MIP_Problem::PRICING_STEEPEST_EDGE_EXACT;
  case 2:
    return MIP_Problem::PRICING_TEXTBOOK;
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
}

jobject
build_java_control_parameter_value
(JNIEnv* env, const MIP_Problem::Control_Parameter_Value& cp_value) {
  jclass j_cp_value_class
    = env->FindClass("parma_polyhedra_library/Control_Parameter_Value");
  CHECK_RESULT_ASSERT(env, j_cp_value_class);
  const char* field_name;
  switch (cp_value) {
  case MIP_Problem::PRICING_STEEPEST_EDGE_FLOAT:
    field_name = "PRICING_STEEPEST_EDGE_FLOAT";
    break;
  case MIP_Problem::PRICING_STEEPEST_EDGE_EXACT:
    field_name = "PRICING_STEEPEST_EDGE_EXACT";
    break;
  case MIP_Problem::PRICING_TEXTBOOK:
    field_name = "PRICING_TEXTBOOK";
    break;
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
  jfieldID fID = env->GetStaticFieldID(j_cp_value_class, field_name,
                                       "Lparma_polyhedra_library/Control_Parameter_Value;");
  CHECK_RESULT_ASSERT(env, fID);
  return env->GetStaticObjectField(j_cp_value_class, fID);
}

Constraint
build_cxx_constraint(JNIEnv* env, jobject j_constraint) {
  jobject lhs_value
    = env->GetObjectField(j_constraint, cached_FMIDs.Constraint_lhs_ID);
  jobject rhs_value
    = env->GetObjectField(j_constraint, cached_FMIDs.Constraint_rhs_ID);
  jobject kind
    = env->GetObjectField(j_constraint, cached_FMIDs.Constraint_kind_ID);
  Linear_Expression first_le = build_cxx_linear_expression(env, lhs_value);
  Linear_Expression second_le = build_cxx_linear_expression(env, rhs_value);
  jint rel_sym
    = env->CallIntMethod(kind, cached_FMIDs.Relation_Symbol_ordinal_ID);
  CHECK_EXCEPTION_ASSERT(env);
  switch (rel_sym) {
  case 0:
    return Constraint(first_le < second_le);
  case 1:
    return Constraint(first_le <= second_le);
  case 2:
    return Constraint(first_le == second_le);
  case 3:
    return Constraint(first_le >= second_le);
  case 4:
    return Constraint(first_le > second_le);
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
}

Linear_Expression
build_cxx_linear_expression(JNIEnv* env, jobject j_le) {
  jclass current_class = env->GetObjectClass(j_le);
  // LE_Variable
  if (env->IsAssignableFrom(current_class,
                            cached_classes.Linear_Expression_Variable)) {
    jint var_id
      = env->CallIntMethod(j_le,
                           cached_FMIDs.Linear_Expression_Variable_var_id_ID);
    return Linear_Expression(Variable(var_id));
  }
  // LE_Coefficient
  if (env->IsAssignableFrom(current_class,
                            cached_classes.Linear_Expression_Coefficient)) {
    jfieldID fID = cached_FMIDs.Linear_Expression_Coefficient_coeff_ID;
    jobject ppl_coeff = env->GetObjectField(j_le, fID);
    return Linear_Expression(build_cxx_coeff(env, ppl_coeff));
  }
  // LE_Sum
  if (env->IsAssignableFrom(current_class,
                            cached_classes.Linear_Expression_Sum)) {
    jobject l_value
      = env->GetObjectField(j_le, cached_FMIDs.Linear_Expression_Sum_lhs_ID);
    jobject r_value
      = env->GetObjectField(j_le, cached_FMIDs.Linear_Expression_Sum_rhs_ID);
    return (build_cxx_linear_expression(env, l_value)
	    + build_cxx_linear_expression(env, r_value));
  }
  // LE_Times
  if (env->IsAssignableFrom(current_class,
                            cached_classes.Linear_Expression_Times)) {
    jobject le_coeff_value
      = env->GetObjectField(j_le,
                            cached_FMIDs.Linear_Expression_Times_lhs_ID);
    jobject ppl_coeff
      = env->GetObjectField(le_coeff_value,
                            cached_FMIDs.Linear_Expression_Coefficient_coeff_ID);
    jobject le_value
      = env->GetObjectField(j_le,
                            cached_FMIDs.Linear_Expression_Times_rhs_ID);
    return (build_cxx_coeff(env, ppl_coeff)
	    * build_cxx_linear_expression(env, le_value));
  }
  // LE_Difference
  if (env->IsAssignableFrom(current_class,
                            cached_classes.Linear_Expression_Difference)) {
    jobject l_value
      = env->GetObjectField(j_le,
                            cached_FMIDs.Linear_Expression_Difference_lhs_ID);
    jobject r_value
      = env->GetObjectField(j_le,
                            cached_FMIDs.Linear_Expression_Difference_rhs_ID);
    return (build_cxx_linear_expression(env, l_value)
	    - build_cxx_linear_expression(env, r_value));
  }
  // LE_Unary_Minus
  if (env->IsAssignableFrom(current_class,
                            cached_classes.Linear_Expression_Unary_Minus)) {
    jobject le_value
      = env->GetObjectField(j_le,
                            cached_FMIDs.Linear_Expression_Unary_Minus_arg_ID);
    return (-build_cxx_linear_expression(env, le_value));
  }
  assert(false);
  throw std::runtime_error("PPL Java interface internal error");
}

Generator
build_cxx_generator(JNIEnv* env, jobject j_generator) {
  jobject j_le
    = env->GetObjectField(j_generator, cached_FMIDs.Generator_le_ID);
  jobject generator_type
    = env->GetObjectField(j_generator, cached_FMIDs.Generator_gt_ID);
  jint generator_type_ordinal
    = env->CallIntMethod(generator_type,
                         cached_FMIDs.Generator_Type_ordinal_ID);
  CHECK_EXCEPTION_ASSERT(env);
  switch (generator_type_ordinal) {
  case 0:
    return line(build_cxx_linear_expression(env, j_le));
  case 1:
    return ray(build_cxx_linear_expression(env, j_le));
  case 2:
    {
      jobject j_div
        = env->GetObjectField(j_generator, cached_FMIDs.Generator_div_ID);
      return point(build_cxx_linear_expression(env, j_le),
                   build_cxx_coeff(env, j_div));
    }
  case 3:
    {
      jobject j_div
        = env->GetObjectField(j_generator, cached_FMIDs.Generator_div_ID);
      return closure_point(build_cxx_linear_expression(env, j_le),
                           build_cxx_coeff(env, j_div));
    }
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
}

Grid_Generator
build_cxx_grid_generator(JNIEnv* env, jobject j_grid_generator) {
  jobject j_le
    = env->GetObjectField(j_grid_generator, cached_FMIDs.Grid_Generator_le_ID);
  jobject grid_generator_type
    = env->GetObjectField(j_grid_generator, cached_FMIDs.Grid_Generator_gt_ID);
  jint grid_generator_type_ordinal
    = env->CallIntMethod(grid_generator_type,
                         cached_FMIDs.Grid_Generator_Type_ordinal_ID);
  CHECK_EXCEPTION_ASSERT(env);
  switch (grid_generator_type_ordinal) {
  case 0:
    return grid_line(build_cxx_linear_expression(env, j_le));
  case 1:
    {
      jobject j_div = env->GetObjectField(j_grid_generator,
                                          cached_FMIDs.Grid_Generator_div_ID);
      return parameter(build_cxx_linear_expression(env, j_le),
                       build_cxx_coeff(env, j_div));
    }
  case 2:
    {
      jobject j_div = env->GetObjectField(j_grid_generator,
                                          cached_FMIDs.Grid_Generator_div_ID);
      return grid_point(build_cxx_linear_expression(env, j_le),
                        build_cxx_coeff(env, j_div));
    }
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
}

jobject
build_java_linear_expression_coefficient(JNIEnv* env, const Coefficient& c) {
  jobject j_coeff = build_java_coeff(env, c);
  jobject ret
    = env->NewObject(cached_classes.Linear_Expression_Coefficient,
                     cached_FMIDs.Linear_Expression_Coefficient_init_ID,
                     j_coeff);
  CHECK_RESULT_THROW(env, ret);
  return ret;
}

void
set_generator(JNIEnv* env, jobject dst, jobject src) {
  jobject src_gt = env->GetObjectField(src, cached_FMIDs.Generator_gt_ID);
  env->SetObjectField(dst, cached_FMIDs.Generator_gt_ID, src_gt);
  jobject src_le = env->GetObjectField(src, cached_FMIDs.Generator_le_ID);
  env->SetObjectField(dst, cached_FMIDs.Generator_le_ID, src_le);
  jobject src_div = env->GetObjectField(src, cached_FMIDs.Generator_div_ID);
  env->SetObjectField(dst, cached_FMIDs.Generator_div_ID, src_div);
}

void
set_pair_element(JNIEnv* env, jobject dst_pair, int arg, jobject src) {
  switch (arg) {
  case 0:
    env->SetObjectField(dst_pair, cached_FMIDs.Pair_first_ID, src);
    break;
  case 1:
    env->SetObjectField(dst_pair, cached_FMIDs.Pair_second_ID, src);
    break;
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error: "
                             "pair value not allowed");
  }
}

jobject
get_pair_element(JNIEnv* env, int arg, jobject j_pair) {
  switch (arg) {
  case 0:
    return env->GetObjectField(j_pair, cached_FMIDs.Pair_first_ID);
  case 1:
    return env->GetObjectField(j_pair, cached_FMIDs.Pair_second_ID);
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error: "
                             "pair value not allowed");
  }
}

jobject
build_java_constraint(JNIEnv* env, const Constraint& c) {
  jobject lhs = build_linear_expression(env, c);
  jobject rhs
    = build_java_linear_expression_coefficient(env, -c.inhomogeneous_term());
  jfieldID fID;
  switch (c.type()) {
  case Constraint::EQUALITY:
    fID = cached_FMIDs.Relation_Symbol_EQUAL_ID;
    break;
  case Constraint::NONSTRICT_INEQUALITY:
    fID = cached_FMIDs.Relation_Symbol_GREATER_OR_EQUAL_ID;
    break;
  case Constraint::STRICT_INEQUALITY:
    fID = cached_FMIDs.Relation_Symbol_GREATER_THAN_ID;
    break;
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
  jobject relation
    = env->GetStaticObjectField(cached_classes.Relation_Symbol, fID);
  jobject ret = env->NewObject(cached_classes.Constraint,
                               cached_FMIDs.Constraint_init_ID,
			       lhs, relation, rhs);
  CHECK_RESULT_THROW(env, ret);
  return ret;
}

jobject
build_java_congruence(JNIEnv* env, const Congruence& cg) {
  jobject j_modulus = build_java_coeff(env, cg.modulus());
  jobject j_lhs = build_linear_expression(env, cg);
  jobject j_rhs
    = build_java_linear_expression_coefficient(env, -cg.inhomogeneous_term());
  jobject ret = env->NewObject(cached_classes.Congruence,
                               cached_FMIDs.Congruence_init_ID,
			       j_lhs, j_rhs, j_modulus);
  CHECK_RESULT_THROW(env, ret);
  return ret;
}

jobject
build_java_generator(JNIEnv* env, const Generator& g) {
  jobject j_g_le = build_linear_expression(env, g);
  jobject ret;
  switch (g.type()) {
  case Generator::LINE:
    ret = env->CallStaticObjectMethod(cached_classes.Generator,
				      cached_FMIDs.Generator_line_ID,
                                      j_g_le);
    break;
  case Generator::RAY:
    ret = env->CallStaticObjectMethod(cached_classes.Generator,
				      cached_FMIDs.Generator_ray_ID,
                                      j_g_le);
    break;
  case Generator::POINT:
    {
      const Coefficient& divisor = g.divisor();
      jobject j_div = build_java_coeff(env, divisor);
      ret = env->CallStaticObjectMethod(cached_classes.Generator,
                                        cached_FMIDs.Generator_point_ID,
                                        j_g_le, j_div);
      break;
    }
  case Generator::CLOSURE_POINT:
    {
      const Coefficient& divisor = g.divisor();
      jobject j_div = build_java_coeff(env, divisor);
      ret = env->CallStaticObjectMethod(cached_classes.Generator,
                                        cached_FMIDs.Generator_closure_point_ID,
                                        j_g_le, j_div);
      break;
    }
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
  CHECK_EXCEPTION_THROW(env);
  return ret;
}

jobject
build_java_grid_generator(JNIEnv* env, const Grid_Generator& g) {
  jobject j_g_le = build_linear_expression(env, g);
  jobject ret;
  switch (g.type()) {
  case Grid_Generator::LINE:
    ret = env->CallStaticObjectMethod(cached_classes.Grid_Generator,
				      cached_FMIDs.Grid_Generator_grid_line_ID,
                                      j_g_le);
    break;
  case Grid_Generator::PARAMETER:
    {
      const Coefficient& divisor = g.divisor();
      jobject j_div = build_java_coeff(env, divisor);
      ret = env->CallStaticObjectMethod(cached_classes.Grid_Generator,
                                        cached_FMIDs.Grid_Generator_parameter_ID,
                                        j_g_le, j_div);
      break;
    }
  case Grid_Generator::POINT:
    {
      const Coefficient& divisor = g.divisor();
      jobject j_div = build_java_coeff(env, divisor);
      ret = env->CallStaticObjectMethod(cached_classes.Grid_Generator,
                                        cached_FMIDs.Grid_Generator_grid_point_ID,
                                        j_g_le, j_div);
      break;
    }
  default:
    assert(false);
    throw std::runtime_error("PPL Java interface internal error");
  }
  CHECK_EXCEPTION_THROW(env);
  return ret;
}

jobject
build_java_constraint_system(JNIEnv* env, const Constraint_System& cs) {
  jobject j_cs = env->NewObject(cached_classes.Constraint_System,
                                cached_FMIDs.Constraint_System_init_ID);
  CHECK_RESULT_THROW(env, j_cs);
  for (Constraint_System::const_iterator v_begin = cs.begin(),
 	 v_end = cs.end(); v_begin != v_end; ++v_begin) {
    jobject j_constraint = build_java_constraint(env, *v_begin);
    env->CallBooleanMethod(j_cs,
                           cached_FMIDs.Constraint_System_add_ID,
                           j_constraint);
    CHECK_EXCEPTION_THROW(env);
  }
  return j_cs;
}

jobject
build_java_generator_system(JNIEnv* env, const Generator_System& gs) {
  jobject j_gs = env->NewObject(cached_classes.Generator_System,
                                cached_FMIDs.Generator_System_init_ID);
  CHECK_RESULT_THROW(env, j_gs);
  for (Generator_System::const_iterator v_begin = gs.begin(),
 	 v_end = gs.end(); v_begin != v_end; ++v_begin) {
    jobject j_generator = build_java_generator(env, *v_begin);
    env->CallBooleanMethod(j_gs,
                           cached_FMIDs.Generator_System_add_ID,
                           j_generator);
    CHECK_EXCEPTION_THROW(env);
  }
  return j_gs;
}

jobject
build_java_grid_generator_system(JNIEnv* env,
				 const Grid_Generator_System& gs) {
  jobject j_gs = env->NewObject(cached_classes.Grid_Generator_System,
                                cached_FMIDs.Grid_Generator_System_init_ID);
  CHECK_RESULT_THROW(env, j_gs);
  for (Grid_Generator_System::const_iterator v_begin = gs.begin(),
 	 v_end = gs.end(); v_begin != v_end; ++v_begin) {
    jobject j_generator = build_java_grid_generator(env, *v_begin);
    env->CallBooleanMethod(j_gs,
                           cached_FMIDs.Grid_Generator_System_add_ID,
                           j_generator);
    CHECK_EXCEPTION_THROW(env);
  }
  return j_gs;
}

jobject
build_java_congruence_system(JNIEnv* env, const Congruence_System& cgs) {
  jobject j_cgs = env->NewObject(cached_classes.Congruence_System,
                                 cached_FMIDs.Congruence_System_init_ID);
  CHECK_RESULT_THROW(env, j_cgs);
  for (Congruence_System::const_iterator v_begin = cgs.begin(),
  	 v_end = cgs.end(); v_begin != v_end; ++v_begin) {
    jobject j_congruence = build_java_congruence(env,*v_begin);
    env->CallBooleanMethod(j_cgs,
                           cached_FMIDs.Congruence_System_add_ID,
                           j_congruence);
    CHECK_EXCEPTION_THROW(env);
  }
  return j_cgs;
}

} // namespace Java

} // namespace Interfaces

} // namespace Parma_Polyhedra_Library
