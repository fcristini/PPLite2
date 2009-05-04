/* PPL Java interface: domain-independent functions.
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
#include "parma_polyhedra_library_By_Reference.h"
#include "parma_polyhedra_library_Coefficient.h"
#include "parma_polyhedra_library_Complexity_Class.h"
#include "parma_polyhedra_library_Congruence.h"
#include "parma_polyhedra_library_Congruence_System.h"
#include "parma_polyhedra_library_Constraint.h"
#include "parma_polyhedra_library_Constraint_System.h"
#include "parma_polyhedra_library_Degenerate_Element.h"
#include "parma_polyhedra_library_Generator.h"
#include "parma_polyhedra_library_Generator_System.h"
#include "parma_polyhedra_library_Generator_Type.h"
#include "parma_polyhedra_library_Grid_Generator.h"
#include "parma_polyhedra_library_Grid_Generator_System.h"
#include "parma_polyhedra_library_Grid_Generator_Type.h"
#include "parma_polyhedra_library_IO.h"
#include "parma_polyhedra_library_Linear_Expression.h"
#include "parma_polyhedra_library_Linear_Expression_Coefficient.h"
#include "parma_polyhedra_library_Linear_Expression_Difference.h"
#include "parma_polyhedra_library_Linear_Expression_Sum.h"
#include "parma_polyhedra_library_Linear_Expression_Times.h"
#include "parma_polyhedra_library_Linear_Expression_Unary_Minus.h"
#include "parma_polyhedra_library_Linear_Expression_Variable.h"
#include "parma_polyhedra_library_MIP_Problem.h"
#include "parma_polyhedra_library_MIP_Problem_Status.h"
#include "parma_polyhedra_library_Optimization_Mode.h"
#include "parma_polyhedra_library_Pair.h"
#include "parma_polyhedra_library_Parma_Polyhedra_Library.h"
#include "parma_polyhedra_library_Poly_Con_Relation.h"
#include "parma_polyhedra_library_Poly_Gen_Relation.h"
#include "parma_polyhedra_library_PPL_Object.h"
#include "parma_polyhedra_library_Relation_Symbol.h"
#include "parma_polyhedra_library_Variable.h"
#include "parma_polyhedra_library_Variables_Set.h"

using namespace Parma_Polyhedra_Library;
using namespace Parma_Polyhedra_Library::Interfaces::Java;

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Parma_1Polyhedra_1Library_initialize_1library
(JNIEnv* env, jclass /* ppl_class */) {
  initialize();
  cached_classes.init_cache(env);
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Parma_1Polyhedra_1Library_finalize_1library
(JNIEnv* env, jclass /* ppl_class */) {
  cached_classes.clear_cache(env);
  finalize();
}


JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_By_1Reference_initIDs
(JNIEnv* env, jclass j_by_ref_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_by_ref_class, "obj", "Ljava/lang/Object;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.By_Reference_obj_ID = fID;
  jmethodID mID;
  mID = env->GetMethodID(j_by_ref_class, "<init>", "(Ljava/lang/Object;)V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.By_Reference_init_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Coefficient_initIDs
(JNIEnv* env, jclass j_coeff_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_coeff_class, "value", "Ljava/math/BigInteger;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Coefficient_value_ID = fID;
  jmethodID mID;
  mID = env->GetMethodID(j_coeff_class, "<init>", "(Ljava/lang/String;)V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Coefficient_init_from_String_ID = mID;
  mID = env->GetMethodID(j_coeff_class, "toString", "()Ljava/lang/String;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Coefficient_toString_ID = mID;
  // Boolean.
  mID = env->GetStaticMethodID(cached_classes.Boolean, "valueOf",
                               "(Z)Ljava/lang/Boolean;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Boolean_valueOf_ID = mID;
  // Integer.
  mID = env->GetStaticMethodID(cached_classes.Integer, "valueOf",
                               "(I)Ljava/lang/Integer;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Integer_valueOf_ID = mID;
  mID = env->GetMethodID(cached_classes.Integer, "intValue", "()I");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Integer_intValue_ID = mID;
  // Long.
  mID = env->GetStaticMethodID(cached_classes.Long, "valueOf",
                               "(J)Ljava/lang/Long;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Long_valueOf_ID = mID;
  mID = env->GetMethodID(cached_classes.Long, "longValue", "()J");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Long_longValue_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Complexity_1Class_initIDs
(JNIEnv* env, jclass j_complexity_class) {
  jmethodID mID = env->GetMethodID(j_complexity_class, "ordinal", "()I");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Complexity_Class_ordinal_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Congruence_initIDs
(JNIEnv* env, jclass j_congruence_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_congruence_class, "modulus",
                        "Lparma_polyhedra_library/Coefficient;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Congruence_modulus_ID = fID;
  fID = env->GetFieldID(j_congruence_class, "lhs",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Congruence_lhs_ID = fID;
  fID = env->GetFieldID(j_congruence_class, "rhs",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Congruence_rhs_ID = fID;
  jmethodID mID;
  mID = env->GetMethodID(j_congruence_class, "<init>",
                         "(Lparma_polyhedra_library/Linear_Expression;"
                         "Lparma_polyhedra_library/Linear_Expression;"
                         "Lparma_polyhedra_library/Coefficient;)V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Congruence_init_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Congruence_1System_initIDs
(JNIEnv* env, jclass j_con_sys_class) {
  jmethodID mID;
  mID = env->GetMethodID(j_con_sys_class, "<init>", "()V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Congruence_System_init_ID = mID;
  mID = env->GetMethodID(j_con_sys_class, "add", "(Ljava/lang/Object;)Z");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Congruence_System_add_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Constraint_initIDs
(JNIEnv* env, jclass j_constraint_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_constraint_class, "lhs",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Constraint_lhs_ID = fID;
  fID = env->GetFieldID(j_constraint_class, "rhs",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Constraint_rhs_ID = fID;
  fID = env->GetFieldID(j_constraint_class, "kind",
                        "Lparma_polyhedra_library/Relation_Symbol;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Constraint_kind_ID = fID;
  jmethodID mID;
  mID = env->GetMethodID(j_constraint_class, "<init>",
                         "(Lparma_polyhedra_library/Linear_Expression;"
                         "Lparma_polyhedra_library/Relation_Symbol;"
                         "Lparma_polyhedra_library/Linear_Expression;)V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Constraint_init_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Constraint_1System_initIDs
(JNIEnv* env, jclass j_con_sys_class) {
  jmethodID mID;
  mID = env->GetMethodID(j_con_sys_class, "<init>", "()V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Constraint_System_init_ID = mID;
  mID = env->GetMethodID(j_con_sys_class, "add", "(Ljava/lang/Object;)Z");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Constraint_System_add_ID = mID;
  // NOTE: initialize the iterator method IDs common to all *_System classes.
  mID = env->GetMethodID(j_con_sys_class, "iterator",
                         "()Ljava/util/Iterator;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.System_iterator_ID = mID;
  mID = env->GetMethodID(cached_classes.Iterator, "hasNext", "()Z");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.System_Iterator_has_next_ID = mID;
  assert(cached_classes.Iterator != NULL);
  mID = env->GetMethodID(cached_classes.Iterator, "next",
                         "()Ljava/lang/Object;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.System_Iterator_next_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Degenerate_1Element_initIDs
(JNIEnv* env, jclass j_degenerate_class) {
  jmethodID mID = env->GetMethodID(j_degenerate_class, "ordinal", "()I");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Degenerate_Element_ordinal_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Generator_initIDs
(JNIEnv* env, jclass j_generator_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_generator_class, "gt",
                        "Lparma_polyhedra_library/Generator_Type;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Generator_gt_ID = fID;
  fID = env->GetFieldID(j_generator_class, "le",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Generator_le_ID = fID;
  fID = env->GetFieldID(j_generator_class, "div",
                        "Lparma_polyhedra_library/Coefficient;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Generator_div_ID = fID;
  jmethodID mID;
  mID = env->GetStaticMethodID(j_generator_class, "line",
                               "(Lparma_polyhedra_library/Linear_Expression;)"
                               "Lparma_polyhedra_library/Generator;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Generator_line_ID = mID;
  mID = env->GetStaticMethodID(j_generator_class, "ray",
                               "(Lparma_polyhedra_library/Linear_Expression;)"
                               "Lparma_polyhedra_library/Generator;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Generator_ray_ID = mID;
  mID = env->GetStaticMethodID(j_generator_class, "point",
                               "(Lparma_polyhedra_library/Linear_Expression;"
                               "Lparma_polyhedra_library/Coefficient;)"
                               "Lparma_polyhedra_library/Generator;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Generator_point_ID = mID;
  mID = env->GetStaticMethodID(j_generator_class, "closure_point",
                               "(Lparma_polyhedra_library/Linear_Expression;"
                               "Lparma_polyhedra_library/Coefficient;)"
                               "Lparma_polyhedra_library/Generator;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Generator_closure_point_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Generator_1System_initIDs
(JNIEnv* env, jclass j_gen_sys_class) {
  jmethodID mID;
  mID = env->GetMethodID(j_gen_sys_class, "<init>", "()V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Generator_System_init_ID = mID;
  mID = env->GetMethodID(j_gen_sys_class, "add", "(Ljava/lang/Object;)Z");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Generator_System_add_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Generator_1Type_initIDs
(JNIEnv* env, jclass j_gen_type_class) {
  jmethodID mID;
  mID = env->GetMethodID(j_gen_type_class, "ordinal", "()I");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Generator_Type_ordinal_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Grid_1Generator_initIDs
(JNIEnv* env, jclass j_grid_generator_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_grid_generator_class, "gt",
                        "Lparma_polyhedra_library/Grid_Generator_Type;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Grid_Generator_gt_ID = fID;
  fID = env->GetFieldID(j_grid_generator_class, "le",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Grid_Generator_le_ID = fID;
  fID = env->GetFieldID(j_grid_generator_class, "div",
                        "Lparma_polyhedra_library/Coefficient;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Grid_Generator_div_ID = fID;
  jmethodID mID;
  mID = env->GetStaticMethodID(j_grid_generator_class, "grid_line",
                               "(Lparma_polyhedra_library/Linear_Expression;)"
                               "Lparma_polyhedra_library/Grid_Generator;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Grid_Generator_grid_line_ID = mID;
  mID = env->GetStaticMethodID(j_grid_generator_class, "parameter",
                               "(Lparma_polyhedra_library/Linear_Expression;"
                               "Lparma_polyhedra_library/Coefficient;)"
                               "Lparma_polyhedra_library/Grid_Generator;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Grid_Generator_parameter_ID = mID;
  mID = env->GetStaticMethodID(j_grid_generator_class, "grid_point",
                               "(Lparma_polyhedra_library/Linear_Expression;"
                               "Lparma_polyhedra_library/Coefficient;)"
                               "Lparma_polyhedra_library/Grid_Generator;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Grid_Generator_grid_point_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Grid_1Generator_1System_initIDs
(JNIEnv* env, jclass j_gen_sys_class) {
  jmethodID mID;
  mID = env->GetMethodID(j_gen_sys_class, "<init>", "()V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Grid_Generator_System_init_ID = mID;
  mID = env->GetMethodID(j_gen_sys_class, "add", "(Ljava/lang/Object;)Z");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Grid_Generator_System_add_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Grid_1Generator_1Type_initIDs
(JNIEnv* env, jclass j_grid_gen_type_class) {
  jmethodID mID;
  mID = env->GetMethodID(j_grid_gen_type_class, "ordinal", "()I");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Grid_Generator_Type_ordinal_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Linear_1Expression_initIDs
(JNIEnv* env, jclass j_le_class) {
  jmethodID mID;
  mID = env->GetMethodID(j_le_class, "sum",
                         "(Lparma_polyhedra_library/Linear_Expression;)"
                         "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Linear_Expression_sum_ID = mID;
  mID = env->GetMethodID(j_le_class, "times",
                         "(Lparma_polyhedra_library/Coefficient;)"
                         "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Linear_Expression_times_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Linear_1Expression_1Coefficient_initIDs
(JNIEnv* env, jclass j_le_coeff_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_le_coeff_class, "coeff",
                        "Lparma_polyhedra_library/Coefficient;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Linear_Expression_Coefficient_coeff_ID = fID;
  jmethodID mID;
  mID = env->GetMethodID(j_le_coeff_class, "<init>",
			 "(Lparma_polyhedra_library/Coefficient;)V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Linear_Expression_Coefficient_init_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Linear_1Expression_1Difference_initIDs
(JNIEnv* env, jclass j_le_diff_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_le_diff_class, "lhs",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Linear_Expression_Difference_lhs_ID = fID;
  fID = env->GetFieldID(j_le_diff_class, "rhs",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Linear_Expression_Difference_rhs_ID = fID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Linear_1Expression_1Sum_initIDs
(JNIEnv* env, jclass j_le_sum_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_le_sum_class, "lhs",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Linear_Expression_Sum_lhs_ID = fID;
  fID = env->GetFieldID(j_le_sum_class, "rhs",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Linear_Expression_Sum_rhs_ID = fID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Linear_1Expression_1Times_initIDs
(JNIEnv* env, jclass j_le_times_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_le_times_class, "lhs",
                        "Lparma_polyhedra_library/Linear_Expression_Coefficient;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Linear_Expression_Times_lhs_ID = fID;
  fID = env->GetFieldID(j_le_times_class, "rhs",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Linear_Expression_Times_rhs_ID = fID;
  jmethodID mID;
  mID = env->GetMethodID(j_le_times_class, "<init>",
                         "(Lparma_polyhedra_library/Coefficient;"
                         "Lparma_polyhedra_library/Variable;)V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Linear_Expression_Times_init_from_coeff_var_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Linear_1Expression_1Unary_1Minus_initIDs
(JNIEnv* env, jclass j_le_uminus_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_le_uminus_class, "arg",
                        "Lparma_polyhedra_library/Linear_Expression;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Linear_Expression_Unary_Minus_arg_ID = fID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Linear_1Expression_1Variable_initIDs
(JNIEnv* env, jclass j_le_var_class) {
  jmethodID mID;
  mID = env->GetMethodID(j_le_var_class, "<init>",
			 "(Lparma_polyhedra_library/Variable;)V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Linear_Expression_Variable_init_ID = mID;
  mID = env->GetMethodID(j_le_var_class, "var_id", "()I");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Linear_Expression_Variable_var_id_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_1Status_initIDs
(JNIEnv* env, jclass j_mip_status_class) {
  jfieldID fID;
  fID = env->GetStaticFieldID(j_mip_status_class, "UNFEASIBLE_MIP_PROBLEM",
                              "Lparma_polyhedra_library/MIP_Problem_Status;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.MIP_Problem_Status_UNFEASIBLE_MIP_PROBLEM_ID = fID;
  fID = env->GetStaticFieldID(j_mip_status_class, "UNBOUNDED_MIP_PROBLEM",
                              "Lparma_polyhedra_library/MIP_Problem_Status;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.MIP_Problem_Status_UNBOUNDED_MIP_PROBLEM_ID = fID;
  fID = env->GetStaticFieldID(j_mip_status_class, "OPTIMIZED_MIP_PROBLEM",
                              "Lparma_polyhedra_library/MIP_Problem_Status;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.MIP_Problem_Status_OPTIMIZED_MIP_PROBLEM_ID = fID;
  jmethodID mID;
  mID = env->GetMethodID(j_mip_status_class, "ordinal", "()I");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.MIP_Problem_Status_ordinal_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Optimization_1Mode_initIDs
(JNIEnv* env, jclass j_opt_mode_class) {
  jfieldID fID;
  fID = env->GetStaticFieldID(j_opt_mode_class, "MAXIMIZATION",
                              "Lparma_polyhedra_library/Optimization_Mode;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Optimization_Mode_MAXIMIZATION_ID = fID;
  fID = env->GetStaticFieldID(j_opt_mode_class, "MINIMIZATION",
                              "Lparma_polyhedra_library/Optimization_Mode;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Optimization_Mode_MINIMIZATION_ID = fID;
  jmethodID mID;
  mID = env->GetMethodID(j_opt_mode_class, "ordinal", "()I");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Optimization_Mode_ordinal_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Pair_initIDs
(JNIEnv* env, jclass j_pair_class) {
  jfieldID fID;
  fID = env->GetFieldID(j_pair_class, "first", "Ljava/lang/Object;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Pair_first_ID = fID;
  fID = env->GetFieldID(j_pair_class, "second", "Ljava/lang/Object;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Pair_second_ID = fID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Poly_1Con_1Relation_initIDs
(JNIEnv* env, jclass j_poly_con_relation_class) {
  jmethodID mID;
  mID = env->GetMethodID(j_poly_con_relation_class, "<init>", "(I)V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Poly_Con_Relation_init_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Poly_1Gen_1Relation_initIDs
(JNIEnv* env, jclass j_poly_gen_relation_class) {
  jmethodID mID;
  mID = env->GetMethodID(j_poly_gen_relation_class, "<init>", "(I)V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Poly_Gen_Relation_init_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_PPL_1Object_initIDs
(JNIEnv* env, jclass j_ppl_object_class) {
  jfieldID fID = env->GetFieldID(j_ppl_object_class, "ptr", "J");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.PPL_Object_ptr_ID = fID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Relation_1Symbol_initIDs
(JNIEnv* env, jclass j_rel_sym_class) {
  jfieldID fID;
  fID = env->GetStaticFieldID(j_rel_sym_class, "EQUAL",
                              "Lparma_polyhedra_library/Relation_Symbol;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Relation_Symbol_EQUAL_ID = fID;
  fID = env->GetStaticFieldID(j_rel_sym_class, "GREATER_THAN",
                              "Lparma_polyhedra_library/Relation_Symbol;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Relation_Symbol_GREATER_THAN_ID = fID;
  fID = env->GetStaticFieldID(j_rel_sym_class, "GREATER_OR_EQUAL",
                              "Lparma_polyhedra_library/Relation_Symbol;");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Relation_Symbol_GREATER_OR_EQUAL_ID = fID;
  jmethodID mID;
  mID = env->GetMethodID(j_rel_sym_class, "ordinal", "()I");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Relation_Symbol_ordinal_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Variable_initIDs
(JNIEnv* env, jclass j_variable_class) {
  jfieldID fID = env->GetFieldID(j_variable_class, "varid", "I");
  CHECK_RESULT_ASSERT(env, fID);
  cached_FMIDs.Variable_varid_ID = fID;
  jmethodID mID = env->GetMethodID(j_variable_class, "<init>", "(I)V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Variable_init_ID = mID;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Variables_1Set_initIDs
(JNIEnv* env, jclass j_vset_class) {
  jmethodID mID;
  mID = env->GetMethodID(j_vset_class, "<init>", "()V");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Variables_Set_init_ID = mID;
  mID = env->GetMethodID(j_vset_class, "add", "(Ljava/lang/Object;)Z");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Variables_Set_add_ID = mID;
  mID = env->GetMethodID(j_vset_class, "iterator", "()Ljava/util/Iterator;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Variables_Set_iterator_ID = mID;
  // Iterator on Variables_Set.
  jclass j_vset_iter_class = env->FindClass("java/util/Iterator");
  CHECK_RESULT_ASSERT(env, j_vset_iter_class);
  mID = env->GetMethodID(j_vset_iter_class, "hasNext", "()Z");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Variables_Set_Iterator_has_next_ID = mID;
  mID = env->GetMethodID(j_vset_iter_class, "next", "()Ljava/lang/Object;");
  CHECK_RESULT_ASSERT(env, mID);
  cached_FMIDs.Variables_Set_Iterator_next_ID = mID;
}


JNIEXPORT jint JNICALL
Java_parma_1polyhedra_1library_Parma_1Polyhedra_1Library_version_1major
(JNIEnv *, jclass) {
  return version_major();
}

JNIEXPORT jint JNICALL
Java_parma_1polyhedra_1library_Parma_1Polyhedra_1Library_version_1minor
(JNIEnv *, jclass)  {
  return version_minor();
}

JNIEXPORT jint JNICALL
Java_parma_1polyhedra_1library_Parma_1Polyhedra_1Library_version_1revision
(JNIEnv *, jclass) {
  return version_revision();
}

JNIEXPORT jint JNICALL
Java_parma_1polyhedra_1library_Parma_1Polyhedra_1Library_version_1beta
(JNIEnv *, jclass) {
  return version_beta();
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Parma_1Polyhedra_1Library_version
(JNIEnv* env, jclass) {
  return env->NewStringUTF(version());
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Parma_1Polyhedra_1Library_banner
(JNIEnv* env, jclass) {
  return env->NewStringUTF(banner());
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Parma_1Polyhedra_1Library_set_1rounding_1for_1PPL
(JNIEnv* env, jclass) {
  try {
    set_rounding_for_PPL();
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_Parma_1Polyhedra_1Library_restore_1pre_1PPL_1rounding
(JNIEnv* env, jclass) {
  try {
    restore_pre_PPL_rounding();
  }
  CATCH_ALL;
}

JNIEXPORT jlong JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_max_1space_1dimension
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    return mip->max_space_dimension();
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jlong JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_space_1dimension
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    return mip->space_dimension();
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jobject JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_integer_1space_1dimensions
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    return build_java_variables_set(env, mip->integer_space_dimensions());
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT jobject JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_objective_1function
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    PPL_DIRTY_TEMP_COEFFICIENT(inhomogeneous_term);
    inhomogeneous_term = mip->objective_function().inhomogeneous_term();
    jobject j_coeff_inhomogeneous_term
      = build_java_coeff(env, inhomogeneous_term);
    jobject j_le_coeff
      = env->NewObject(cached_classes.Linear_Expression_Coefficient,
                       cached_FMIDs.Linear_Expression_Coefficient_init_ID,
                       j_coeff_inhomogeneous_term);
    CHECK_RESULT_RETURN(env, j_le_coeff, 0);

    jobject j_le = build_linear_expression(env, mip->objective_function());
    return env->CallObjectMethod(j_le,
                                 cached_FMIDs.Linear_Expression_sum_ID,
                                 j_le_coeff);
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT jobject JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_optimization_1mode
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    return build_java_optimization_mode(env, mip->optimization_mode());
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT jobject JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_get_1control_1parameter
(JNIEnv* env , jobject j_this_mip_problem,
 jobject j_cpn) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    MIP_Problem::Control_Parameter_Name cpn
      = build_cxx_control_parameter_name(env, j_cpn);
    return
      build_java_control_parameter_value(env,
                                         mip->get_control_parameter(cpn));
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_set_1control_1parameter
(JNIEnv* env , jobject j_this_mip_problem,
 jobject j_cpv) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    MIP_Problem::Control_Parameter_Value cpv
      = build_cxx_control_parameter_value(env, j_cpv);
    mip->set_control_parameter(cpv);
  }
  CATCH_ALL;
}

JNIEXPORT jobject JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_constraints
(JNIEnv* env, jobject j_this_mip_problem) {
  try {
    jobject j_cs = env->NewObject(cached_classes.Constraint_System,
                                  cached_FMIDs.Constraint_System_init_ID);
    CHECK_RESULT_RETURN(env, j_cs, 0);

    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    for (MIP_Problem::const_iterator cs_it = mip->constraints_begin(),
	   cs_end = mip->constraints_end(); cs_it != cs_end; ++cs_it) {
      jobject j_constraint = build_java_constraint(env, *cs_it);
      env->CallBooleanMethod(j_cs,
                             cached_FMIDs.Constraint_System_add_ID,
                             j_constraint);
      CHECK_EXCEPTION_RETURN(env, 0);
    }
    return j_cs;
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_clear
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    mip->clear();
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_add_1space_1dimensions_1and_1embed
(JNIEnv* env , jobject j_this_mip_problem, jlong j_dim) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    dimension_type ppl_dim = jtype_to_unsigned<dimension_type>(j_dim);
    mip->add_space_dimensions_and_embed(ppl_dim);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_add_1to_1integer_1space_1dimensions
(JNIEnv* env , jobject j_this_mip_problem, jobject j_vset) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    Variables_Set v_set = build_cxx_variables_set(env, j_vset);
    mip->add_to_integer_space_dimensions(v_set);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_add_1constraint
(JNIEnv* env , jobject j_this_mip_problem, jobject j_c) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    Constraint c = build_cxx_constraint(env, j_c);
    mip->add_constraint(c);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_add_1constraints
(JNIEnv* env , jobject j_this_mip_problem, jobject j_cs) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    Constraint_System cs = build_cxx_constraint_system(env, j_cs);
    mip->add_constraints(cs);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_set_1objective_1function
(JNIEnv* env , jobject j_this_mip_problem, jobject j_le) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    Linear_Expression le = build_cxx_linear_expression(env, j_le);
    mip->set_objective_function(le);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_set_1optimization_1mode
(JNIEnv* env , jobject j_this_mip_problem, jobject j_opt_mode) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    Optimization_Mode opt_mode = build_cxx_optimization_mode(env, j_opt_mode);
    mip->set_optimization_mode(opt_mode);
  }
  CATCH_ALL;
}

JNIEXPORT jboolean JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_is_1satisfiable
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    return mip->is_satisfiable();
  }
  CATCH_ALL;
  return false;
}

JNIEXPORT jobject JNICALL Java_parma_1polyhedra_1library_MIP_1Problem_solve
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    return build_java_mip_status(env, mip->solve());
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_evaluate_1objective_1function
(JNIEnv* env, jobject j_this_mip_problem, jobject j_gen,
 jobject j_coeff_num, jobject j_coeff_den) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    Generator g = build_cxx_generator(env, j_gen);
    PPL_DIRTY_TEMP_COEFFICIENT(num);
    PPL_DIRTY_TEMP_COEFFICIENT(den);
    mip->evaluate_objective_function(g, num, den);
    set_coefficient(env, j_coeff_num, build_java_coeff(env, num));
    set_coefficient(env, j_coeff_den, build_java_coeff(env, den));
  }
  CATCH_ALL;
}

JNIEXPORT jobject JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_feasible_1point
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    Generator g = mip->feasible_point();
    return build_java_generator(env, g);
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT jobject JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_optimizing_1point
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    Generator g = mip->optimizing_point();
    return build_java_generator(env, g);
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_optimal_1value
(JNIEnv* env, jobject j_this_mip_problem,
 jobject j_coeff_num, jobject j_coeff_den) {
  try {
    PPL_DIRTY_TEMP_COEFFICIENT(coeff_num);
    PPL_DIRTY_TEMP_COEFFICIENT(coeff_den);
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    mip->optimal_value(coeff_num, coeff_den);
    set_coefficient(env, j_coeff_num, build_java_coeff(env, coeff_num));
    set_coefficient(env, j_coeff_den, build_java_coeff(env, coeff_den));
  }
  CATCH_ALL;
}

JNIEXPORT jboolean JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_OK
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    return mip->OK();
  }
  CATCH_ALL;
  return false;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_build_1cpp_1object__J
(JNIEnv* env, jobject j_this_mip_problem, jlong j_dim) {
  try {
    dimension_type ppl_dim = jtype_to_unsigned<dimension_type>(j_dim);
    MIP_Problem* mip_ptr = new MIP_Problem(ppl_dim);
    set_ptr(env, j_this_mip_problem,  mip_ptr);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_build_1cpp_1object__JLparma_1polyhedra_1library_Constraint_1System_2Lparma_1polyhedra_1library_Linear_1Expression_2Lparma_1polyhedra_1library_Optimization_1Mode_2
(JNIEnv* env , jobject j_this_mip_problem, jlong j_dim, jobject j_cs,
 jobject j_le, jobject j_opt_mode) {
  try {
    dimension_type ppl_dim = jtype_to_unsigned<dimension_type>(j_dim);
    Constraint_System cs = build_cxx_constraint_system(env, j_cs);
    Linear_Expression le = build_cxx_linear_expression(env, j_le);
    Optimization_Mode opt_mode =  build_cxx_optimization_mode(env, j_opt_mode);
    MIP_Problem* mip_ptr = new MIP_Problem(ppl_dim, cs, le, opt_mode);
    set_ptr(env, j_this_mip_problem, mip_ptr);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_build_1cpp_1object__Lparma_1polyhedra_1library_MIP_1Problem_2
(JNIEnv* env, jobject  j_this, jobject j_y)
{
  MIP_Problem* y_ptr = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_y));
  MIP_Problem* this_ptr = new MIP_Problem(*y_ptr);
  set_ptr(env, j_this, this_ptr);
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_free
(JNIEnv* env, jobject j_this) {
  MIP_Problem* mip  = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this));
  if (!is_java_marked(env, j_this)) {
    delete mip;
    void* null_ptr = 0;
    set_ptr(env, j_this, null_ptr);
  }
}

JNIEXPORT void JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_finalize
(JNIEnv* env, jobject j_this) {
  MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this));
  if (!is_java_marked(env, j_this))
    delete mip;
}

JNIEXPORT jlong JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_total_1memory_1in_1bytes
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    MIP_Problem* mip
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this_mip_problem));
    return mip->total_memory_in_bytes();
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_toString
(JNIEnv* env, jobject j_this) {
  MIP_Problem* this_ptr
    = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this));
  using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  s << *this_ptr;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_MIP_1Problem_ascii_1dump
(JNIEnv* env, jobject j_this) {
  try {
    MIP_Problem* this_ptr
      = reinterpret_cast<MIP_Problem*>(get_ptr(env, j_this));
    std::ostringstream s;
    this_ptr->ascii_dump(s);
    return env->NewStringUTF(s.str().c_str());
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Linear_1Expression_toString
(JNIEnv* env, jobject j_this) {
  using namespace Parma_Polyhedra_Library::IO_Operators;
  Linear_Expression ppl_le = build_cxx_linear_expression(env, j_this);
  std::ostringstream s;
  s << ppl_le;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Linear_1Expression_ascii_1dump
(JNIEnv* env, jobject j_this) {
  try {
    std::ostringstream s;
    Linear_Expression le = build_cxx_linear_expression(env, j_this);
    le.ascii_dump(s);
    return env->NewStringUTF(s.str().c_str());
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Generator_toString
(JNIEnv* env, jobject g) {
  using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Generator ppl_g = build_cxx_generator(env, g);
  s << ppl_g;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Generator_ascii_1dump
(JNIEnv* env, jobject j_this) {
  try {
    std::ostringstream s;
    Generator g = build_cxx_generator(env, j_this);
    g.ascii_dump(s);
    return env->NewStringUTF(s.str().c_str());
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Constraint_toString
(JNIEnv* env, jobject c) {
  using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Constraint ppl_c = build_cxx_constraint(env, c);
  s << ppl_c;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Constraint_ascii_1dump
(JNIEnv* env, jobject j_this) {
  try {
    std::ostringstream s;
    Constraint c = build_cxx_constraint(env, j_this);
    c.ascii_dump(s);
    return env->NewStringUTF(s.str().c_str());
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Grid_1Generator_toString
(JNIEnv* env, jobject g) {
  using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Grid_Generator ppl_g = build_cxx_grid_generator(env, g);
  s << ppl_g;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Grid_1Generator_ascii_1dump
(JNIEnv* env, jobject j_this) {
  try {
    std::ostringstream s;
    Grid_Generator g = build_cxx_grid_generator(env, j_this);
    g.ascii_dump(s);
    return env->NewStringUTF(s.str().c_str());
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Congruence_toString
(JNIEnv* env, jobject g) {
  using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Congruence ppl_g = build_cxx_congruence(env, g);
  s << ppl_g;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Congruence_ascii_1dump
(JNIEnv* env, jobject j_this) {
  try {
    std::ostringstream s;
    Congruence c = build_cxx_congruence(env, j_this);
    c.ascii_dump(s);
    return env->NewStringUTF(s.str().c_str());
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Grid_1Generator_1System_toString
(JNIEnv* env, jobject ggs) {
  using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Grid_Generator_System ppl_ggs = build_cxx_grid_generator_system(env, ggs);
  s << ppl_ggs;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Grid_1Generator_1System_ascii_1dump
(JNIEnv* env, jobject j_this) {
  try {
    std::ostringstream s;
    Grid_Generator_System gs = build_cxx_grid_generator_system(env, j_this);
    gs.ascii_dump(s);
    return env->NewStringUTF(s.str().c_str());
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Generator_1System_toString
(JNIEnv* env, jobject gs) {
  using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Generator_System ppl_gs = build_cxx_generator_system(env, gs);
  s << ppl_gs;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Generator_1System_ascii_1dump
(JNIEnv* env, jobject j_this) {
  try {
    std::ostringstream s;
    Generator_System gs = build_cxx_generator_system(env, j_this);
    gs.ascii_dump(s);
    return env->NewStringUTF(s.str().c_str());
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Constraint_1System_toString
(JNIEnv* env, jobject cs) {
  using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Constraint_System ppl_cs = build_cxx_constraint_system(env, cs);
  s << ppl_cs;
  return env->NewStringUTF(s.str().c_str());
}


JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Constraint_1System_ascii_1dump
(JNIEnv* env, jobject j_this) {
  try {
    std::ostringstream s;
    Constraint_System cs = build_cxx_constraint_system(env, j_this);
    cs.ascii_dump(s);
    return env->NewStringUTF(s.str().c_str());
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Congruence_1System_toString
(JNIEnv* env, jobject cgs) {
  using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Congruence_System ppl_cgs = build_cxx_congruence_system(env, cgs);
  s << ppl_cgs;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_Congruence_1System_ascii_1dump
(JNIEnv* env, jobject j_this) {
  try {
    std::ostringstream s;
    Congruence_System cs = build_cxx_congruence_system(env, j_this);
    cs.ascii_dump(s);
    return env->NewStringUTF(s.str().c_str());
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jstring JNICALL
Java_parma_1polyhedra_1library_IO_wrap_1string
(JNIEnv* env, jclass, jstring str, jint indent_depth,
 jint preferred_first_line_length, jint preferred_line_length) {
  try {
    unsigned ind = jtype_to_unsigned<unsigned int>(indent_depth);
    unsigned pfll = jtype_to_unsigned<unsigned int>(preferred_first_line_length);
    unsigned pll = jtype_to_unsigned<unsigned int>(preferred_line_length);
    const char* chars = env->GetStringUTFChars(str, 0);
    CHECK_RESULT_RETURN(env, chars, 0);
    using namespace Parma_Polyhedra_Library::IO_Operators;
    std::string s = wrap_string(chars, ind, pfll, pll);
    env->ReleaseStringUTFChars(str, chars);
    return env->NewStringUTF(s.c_str());
  }
  CATCH_ALL;
  return 0;
}
