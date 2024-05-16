#include "CheckCleanupStackConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"

#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace clang;

namespace Fang {

CheckCleanupStackConsumer::CheckCleanupStackConsumer() {
    matchFinder.addMatcher(clang::ast_matchers::callExpr().bind(CallExprHandler::kCallExprHandlerId), &callExprHandler);

}

void CheckCleanupStackConsumer::HandleTranslationUnit(clang::ASTContext &context) {
    matchFinder.matchAST(context);
}

} // Fang
