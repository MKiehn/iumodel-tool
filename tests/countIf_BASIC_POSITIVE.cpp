// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

#include "structures.h"

bool predicate(int *foo) { return *foo == 0 ? true : false; }

void countIf_TEST_POSITIVE(int x){
  int foo[] = {16, 2, 77, 40, 12071};
  int counter =0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '++' in line 13 does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  do{
    if(foo[0] == x){
      counter++;
    }
  }while(true);
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '++' in line 19 does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  do {
    switch(foo[0] != x) {
    case 0 : counter++;
    }
  }while(true);
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '++' in line 25 does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  while(true){
    if(!(foo[0] == x)){
      counter++;
    }
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '++' in line 31 does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  while(true){
    switch(foo[0] != x) {
    case 0 : counter++;
    }
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '++' in line 37 does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  do{
    if(foo[0] == x){
      counter++;
    }
  }while(true);

  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '++' in line 44 does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  do {
    if (predicate(&foo[0])) {
      counter++;
    }
  } while (true);

  int fooRangeLoop[5] = {0, 1, 2, 3, 4};
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '++' in line 52 does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  for(auto i : fooRangeLoop){
    switch(foo[i] != x) {
    case 0 : counter++;
    }
  }

  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '++' in line 59 does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  for(auto i : fooRangeLoop){
    if(!(*foo == x)){
      counter++;
    }
  }

  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '++' in line 66 does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  for(auto i : fooRangeLoop){
    switch(i != x) {
    case 0 : counter++;
    }
  }
}
