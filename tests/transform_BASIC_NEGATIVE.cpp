// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

void transform_TEST_NEGATIVE() {
  int foo[] = {16, 2, 77, 40, 12071};
  int foo2[5];
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure with operation '=' in line 8 does look like a std::transform [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    foo[n] = 1;
  }

  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '=' in line 13 does look like a std::transform [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    foo2[n] = foo[n];
  }

  int fooRangeLoop[5] = {0, 1, 2, 3, 4};
  int fooRangeLoop2[5] = {0, 1, 2, 3, 4};
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure with operation '+=' in line 20 does look like a std::transform [search-for-Std-Algorithm-Patterns]
  for(auto i : fooRangeLoop){
    foo[i] += i;
  }

  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure with operation '==' in line 65 does look like a std::transform [search-for-Std-Algorithm-Patterns]
  for(auto i : fooRangeLoop){
    // CHECK-MESSAGES-NOT: :[[@LINE+1]]:5: warning: Structure with operation '==' in line 65 does look like a std::transform [search-for-Std-Algorithm-Patterns]
    for(auto j : fooRangeLoop2){
      i = j;
    }
  }
}

