// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

#include <string.h>
// SU2-6.1.0/externals/tecio/tecsrc/datautil.cpp:706:25:

char GetIoFileInt(char* FileStream, int IVersion, int var1, int var2,
                  bool flag) {
  return 'c';
}
bool ReallocString(char* TargetStr, int TargetStrLen) { return true; }

void countIf_TEST_POSITIVE() {
  char CharValue;
  char StrBuffer[10];
  int I;
  char MaxCharacters;
  bool IsOk, ProcessData;
  int MAX_STRBUFFER_LEN, StrBufferLen, TargetStrLen;
  char* TargetStr;
  char* FileStream;
  int IVersion;
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: Structure with operation '++' in line 32 does look like a std::count_if [search-for-Std-Algorithm-Patterns]
  do {
    CharValue = GetIoFileInt(FileStream, IVersion, 0, 255, &IsOk);
    if (IsOk && ProcessData) {
      /*
       * if the limit is not exceded, stuff the
       * character into the buffer
       */
      if (CharValue != '\0' && (I < MaxCharacters || MaxCharacters == 0)) {
        StrBuffer[StrBufferLen] = (char)CharValue;
        StrBufferLen++;
      }

      if (CharValue == '\0' || StrBufferLen == MAX_STRBUFFER_LEN) {
        if (StrBufferLen != 0 || *TargetStr == NULL) {
          StrBuffer[StrBufferLen] = '\0';
          TargetStrLen += StrBufferLen;
          IsOk = ReallocString(TargetStr, TargetStrLen);
          if (IsOk)
            // strcat(*TargetStr, StrBuffer);
            StrBufferLen = 0; /* reset the string buffer */
        }
      }
    }

    I++;
  } while (IsOk && (char)CharValue != '\0');
}
