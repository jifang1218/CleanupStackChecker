#include "clang/AST/ASTConsumer.h"
#include "matchers/CallExprHandler.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

namespace clang {
	class ASTContext;
}

namespace Fang {

/**
 The consumer class, required by the AST traversal.
 */
class CheckCleanupStackConsumer : public clang::ASTConsumer {
public:
    CheckCleanupStackConsumer();
    void HandleTranslationUnit(clang::ASTContext &context) override;
    
private:
    // the matcher callback will be handled in callExprHandler. 
    CallExprHandler callExprHandler;
    clang::ast_matchers::MatchFinder matchFinder;
};

} // Fang
