include(`ppl_interface_generator_common.m4')dnl
include(`ppl_interface_generator_prolog_dat.m4')dnl
divert(-1)

dnl m4_separator(String)
dnl
dnl String is returned unless if it is empty, then use `,'
define(`m4_separator', `ifelse($1, `', `,', `$1')')

dnl m4_pattern_delimiter(String)
dnl
dnl For the system files we use the macro names
dnl where the patterns have no delimiters
dnl FIXME The `4' is temporary.
dnl This needs to be replaced by the empty string `'
dnl when the dat.m4 and code.m4 files are changed.
define(`m4_pattern_delimiter', `4')

dnl m4_term_sequence(Number of Iterations, String to be Repeated)
dnl
dnl generates a sequence of strings with the option of
dnl identifying each string uniquely and the option of
dnl changing the separator from the default `,'.
define(`m4_term_sequence',
  `ifelse(`$1', 0, ,
     `$2(1)`'ifelse(`$1', 1, ,
       `m4_forloop(`i', 2, `$1', `m4_separator(`$3') $2(i)')')')')

dnl ppl_prolog_sys_code
dnl
dnl For each recognised class in the "classes" list,
dnl takes main predicate input list and sends one line at a time to
dnl a macro that adds extensions for the result of
dnl a macro that sets the class and the schema(s).
define(`ppl_prolog_sys_code', `dnl
dnl Note: passing a dummy Class_Kind.
m4_procedure_names_to_code(`', m4_library_predicate_list)dnl
m4_all_classes_code`'dnl
')
divert`'dnl
