/* Test number input.
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2014 BUGSENG srl (http://bugseng.com)

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
site: http://bugseng.com/products/ppl/ . */

#include "ppl_test.hh"
#include <string>
#include <sstream>
#include <cstdlib>

namespace {

using namespace Checked;

struct Test_Extended_Number_Policy {
  const_bool_nodef(check_overflow, true);
  const_bool_nodef(check_inf_add_inf, false);
  const_bool_nodef(check_inf_sub_inf, false);
  const_bool_nodef(check_inf_mul_zero, false);
  const_bool_nodef(check_div_zero, false);
  const_bool_nodef(check_inf_div_inf, false);
  const_bool_nodef(check_inf_mod, false);
  const_bool_nodef(check_sqrt_neg, false);
  const_bool_nodef(has_nan, true);
  const_bool_nodef(has_infinity, true);
  const_bool_nodef(fpu_check_inexact, false);
  const_bool_nodef(check_nan_result, true);
  static const Rounding_Dir ROUND_DEFAULT = ROUND_UP;
  static void handle_result(Result r);
};

inline void
Test_Extended_Number_Policy::handle_result(Result r) {
  if (r == V_NAN)
    return;
  Extended_Number_Policy::handle_result(r);
}

bool
aux_test(std::string input_string,
         std::string expected_output,
         std::string expected_residual,
         Result expected_result) {
  std::stringstream input_stream(input_string);
  Checked_Number<mpq_class, Test_Extended_Number_Policy> value;
  Result result = input(value, input_stream, ROUND_UP);
  // NOTE: clear input_stream status bits, since otherwise the next call
  // to getline will retrieve nothing at all.
  input_stream.clear();
  std::string residual;
  getline(input_stream, residual, '\0');
  std::stringstream output_stream;
  output_stream << value;
  std::string output = output_stream.str();

  bool ok = (result == expected_result
             && residual == expected_residual
             && output == expected_output);

  nout << "input = \"" << input_string << "\""
       << endl
       << "expected result = " << expected_result
       << ", actual result = " << result
       << endl
       << "expected value = \"" << expected_output << "\""
       << ", actual value = \"" << output << "\""
       << endl
       << "expected residual = \"" << expected_residual << "\""
       << ", actual residual = \"" << residual << "\""
       << endl;

  return ok;
}

// Testing symbols.
bool
test01() {
  return aux_test("inf", "+inf", "", V_EQ_PLUS_INFINITY)
    && aux_test("InF", "+inf", "", V_EQ_PLUS_INFINITY)
    && aux_test("+inF", "+inf", "", V_EQ_PLUS_INFINITY)
    && aux_test("-InF", "-inf", "", V_EQ_MINUS_INFINITY)
    && aux_test("-InFinity", "-inf", "inity", V_EQ_MINUS_INFINITY)
    && aux_test("Inf7", "+inf", "7", V_EQ_PLUS_INFINITY)
    && aux_test("nan", "nan", "", V_NAN)
    && aux_test("NAN", "nan", "", V_NAN)
    && aux_test("Nan", "nan", "", V_NAN);
}

// Testing symbols with trailing input and errors.
bool
test02() {
  return aux_test("nAn+", "nan", "+", V_NAN)
    && aux_test("naN/", "nan", "/", V_NAN)
    && aux_test("nAN/0", "nan", "/0", V_NAN)
    && aux_test("nAN/-3", "nan", "/-3", V_NAN)
    && aux_test("inF/3", "+inf", "/3", V_EQ_PLUS_INFINITY)
    && aux_test("Inf/-3", "+inf", "/-3", V_EQ_PLUS_INFINITY)
    && aux_test("-inf/-3", "-inf", "/-3", V_EQ_MINUS_INFINITY)
    && aux_test("-NAn", "nan", "NAn", V_CVT_STR_UNK);
}

// Testing integers.
bool
test03() {
  return aux_test("  -  2", "nan", "  2", V_CVT_STR_UNK)
    && aux_test("15", "15", "", V_EQ)
    && aux_test("34976098", "34976098", "", V_EQ)
    && aux_test("34976098349760983497609834976098",
                "34976098349760983497609834976098", "", V_EQ)
    && aux_test("3/-inf", "nan", "", V_CVT_STR_UNK)
    && aux_test("+77", "77", "", V_EQ)
    && aux_test("-77", "-77", "", V_EQ)
    && aux_test("-7777777777777777777777777",
                "-7777777777777777777777777", "", V_EQ)
    && aux_test("-77 ", "-77", " ", V_EQ)
    && aux_test("-77   ", "-77", "   ", V_EQ)
    && aux_test("-77ab", "-77", "ab", V_EQ)
    && aux_test("-77,33", "-77", ",33", V_EQ)
    && aux_test(" -  2", "nan", "  2", V_CVT_STR_UNK);
}

// Testing fractions.
bool
test04() {
  return aux_test("71.3", "713/10", "", V_EQ)
    && aux_test("0.123456", "1929/15625", "", V_EQ)
    && aux_test("12345678910111213141516.12345678910111213141516",
                "308641972752780328537903086419727527803285379/25000000000000000000000",
                "", V_EQ)
    && aux_test("0.123456 101", "1929/15625", " 101", V_EQ)
    && aux_test("0.123456   101", "1929/15625", "   101", V_EQ)
    && aux_test("0.123456     ", "1929/15625", "     ", V_EQ)
    && aux_test(".499975", "19999/40000", "", V_EQ)
    && aux_test(".333", "333/1000", "", V_EQ)
    && aux_test("+.333", "333/1000", "", V_EQ)
    && aux_test("-.333", "-333/1000", "", V_EQ)
    && aux_test(".0x333", "0", "x333", V_EQ);
}

// Testing exponent.
bool
test05() {
  return aux_test("15e1", "150", "", V_EQ)
    && aux_test("15*^8", "1500000000", "", V_EQ)
    && aux_test("1*^009", "1000000000", "", V_EQ)
    && aux_test("15*^111",
                "15000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                "", V_EQ)
    && aux_test("151515e+1", "1515150", "", V_EQ)
    && aux_test("151515151515151515e+1", "1515151515151515150", "", V_EQ)
    && aux_test("9200e-2", "92", "", V_EQ)
    && aux_test("15*^7e4", "150000000", "e4", V_EQ)
    && aux_test("15*^6/", "nan", "", V_CVT_STR_UNK)
    && aux_test("9200e", "nan", "", V_CVT_STR_UNK)
    && aux_test("9200ea", "nan", "a", V_CVT_STR_UNK)
    && aux_test("9200*^", "nan", "", V_CVT_STR_UNK)
    && aux_test("9200*^b", "nan", "b", V_CVT_STR_UNK)
    // Exponent and fraction.
    && aux_test("5.3e3", "5300", "", V_EQ)
    && aux_test("2.2e-1", "11/50", "", V_EQ)
    && aux_test("5.33333*^-4", "533333/1000000000", "", V_EQ)
    && aux_test("-2.20001*^+3", "-220001/100", "", V_EQ)
    && aux_test("7.e", "nan", "", V_CVT_STR_UNK)
    && aux_test("7.0 e3", "7", " e3", V_EQ);
}

// Testing exponent size limit.
bool
test06() {
  std::stringstream ss;
  ss << "1e" << (LONG_MAX / 10) + 1 << "0";
  std::stringstream ss2;
  ss2 << "1e" << (LONG_MAX / 10) << (LONG_MAX % 10) + 1;
  return aux_test(ss.str(), "nan", "", V_CVT_STR_UNK)
    && aux_test(ss2.str(), "nan", "", V_CVT_STR_UNK);
}

// Testing hexadecimals.
bool
test07() {
  return aux_test("0x", "nan", "", V_CVT_STR_UNK)
    && aux_test("0xx", "nan", "x", V_CVT_STR_UNK)
    && aux_test("0x0.f", "15/16", "", V_EQ)
    && aux_test("0x.f", "15/16", "", V_EQ)
    && aux_test("0x.fp3", "15/2", "", V_EQ)
    && aux_test("16^^.fp3", "15/2", "", V_EQ)
    && aux_test("0x100p-9", "1/2", "", V_EQ)
    && aux_test("16^^100p-9", "1/2", "", V_EQ)
    && aux_test("100p-9", "nan", "p-9", V_CVT_STR_UNK)
    && aux_test("0x.f*^1", "15", "", V_EQ)
    && aux_test("0x-f", "nan", "-f", V_CVT_STR_UNK)
    && aux_test("0xfa", "250", "", V_EQ)
    && aux_test("-0xfa", "-250", "", V_EQ)
    && aux_test("-0x000000000000000000000000fa", "-250", "", V_EQ)
    && aux_test("-0xfaz", "-250", "z", V_EQ)
    && aux_test("-0xfa .", "-250", " .", V_EQ)
    && aux_test("0xfa0xfa", "4000", "xfa", V_EQ)
    && aux_test("0x0b123", "45347", "", V_EQ);
}

// Testing hexadecimals fractions and exponents.
bool
test08() {
  return
    // Fraction.
    aux_test("0xfa.a", "2005/8", "", V_EQ)
    && aux_test("0xfa.ay", "2005/8", "y", V_EQ)
    && aux_test("-0xfa.", "-250", "", V_EQ)
    // Exponent.
    && aux_test("0x1e2", "482", "", V_EQ)
    && aux_test("0x1*^2", "256", "", V_EQ)
    && aux_test("0x1*^2-1", "256", "-1", V_EQ)
    // Fraction and exponent.
    && aux_test("0x0.1*^3", "256", "", V_EQ)
    && aux_test("-0x29382a093589c501594f729e672567.2f09f342582b4598*^-2",
                "-493504168323155221903720496056512238754896365637429427/590295810358705651712",
                "", V_EQ)
    && aux_test("-0x29382a093589c501594f729e672567.2f09f342582b4598*^-20",
                "-493504168323155221903720496056512238754896365637429427/2787593149816327892691964784081045188247552",
                "", V_EQ)
    && aux_test("-0x29382a093589c501594f729e672567.2f09f342582b4598*^-20b",
                "-493504168323155221903720496056512238754896365637429427/2787593149816327892691964784081045188247552",
                "b", V_EQ)
    && aux_test("0x0.1*^3   -0", "256", "   -0", V_EQ);
}

// Testing bases.
bool
test09() {
  return aux_test("3^^", "nan", "", V_CVT_STR_UNK)
    && aux_test("3^^z", "nan", "z", V_CVT_STR_UNK)
    && aux_test("^^3", "nan", "^^3", V_CVT_STR_UNK)
    && aux_test("3^^1", "1", "", V_EQ)
    && aux_test("2^^0", "0", "", V_EQ)
    && aux_test("2^^1", "1", "", V_EQ)
    && aux_test("2^^10", "2", "", V_EQ)
    && aux_test("2^^11", "3", "", V_EQ)
    && aux_test("36^^z", "35", "", V_EQ)
    && aux_test("36^^yz", "1259", "", V_EQ)
    && aux_test("36^^xyz", "44027", "", V_EQ)
    && aux_test("37^^2", "nan", "^2", V_CVT_STR_UNK)
    && aux_test("37^^1.1", "nan", "^1.1", V_CVT_STR_UNK)
    && aux_test("2^^113", "3", "3", V_EQ)
    && aux_test("2^^11 3", "3", " 3", V_EQ)
    && aux_test("3^^e2", "nan", "e2", V_CVT_STR_UNK);
}

// Testing bases with fractions and exponents.
bool
test10() {
  return
    // Fraction.
    aux_test("2^^11.1", "7/2", "", V_EQ)
    && aux_test("2^^11.1a", "7/2", "a", V_EQ)
    && aux_test("2^^11.1.", "7/2", ".", V_EQ)
    && aux_test("2^^11.1   ", "7/2", "   ", V_EQ)
    // Exponent.
    && aux_test("10^^2e3", "2000", "", V_EQ)
    && aux_test("8^^2e3", "1024", "", V_EQ)
    && aux_test("8^^2e38", "41538374868278621028243970633760768", "", V_EQ)
    && aux_test("8^^2e3e", "1024", "e", V_EQ)
    // Fraction and exponent.
    && aux_test("8^^2.1e3", "1088", "", V_EQ)
    && aux_test("8^^20402543.120347e7", "9073863231288", "", V_EQ)
    && aux_test("8^^2.18e3", "17/8", "8e3", V_EQ);
}

// Testing denominators.
bool
test11() {
  return aux_test("15/0", "nan", "", V_NAN)
    && aux_test("15/1", "15", "", V_EQ)
    && aux_test("15/3", "5", "", V_EQ)
    && aux_test("15/-3", "-5", "", V_EQ)
    && aux_test("15/3f", "5", "f", V_EQ);
}

// Testing denominators with fractions and exponents.
bool
test12() {
  return
    // Fraction.
    aux_test("27.9/3.1", "9", "", V_EQ)
    && aux_test("27.9/3.1=9", "9", "=9", V_EQ)
    // Exponent.
    && aux_test("15/30e-1", "5", "", V_EQ)
    && aux_test("27e3/30e-1", "9000", "", V_EQ)
    && aux_test("15*^-3/29e2", "3/580000", "", V_EQ)
    && aux_test("15/30e-1,2", "5", ",2", V_EQ)
    && aux_test("15/30e-1.2", "5", ".2", V_EQ)
    // Exponent and fraction.
    && aux_test("27.9e3/30e-1", "9300", "", V_EQ)
    && aux_test("27.9e3/30e-1/2", "9300", "/2", V_EQ)
    && aux_test("27.9e3/30e-1^^", "9300", "^^", V_EQ);
}

// Testing denominators with hexadecimals and bases.
bool
test13() {
  return
    // Hexadecimal.
    aux_test("0xf/0x3", "5", "", V_EQ)
    && aux_test("3048227.23429e3/0x230abc43",
                "304822723429/58790611500", "", V_EQ)
    && aux_test("0xf/0x3g", "5", "g", V_EQ)
    // Base.
    && aux_test("16^^f/4^^3.0e0*^3", "5", "*^3", V_EQ);
}

// LARGE_NUM has 14057 digits.
#define LARGE_NUM "29382093589501594796725672938209358950159472967256372938209358950159472967256729382093589501594729672567293820935899501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729611972567293820935899501594729672567229382093589501594292729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567299382093589501594072967256729382093589501594729672567293820935895015947296725672938209358950159472967256729383333332093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567293820935895015947296725672938209358950159472967256729382093589501594729672567"

// Testing a very large number.
bool
test14() {
  return aux_test(LARGE_NUM, LARGE_NUM, "", V_EQ);
}

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
  DO_TEST(test02);
  DO_TEST(test03);
  DO_TEST(test04);
  DO_TEST(test05);
  DO_TEST(test06);
  DO_TEST(test07);
  DO_TEST(test08);
  DO_TEST(test09);
  DO_TEST(test10);
  DO_TEST(test11);
  DO_TEST(test12);
  DO_TEST(test13);
  DO_TEST(test14);
END_MAIN
