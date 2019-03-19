// RUN: %check_clang_tidy %s misc-search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/misc-finduse-ofstdalgorithm

#include "structures.h"

void accumulate_TEST_POSITIV(){
  int foo[5] = {16, 2, 77, 40, 12071};
  int *foop;
  foop = foo;
  int sum1 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::accumulate [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    sum1 += foo[n];
  }

  int sum2 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::accumulate [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    sum2 += *(foo + n);
  }

  int sum4 = 0;
  int doLoopIndex2 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::accumulate [misc-search-for-Std-Algorithm-Patterns]
  do {
    sum4 += *(foo + doLoopIndex2);
    doLoopIndex2++;
  } while (doLoopIndex2 < 5);

  int sum5 = 0;
  int whileLoopIndex1 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::accumulate [misc-search-for-Std-Algorithm-Patterns]
  while (whileLoopIndex1 < 5) {
    sum5 += foo[whileLoopIndex1];
    whileLoopIndex1++;
  }

  int sum6 = 0;
  int whileLoopIndex2 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::accumulate [misc-search-for-Std-Algorithm-Patterns]
  while (whileLoopIndex2 < 5) {
    sum6 += *(foo + whileLoopIndex2);
    whileLoopIndex2++;
  }

  int sum7 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::accumulate [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    sum7 *= sum7 + foo[n];
  }

  int sum8 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::accumulate [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    sum8 = sum8 + *(foo + n);
  }

  int sum10 = 0;
  int doLoopIndex4 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::accumulate [misc-search-for-Std-Algorithm-Patterns]
  do {
    sum10 = sum10 + *(foo + doLoopIndex2);
    doLoopIndex4++;
  } while (doLoopIndex4 < 5);

  int sum12 = 0;
  int whileLoopIndex4 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::accumulate [misc-search-for-Std-Algorithm-Patterns]
  while (whileLoopIndex4 < 5) {
    sum12 = sum12 + *(foo + whileLoopIndex4);
    whileLoopIndex4++;
  }

  int sum13 = 0;
  int whileLoopIndex5 = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::accumulate [misc-search-for-Std-Algorithm-Patterns]
  while (whileLoopIndex5 < 5) {
    sum13 = *(foo + whileLoopIndex4) + sum13  ;
    whileLoopIndex5++;
  }
}
// negativ accumulate

void transform_TEST_POSITIV() {
  int foo[] = {16, 2, 77, 40, 12071};
  int foo2[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    foo2[n] = foo[n];
  }

  int foo3[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    *(foo3 + n) = *(foo + n);
  }

  int counter = 0;
  int foo4[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [misc-search-for-Std-Algorithm-Patterns]
  do {
    foo4[counter] = foo[counter];
    counter++;
  } while (counter <= 4);

  int counter1 = 0;
  int foo5[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [misc-search-for-Std-Algorithm-Patterns]
  do {
    *(foo5 + counter1) = *(foo + counter1);
    counter1++;
  } while (counter1 <= 4);

  int counter2 = 0;
  int foo6[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [misc-search-for-Std-Algorithm-Patterns]
  while (counter2 <= 4) {
    foo6[counter2] = foo[counter2];
    counter2++;
  }

  int counter3 = 0;
  int foo7[5];
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [misc-search-for-Std-Algorithm-Patterns]
  while (counter3 <= 4) {
    *(foo7 + counter3) = *(foo + counter3);
    counter3++;
  }
}

void transform_TEST_NEGATIV() {
}

void find_TEST_POSITIV(int x){
  int foo[] = {16, 2, 77, 40, 12071};
  int counter =0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::find [misc-search-for-Std-Algorithm-Patterns]
  do{
    if(foo[counter] == x){
      break;
    }
    counter++;
  }while(true);
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::find [misc-search-for-Std-Algorithm-Patterns]
  do {
    switch(foo[counter] != x) {
    case 0 : return;
    }
    counter++;
  }while(true);
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::find [misc-search-for-Std-Algorithm-Patterns]
  while(true){
    if( foo[counter] == x){
      break;
    }
    counter++;
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::find [misc-search-for-Std-Algorithm-Patterns]
  while(true){
    switch(foo[counter] != x) {
    case 0 : return;
    }
    counter++;
  }
}

void countIf_TEST_POSITIV(int x){
  int foo[] = {16, 2, 77, 40, 12071};
  int counter =0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [misc-search-for-Std-Algorithm-Patterns]
  do{
    if(foo[0] == x){
      counter++;
    }
  }while(true);
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [misc-search-for-Std-Algorithm-Patterns]
  do {
    switch(foo[0] != x) {
    case 0 : counter++;
    }
  }while(true);
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [misc-search-for-Std-Algorithm-Patterns]
  while(true){
    if(!(foo[0] == x)){
      counter++;
    }
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [misc-search-for-Std-Algorithm-Patterns]
  while(true){
    switch(foo[0] != x) {
    case 0 : counter++;
    }
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::count_if [misc-search-for-Std-Algorithm-Patterns]
  do{
    if(foo[0] == x){
      counter++;
    }
  }while(true);
}

void mismatch_TEST_POSITIV() {
  int foo[5] = {16, 2, 77, 40, 12071};
  int foo2[5] = {16, 3, 77, 40, 12071};

  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::mismatch [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    for (int m = 0; m < 5; m++){
      if (foo2[n] != foo[m]) {
        return;
      }
    }
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::mismatch [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    int counter = 0;
    do {
      if (*(foo2 + n) != *(foo + counter)) {
        break;
      }
      counter++;
    } while (counter < 5);
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::mismatch [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    int counter = 0;
    while (counter < 5) {
      switch (*(foo2 + n) != *(foo + counter)) {
      case 0:
        return;
      }
      counter++;
    }
  }
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::mismatch [misc-search-for-Std-Algorithm-Patterns]
  int counter = 0;
  do {
    for (int m = 0; m < 5; m++){
      if (foo2[counter] != foo[m]) {
        break;
      }
    }
    counter++;
  }while(counter < 5);
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::mismatch [misc-search-for-Std-Algorithm-Patterns]
  int counter2 = 0;
  do {
    int counter = 0;
    do {
      if (foo2[counter2] != foo[counter]) {
        return;
      }
      counter++;
    } while (counter < 5);
    counter2++;
  }while( counter2 < 5);
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::mismatch [misc-search-for-Std-Algorithm-Patterns]
  int counter3 = 0;
  do {
    int counter = 0;
    while (counter < 5) {
      switch (*(foo2 + counter3) != *(foo + counter)) {
      case 0:
        return;
      }
      counter++;
    }
    counter3++;
  }while(counter3 < 5);
  // While here
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::mismatch [misc-search-for-Std-Algorithm-Patterns]
  int counter4 = 0;
  while(counter4 < 5) {
    for (int m = 0; m < 5; m++){
      if (foo2[counter4] != foo[m]) {
        break;
      }
    }
    counter4++;
  }
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::mismatch [misc-search-for-Std-Algorithm-Patterns]
  int counter5 = 0;
  while(counter5 < 5){
    int counter = 0;
    do {
      if (foo2[counter5] != foo[counter]) {
        return;
      }
      counter++;
    } while (counter < 5);
    counter5++;
  }
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::mismatch [misc-search-for-Std-Algorithm-Patterns]
  int counter6 = 0;
  while(counter6 < 5) {
    int counter = 0;
    while (counter < 5) {
      switch (*(foo2 + counter6) != *(foo + counter)) {
      case 0:
        return;
      }
      counter++;
    }
    counter6++;
  }
}

void search_TEST_POSITIV() {
  int foo[5] = {16, 2, 77, 40, 12071};
  int foo2[5] = {16, 3, 77, 40, 12071};

  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::search [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    for (int m = 0; m < 5; m++){
      if (foo2[n] == foo[m]) {
        return;
      }
    }
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::search [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    int counter = 0;
    do {
      if (*(foo2 + n) == *(foo + counter)) {
        break;
      }
      counter++;
    } while (counter < 5);
  }
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::search [misc-search-for-Std-Algorithm-Patterns]
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
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [misc-search-for-Std-Algorithm-Patterns]
  int counter = 0;
  do {
    for (int m = 0; m < 5; m++){
      if (foo2[counter] == foo[m]) {
        break;
      }
    }
    counter++;
  }while(counter < 5);
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [misc-search-for-Std-Algorithm-Patterns]
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
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [misc-search-for-Std-Algorithm-Patterns]
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
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [misc-search-for-Std-Algorithm-Patterns]
  int counter4 = 0;
  while(counter4 < 5) {
    for (int m = 0; m < 5; m++){
      if (foo2[counter4] == foo[m]) {
        break;
      }
    }
    counter4++;
  }
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [misc-search-for-Std-Algorithm-Patterns]
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
  // CHECK-MESSAGES: :[[@LINE+2]]:3: warning: Structure does look like a std::search [misc-search-for-Std-Algorithm-Patterns]
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

void development_TEST_CASES(){
  int foo[] = {16, 2, 77, 40, 12071};
  int foo2[5];
  int i =0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [misc-search-for-Std-Algorithm-Patterns]
  for (int n = 0; n < 5; n++) {
    foo2[n] = foo[n];
    if(foo[n] > 1){
      i++;
    }
  }
}
