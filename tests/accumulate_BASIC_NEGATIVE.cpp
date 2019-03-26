// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

//#include "structures.h"

void accumulate_TEST_NEGATIVE() {
  int foo[5] = {16, 2, 77, 40, 12071};
  int *foop;
  foop = foo;
  int sum1 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '=' in line 12 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    sum1 = foo[n] + (sum1 + 1);
  }
}
