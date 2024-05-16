#include "clang/AST/ASTConsumer.h"
#include "matchers/CallExprHandler.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

namespace clang {
	class ASTContext;
}

namespace Fang {

class CheckCleanupStackConsumer : public clang::ASTConsumer {
public:
    CheckCleanupStackConsumer();
    void HandleTranslationUnit(clang::ASTContext &context) override;
    
private:
    CallExprHandler callExprHandler;
    clang::ast_matchers::MatchFinder matchFinder;
};

} // Fang
