// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

#include "structures.h"

bool predicate(int *foo) { return *foo == 0 ? true : false; }

void countIf_TEST_NEGATIVE(int x) {
  int foo[] = {16, 2, 77, 40, 12071};
  int counter = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  do {
    if (predicate(&foo[0])) {
      counter++;
    }
  } while (true);

  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  while (true) {
    if (!(foo[0] == x)) {
      counter = counter + 1;
    }
  }

  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  while (true) {
    switch (foo[0] != x) {
      case 0:
        counter += 1;
    }
  }

  int counterConst = 1;
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    switch (foo[0] != x) {
      case 0:
        counter = counter + counterConst;
    }
  }
}
