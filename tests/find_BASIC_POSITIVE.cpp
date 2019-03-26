// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

#include "structures.h"

void find_TEST_POSITIVE(int x){
  int foo[] = {16, 2, 77, 40, 12071};
  int counter =0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '==' in line 10 does look like a std::find [search-for-Std-Algorithm-Patterns]
  do{
    if(foo[counter] == x){
      break;
    }
    counter++;
  }while(true);
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '!=' in line 17 does look like a std::find [search-for-Std-Algorithm-Patterns]
  do {
    switch(foo[counter] != x) {
    case 0 : return;
    }
    counter++;
  }while(true);
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '==' in line 24 does look like a std::find [search-for-Std-Algorithm-Patterns]
  while(true){
      if( foo[counter] == x){
      break;
    }
    counter++;
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '!=' in line 31 does look like a std::find [search-for-Std-Algorithm-Patterns]
  while(true){
      switch(foo[counter] != x) {
    case 0 : return;
    }
    counter++;
  }
}

