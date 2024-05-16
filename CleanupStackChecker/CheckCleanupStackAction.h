#include "clang/Frontend/FrontendAction.h"
#include "clang/AST/ASTConsumer.h"
#include "llvm/ADT/StringRef.h"
#include <memory>

namespace clang {
	class CompilerInstance;
}

namespace Fang {

class CheckCleanupStackAction : public clang::ASTFrontendAction {
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
                                                          clang::CompilerInstance &CI, llvm::StringRef InFile) override;
};

} // Fang
