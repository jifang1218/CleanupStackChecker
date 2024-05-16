#include "CheckCleanupStackAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "CheckCleanupStackConsumer.h"

using namespace clang;

namespace Fang {

std::unique_ptr<ASTConsumer> CheckCleanupStackAction::CreateASTConsumer(clang::CompilerInstance &CI, llvm::StringRef inFile) {
    return std::unique_ptr<ASTConsumer>(new CheckCleanupStackConsumer());
}

} // Fang
