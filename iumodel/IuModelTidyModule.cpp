#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "SearchForStdAlgorithmPatternsCheck.h"

namespace clang {
namespace tidy {
namespace iumodel {

class IUmodelModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<SearchForStdAlgorithmPatternsCheck>(
        "search-for-Std-Algorithm-Patterns");
  }
};

} // namespace iumodel

// Register the IumodelTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<iumodel::IUmodelModule>
    X("iumodel-module", "Adds sf40 lint checks.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the IumodelModule.
volatile int IumodelModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
