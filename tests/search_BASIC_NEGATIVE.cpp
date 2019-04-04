// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

//#include "structures.h"

bool predicate(int *foo, int *bar) { return *foo == *bar ? true : false; }

void search_TEST_NEGATIVE() {
  int foo[5] = {16, 2, 77, 40, 12071};
  int foo2[5] = {16, 3, 77, 40, 12071};

  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure with operation '==' in line 15 does look like a std::search [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:5: warning: Structure with operation '==' in line 15 does look like a std::search [search-for-Std-Algorithm-Patterns]
    for (int m = 0; m < 5; m++) {
      if (predicate(&foo2[n], &foo[m])) {
        return;
      }
    }
  }

  int fooRangeLoop[5] = {0, 1, 2, 3, 4};
  int fooRangeLoop2[5] = {0, 1, 2, 3, 4};
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure with operation '==' in line 28 does look like a std::search [search-for-Std-Algorithm-Patterns]
  for(auto i : fooRangeLoop){
    int counter = 0;
  // CHECK-MESSAGES: :[[@LINE+2]]:5: warning: Structure with operation '==' in line 29 does look like a std::find [search-for-Std-Algorithm-Patterns]
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:5: warning: Structure with operation '==' in line 29 does look like a std::search [search-for-Std-Algorithm-Patterns]
    while (counter < 5) {
      switch (*(foo + counter) == i) {
      case 0:
        return;
      }
    }
  }
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure with operation '==' in line 40 does look like a std::search [search-for-Std-Algorithm-Patterns]
  int counter2 = 0;
  do{
  // CHECK-MESSAGES: :[[@LINE+2]]:5: warning: Structure with operation '==' in line 41 does look like a std::find [search-for-Std-Algorithm-Patterns]
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:5: warning: Structure with operation '==' in line 41 does look like a std::search [search-for-Std-Algorithm-Patterns]
    for(auto i : fooRangeLoop){
      switch (*(foo2 + counter2) == i) {
      case 0:
        return;
      }
      counter2++;
    }
  }while (counter2 < 5);

  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure with operation '==' in line 53 does look like a std::search [search-for-Std-Algorithm-Patterns]
  for(auto i : fooRangeLoop){
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:5: warning: Structure with operation '==' in line 53 does look like a std::search [search-for-Std-Algorithm-Patterns]
    for(auto j : fooRangeLoop2){
      if(i == j){
        return;
      }
    }
  }
}
