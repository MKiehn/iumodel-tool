// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/misc-finduse-ofstdalgorithm

#include "structures.h"

void countIf_TEST_POSITIV(int x){
  int foo[] = {16, 2, 77, 40, 12071};
  int counter =0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  do{
    if(foo[0] == x){
      counter++;
    }
  }while(true);
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  do {
    switch(foo[0] != x) {
    case 0 : counter++;
    }
  }while(true);
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  while(true){
    if(!(foo[0] == x)){
      counter++;
    }
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  while(true){
    switch(foo[0] != x) {
    case 0 : counter++;
    }
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  do{
    if(foo[0] == x){
      counter++;
    }
  }while(true);
}