### install manually
1. copy the folder **uimodel** to your **_clang-tidy folder_** (`llvm/tools/clang/tools/extra/clang-tidy`)
2. insert `add_subdirectory(uimodel)` in **CMakeLists.txt** in your **_clang-tidy folder_**
3. add `clangTidyIumodelModule` to **target_link_libraries** in **CMakeLists.txt** in **_clang-tidy folder_/tool**
4. insert the following code in **ClangTidyMain.cpp** in **_clang-tidy folder_/tool** at the end of the **namespace tidy**
```
// This anchor is used to force the linker to link the IumodelModule.
extern volatile int IumodelModuleAnchorSource;
static int LLVM_ATTRIBUTE_UNUSED IumodelModuleAnchorDestination = IumodelModuleAnchorSource;
```
5. run cmake and recompile clang-tidy
