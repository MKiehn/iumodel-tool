// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/misc-finduse-ofstdalgorithm

#include "structures.h"

void search_TEST_POSITIV() {
  int foo[5] = {16, 2, 77, 40, 12071};
  int foo2[5] = {16, 3, 77, 40, 12071};

  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::search [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    for (int m = 0; m < 5; m++){
      if (foo2[n] == foo[m]) {
        return;
      }
    }
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::search [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    int counter = 0;
    do {
      if (*(foo2 + n) == *(foo + counter)) {
        break;
      }
      counter++;
    } while (counter < 5);
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::search [search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    int counter = 0;
    while (counter < 5) {
      switch (*(foo2 + n) == *(foo + counter)) {
      case 0:
        return;
      }
      counter++;
    }
  }
  // Do here
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [search-for-Std-Algorithm-Patterns]
  int counter = 0;
  do {
    for (int m = 0; m < 5; m++){
      if (foo2[counter] == foo[m]) {
        break;
      }
    }
    counter++;
  }while(counter < 5);
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [search-for-Std-Algorithm-Patterns]
  int counter2 = 0;
  do {
    int counter = 0;
    do {
      if (foo2[counter2] == foo[counter]) {
        return;
      }
      counter++;
    } while (counter < 5);
    counter2++;
  }while( counter2 < 5);
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [search-for-Std-Algorithm-Patterns]
  int counter3 = 0;
  do {
    int counter = 0;
    while (counter < 5) {
      switch (*(foo2 + counter3) == *(foo + counter)) {
      case 0:
        return;
      }
      counter++;
    }
    counter3++;
  }while(counter3 < 5);
  // While here
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [search-for-Std-Algorithm-Patterns]
  int counter4 = 0;
  while(counter4 < 5) {
    for (int m = 0; m < 5; m++){
      if (foo2[counter4] == foo[m]) {
        break;
      }
    }
    counter4++;
  }
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [search-for-Std-Algorithm-Patterns]
  int counter5 = 0;
  while(counter5 < 5){
    int counter = 0;
    do {
      if (foo2[counter5] == foo[counter]) {
        return;
      }
      counter++;
    } while (counter < 5);
    counter5++;
  }
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [search-for-Std-Algorithm-Patterns]
  int counter6 = 0;
  while(counter6 < 5) {
    int counter = 0;
    while (counter < 5) {
      switch (*(foo2 + counter6) == *(foo + counter)) {
      case 0:
        return;
      }
      counter++;
    }
    counter6++;
  }
}
