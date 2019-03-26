// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

//#include "structures.h"

// SU2-6.1.0/SU2_CFD/src/solver_structure.cpp:2626:3:
void transform_TEST_POSITIVE(){
int Restart_Meta[8];
int Restart_Meta_Passive[8];

  // CHECK-MESSAGES: :[[@LINE+1]]:1: warning: Structure with operation '=' in line 12 does look like a std::transform [search-for-Std-Algorithm-Patterns]
for (unsigned short iVar = 0; iVar < 8; iVar++)
  Restart_Meta[iVar] = Restart_Meta_Passive[iVar];
}
