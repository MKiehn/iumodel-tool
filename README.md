### install manually
1. copy the folder **iumodel** to your **_clang-tidy folder_** (`llvm/tools/clang/tools/extra/clang-tidy`)
2. insert `add_subdirectory(iumodel)` in **CMakeLists.txt** in your **_clang-tidy folder_**
3. add `clangTidyIumodelModule` to **target_link_libraries** in **CMakeLists.txt** in **_clang-tidy folder_/tool**
4. insert the following code in **ClangTidyMain.cpp** in **_clang-tidy folder_/tool** at the end of the **namespace tidy**
```
// This anchor is used to force the linker to link the IumodelModule.
extern volatile int IumodelModuleAnchorSource;
static int LLVM_ATTRIBUTE_UNUSED IumodelModuleAnchorDestination = IumodelModuleAnchorSource;
```
5. copy the cpp files in folder **tests** to your **_test folder_** (`llvm/tools/clang/tools/extra/test`)
6. copy the folder in **tests/Inputs** to your **_Inputs folder_** (`llvm/tools/clang/tools/extra/test/Inputs`)
7. run cmake and recompile clang-tidy

### run clang-tidy
you probably want to run this tool like this:  
`.\clang-tidy.exe -config="{Checks: '-*,search-for-Std-Algorithm-Patterns'}" path/to/the/c/file/code.c --`

