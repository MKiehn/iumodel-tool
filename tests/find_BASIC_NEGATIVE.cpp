// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

#include "structures.h"

bool predicate(int *foo) { return *foo == 0 ? true : false; }

void find_TEST_NEGATIVE(int x) {
  int foo[] = {16, 2, 77, 40, 12071};
  int counter = 0;
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure does look like a std::find [search-for-Std-Algorithm-Patterns]
  do {
    if (predicate(&foo[counter])) {
      break;
    }
    counter++;
  } while (true);

  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure does look like a std::find [search-for-Std-Algorithm-Patterns]
  do {
    switch (foo[counter] > x) {
      case 0:
        return;
    }
    counter++;
  } while (true);
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure does look like a std::find [search-for-Std-Algorithm-Patterns]
  while (true) {
    if (foo[counter] < x) {
      break;
    }
    counter++;
  }
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure does look like a std::find [search-for-Std-Algorithm-Patterns]
  while (true) {
    switch (foo[counter] >= x) {
      case 0:
        return;
    }
    counter++;
  }
}
