// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

//#include "structures.h"

// SU2-6.1.0/Common/src/geometry_structure.cpp:9428:19:
Xcg = 0.0;
Counter = 0;
// CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
for (unsigned short j = 0; j < N_POINTS_TRIANGLE; j++) {
  if (vnodes_triangle[j] < Global_nPoint - ActDiskNewPoints) {
    Xcg += CoordXVolumePoint[VolumePoint_Inv[vnodes_triangle[j]]];
    Counter++;
  }
}
