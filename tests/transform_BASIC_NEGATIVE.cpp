// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

#include "structures.h"

bool predicate(int *foo, int *bar){
    return *foo == *bar ? true : false;
}

bool predicateValue(int *foo){
    return *foo > 5 ? true : false;
}

void transform_TEST_NEGATIVE() {
}
