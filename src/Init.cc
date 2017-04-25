/* Init class implementation (non-inline functions and static variables).
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2017 BUGSENG srl (http://bugseng.com)

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

#include "ppl-config.h"
#include "Init_defs.hh"
#include "Variable_defs.hh"
#include "Rounding_Dir_defs.hh"
#include "Coefficient_defs.hh"
#include "Linear_Expression_defs.hh"
#include "Constraint_defs.hh"
#include "Generator_defs.hh"
#include "Congruence_defs.hh"
#include "Grid_Generator_defs.hh"
#include "Constraint_System_defs.hh"
#include "Generator_System_defs.hh"
#include "Congruence_System_defs.hh"
#include "Grid_Generator_System_defs.hh"
#include "Polyhedron_defs.hh"
#include "Watchdog_defs.hh"
#include <stdexcept>

namespace PPL = Parma_Polyhedra_Library;

unsigned int PPL::Init::count = 0;

extern "C" void
ppl_set_GMP_memory_allocation_functions(void);


PPL::Init::Init() {
  // Only when the first Init object is constructed...
  if (count++ == 0) {
    // ... the GMP memory allocation functions are set, ...
    ppl_set_GMP_memory_allocation_functions();
    // ... the default output function for Variable objects is set, ...
    Variable::set_output_function(&Variable::default_output_function);
    // ... the Coefficient constants are initialized, ...
    Coefficient_constants_initialize();
    // ... the Linear_Expression class is initialized, ...
    Linear_Expression::initialize();
    // ... the Constraint, Generator, Congruence, Grid_Generator,
    // Constraint_System, Generator_System, Congruence_System,
    // Grid_Generator_System and Polyhedron classes are initialized, ...
    Constraint::initialize();
    Generator::initialize();
    Congruence::initialize();
    Grid_Generator::initialize();
    Constraint_System::initialize();
    Generator_System::initialize();
    Congruence_System::initialize();
    Grid_Generator_System::initialize();
    Polyhedron::initialize();

#if PPL_HAVE_DECL_SETITIMER && PPL_HAVE_DECL_SIGACTION
    // ... the Watchdog subsystem is initialized, ...
    Watchdog::Watchdog::initialize();
#endif // PPL_HAVE_DECL_SETITIMER && PPL_HAVE_DECL_SIGACTION

    // The default is chosen to have a precision greater than most
    // precise IEC 559 floating point (112 bits of mantissa).
    set_irrational_precision(DEFAULT_IRRATIONAL_PRECISION);
  }
}

PPL::Init::~Init() {
  // Only when the last Init object is destroyed...
  if (--count == 0) {

#if PPL_HAVE_DECL_SETITIMER && PPL_HAVE_DECL_SIGACTION
    // ... the Watchdog subsystem is finalized, ...
    Watchdog::Watchdog::finalize();
#endif // PPL_HAVE_DECL_SETITIMER && PPL_HAVE_DECL_SIGACTION

    // ... the Polyhedron, Grid_Generator_System, Congruence_System,
    // Generator_System, Constraint_System, Grid_Generator,
    // Congruence, Generator and Constraint classes are finalized
    // IN THAT ORDER, ...
    Polyhedron::finalize();
    Grid_Generator_System::finalize();
    Congruence_System::finalize();
    Generator_System::finalize();
    Constraint_System::finalize();
    Grid_Generator::finalize();
    Congruence::finalize();
    Generator::finalize();
    Constraint::finalize();
    // ... the Linear_Expression class is finalized, ...
    Linear_Expression::finalize();
    // ... and the Coefficient constants are finalized.
    Coefficient_constants_finalize();
  }
}

namespace Parma_Polyhedra_Library {

namespace Implementation {

namespace {

static Parma_Polyhedra_Library::Init* Parma_Polyhedra_Library_initializer_p;

} // namespace

void
initialize_aux() {
  if (Parma_Polyhedra_Library_initializer_p == 0) {
    Parma_Polyhedra_Library_initializer_p = new Init();
  }
}

void
finalize_aux() {
  PPL_ASSERT(Parma_Polyhedra_Library_initializer_p != 0);
  delete Parma_Polyhedra_Library_initializer_p;
  Parma_Polyhedra_Library_initializer_p = 0;
}

} // namespace Implementation

} // namespace Parma_Polyhedra_Library
