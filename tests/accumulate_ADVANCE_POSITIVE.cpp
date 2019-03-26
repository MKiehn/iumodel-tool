// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

//#include "structures.h"

// SU2-6.1.0/Common/src/geometry_structure.cpp:9428:19:
void accumulate_TEST_POSITIVE() {
  float Xcg = 0.0;
  int Counter = 0;
  short N_POINTS_TRIANGLE = 5;
  int vnodes_triangle[5];
  int CoordXVolumePoint[5];
  int VolumePoint_Inv[5];
  int Global_nPoint = 1;
  int ActDiskNewPoints = 0;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '+=' in line 18 does look like a std::accumulate [search-for-Std-Algorithm-Patterns]
  for (unsigned short j = 0; j < N_POINTS_TRIANGLE; j++) {
    if (vnodes_triangle[j] < Global_nPoint - ActDiskNewPoints) {
      Xcg += CoordXVolumePoint[VolumePoint_Inv[vnodes_triangle[j]]];
      Counter++;
    }
  }
}
