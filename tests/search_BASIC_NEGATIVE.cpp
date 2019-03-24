// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

#include "structures.h"

bool predicate(int *foo, int *bar){
    return *foo == *bar ? true : false;
}

void search_TEST_NEGATIVE() {
    int foo[5] = {16, 2, 77, 40, 12071};
    int foo2[5] = {16, 3, 77, 40, 12071};

    // CHECK-MESSAGES-NOT: :[[@LINE+1]]:3: warning: Structure does look like a std::search [search-for-Std-Algorithm-Patterns]
    for (int n = 0; n < 5; n++) {
        for (int m = 0; m < 5; m++){
            if (predicate(&foo2[n],&foo[m])) {
                return;
            }
        }
    }
}
