// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel


#include "structures.h"

void accumulate_TEST_POSITIVE(){
  int foo[5] = {16, 2, 77, 40, 12071};
  int *foop;
  foop = foo;
  int sum1 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '+=' in line 13 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    sum1 += foo[n];
  }

  int sum2 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '+=' in line 19 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    sum2 += *(foo + n);
  }

  int sum4 = 0;
  int doLoopIndex2 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '+=' in line 26 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  do {
    sum4 += *(foo + doLoopIndex2);
    doLoopIndex2++;
  } while (doLoopIndex2 < 5);

  int sum5 = 0;
  int whileLoopIndex1 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '+=' in line 34 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  while (whileLoopIndex1 < 5) {
    sum5 += foo[whileLoopIndex1];
    whileLoopIndex1++;
  }

  int sum6 = 0;
  int whileLoopIndex2 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '+=' in line 42 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  while (whileLoopIndex2 < 5) {
    sum6 += *(foo + whileLoopIndex2);
    whileLoopIndex2++;
  }

  int sum7 = 0;
  // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure with operation '=' in line 49 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    sum7 = sum7 + foo[n];
  }

  int sum8 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '=' in line 55 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    sum8 = sum8 + *(foo + n);
  }

  int sum10 = 0;
  int doLoopIndex4 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '=' in line 62 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  do {
    sum10 = sum10 + *(foo + doLoopIndex2);
    doLoopIndex4++;
  } while (doLoopIndex4 < 5);

  int sum12 = 0;
  int whileLoopIndex4 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '=' in line 70 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  while (whileLoopIndex4 < 5) {
    sum12 = sum12 + *(foo + whileLoopIndex4);
    whileLoopIndex4++;
  }

  int sum13 = 0;
  int whileLoopIndex5 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '=' in line 78 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  while (whileLoopIndex5 < 5) {
    sum13 = *(foo + whileLoopIndex4) + sum13  ;
    whileLoopIndex5++;
  }

  int sum14 = 0;
  int forrangeLoopIndex = 0;
  int fooRangeLoop[5] = {0, 1, 2, 3, 4};
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '+=' in line 87 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  for(auto i : fooRangeLoop){
    sum14 += foo[i];
  }

  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '=' in line 92 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  for(auto i : fooRangeLoop){
    sum14 = sum14 + *(foo + i);
  }
}
