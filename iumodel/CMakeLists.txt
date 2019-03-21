set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyIumodelModule
  SearchForStdAlgorithmPatternsCheck.cpp
  IuModelTidyModule.cpp

  LINK_LIBS
  clangAnalysis
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  clangTidyUtils
  clangTooling
)
