// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

#include "structures.h"

// SU2-6.1.0/Common/src/grid_movement_structure.cpp:2336:3:
// CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure does look like a std::transform [search-for-Std-Algorithm-Patterns]
for (unsigned short jMarker = 0; jMarker < config->GetnMarker_Monitoring();
     jMarker++) {
  Center[0] = config->GetRefOriginMoment_X(jMarker) + deltaX[0];
  Center[1] = config->GetRefOriginMoment_Y(jMarker) + deltaX[1];
  Center[2] = config->GetRefOriginMoment_Z(jMarker) + deltaX[2];
  config->SetRefOriginMoment_X(jMarker, Center[0]);
  config->SetRefOriginMoment_Y(jMarker, Center[1]);
  config->SetRefOriginMoment_Z(jMarker, Center[2]);
}
