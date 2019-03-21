// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

#include "structures.h"

void transform_TEST_POSITIVE() {
  int foo[] = {16, 2, 77, 40, 12071};
  int foo2[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    foo2[n] = foo[n];
  }

  int foo3[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    *(foo3 + n) = *(foo + n);
  }

  int counter = 0;
  int foo4[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [search-for-Std-Algorithm-Patterns]
  do {
    foo4[counter] = foo[counter];
    counter++;
  } while (counter <= 4);

  int counter1 = 0;
  int foo5[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [search-for-Std-Algorithm-Patterns]
  do {
    *(foo5 + counter1) = *(foo + counter1);
    counter1++;
  } while (counter1 <= 4);

  int counter2 = 0;
  int foo6[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [search-for-Std-Algorithm-Patterns]
  while (counter2 <= 4) {
    foo6[counter2] = foo[counter2];
    counter2++;
  }

  int counter3 = 0;
  int foo7[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [search-for-Std-Algorithm-Patterns]
  while (counter3 <= 4) {
    *(foo7 + counter3) = *(foo + counter3);
    counter3++;
  }
}
