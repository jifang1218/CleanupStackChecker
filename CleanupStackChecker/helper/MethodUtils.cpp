//
//  MethodUtils.cpp
//  CleanupStackChecker
//
//  Created by jifang on 2024-05-13.
//

#include "MethodUtils.h"
#include "clang/AST/DeclCXX.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/SourceManager.h"
#include "llvm/Support/SystemUtils.h"

namespace Fang {

using namespace std;
using namespace clang;

list<string> MethodUtils::_senders;

bool MethodUtils::IsCleanupStackMethod(const std::string &sender, const std::string &message) {
    bool ret = false;
    
    ret = !isCleanupStackPush(sender, message)
        && !isCleanupStackPop(sender, message)
        && !isCleanupStackPush(sender, message)
        && !isCleanupStackPopAndDestroy(sender, message);
    
    return ret;
}

bool MethodUtils::isCleanupStackPush(const std::string &sender, const std::string &message) {
    bool ret = false;
    
    if (sender == "CleanupStack"
        && message == "Push") {
        ret = true;
    }
    
    return ret;
}

bool MethodUtils::isCleanupStackPop(const std::string &sender, const std::string &message) {
    bool ret = false;
    
    if (sender == "CleanupStack"
        && message == "Pop") {
        ret = true;
    }
    
    return ret;
}

bool MethodUtils::isCleanupStackPopAndDestroy(const std::string &sender, const std::string &message) {
    bool ret = false;
    
    if (sender == "CleanupStack"
        && message == "PopAndDestroy") {
        ret = true;
    }
    
    return ret;
}

bool MethodUtils::isLMethod(const std::string &sender, const std::string &message) {
    bool ret = false;
    
    if (message.substr(message.length() - 1) == "L") {
        ret = true;
    }
    
    return ret;
}

bool MethodUtils::isLCMethod(const std::string &sender, const std::string &message) {
    bool ret = false;

    if (message.substr(message.length() - 2) == "LC") {
        ret = true;
    }
    
    return ret;
}

bool MethodUtils::isSafeMethod(const std::string &sender, const std::string &message) {
    bool ret = false;
    
    ret = !MethodUtils::IsCleanupStackMethod(sender, message)
        && !MethodUtils::isLCMethod(sender, message)
        && !MethodUtils::isLMethod(sender, message);
    
    return ret;
}

MethodInfo MethodUtils::GetCallInfo(const clang::CallExpr *callExpr) {
    MethodInfo ret;
    
    if (!callExpr) {
        return ret;
    }
    
    // CXXMethodDecl represents static/non-static methods.
    const CXXMethodDecl *methodDecl = llvm::dyn_cast<CXXMethodDecl>(callExpr->getCalleeDecl());
    ret.message = methodDecl->getNameAsString();
    
    // get CXX class type.
    const CXXRecordDecl *recordDecl = llvm::dyn_cast<CXXRecordDecl>(methodDecl->getParent());
    ret.sender = recordDecl->getNameAsString();
    
#if 0
    llvm::outs() << "---------------------------------\n";
    llvm::outs() << ret.sender << "\n";
    llvm::outs() << ret.message << "\n";
#endif
    
    // if the method has 1 or more parameters, we get the 1st parameter name
    // Ex. CleanupStack::Push(pObj) ==> we get pObj.
    if (callExpr->getNumArgs() > 0) {
        const clang::Expr *argExpr = callExpr->getArg(0)->IgnoreParenCasts();
        if (const clang::DeclRefExpr *instanceDeclRef = llvm::dyn_cast<clang::DeclRefExpr>(argExpr)) {
            if (const NamedDecl *instanceNamedDecl = instanceDeclRef->getFoundDecl()) {
                ret.param = instanceNamedDecl->getNameAsString();
            }
        }
    }
    
    // get location & path
    const ASTContext &ast = recordDecl->getASTContext();
    const SourceManager &SM = ast.getSourceManager();
    clang::SourceRange Range = callExpr->getSourceRange();
    clang::SourceLocation startLoc = Range.getBegin();
    ret.lineNum = SM.getSpellingLineNumber(startLoc);
    ret.colNum = SM.getSpellingColumnNumber(startLoc);
    ret.filePath = SM.getFilename(startLoc);
    
    // it is a instance method, we need to replace classname with instance name.
    // otherwise it is a static method of a class, we just keep the class name.
    if (const clang::CXXMemberCallExpr *memberCallExpr = llvm::dyn_cast<CXXMemberCallExpr>(callExpr)) {
        clang::Expr *instanceExpr = memberCallExpr->getImplicitObjectArgument()->IgnoreParenCasts();
        clang::DeclRefExpr *instanceDeclRef = llvm::dyn_cast<clang::DeclRefExpr>(instanceExpr);
        
        if (const NamedDecl *instanceNamedDecl = instanceDeclRef->getFoundDecl()) {
            ret.sender = instanceNamedDecl->getNameAsString();
        }
    }

#if 0
    llvm::outs() << "---------------------------------\n";
    llvm::outs() << ret.sender << "\n"
                << ret.message << "\n"
                << ret.param << "\n"
                << "(" << ret.lineNum << ", " << ret.colNum << ")\n"
                << ret.filePath << "\n";
#endif
    
    // determine its type.
    if (MethodUtils::isLMethod(ret.sender, ret.message)) {
        ret.type = MethodType::L_Method;
    } else if (MethodUtils::isLCMethod(ret.sender, ret.message)) {
        ret.type = MethodType::LC_Method;
    } else if (MethodUtils::isSafeMethod(ret.sender, ret.message)) {
        ret.type = MethodType::Safe_Method;
    } else if (MethodUtils::isCleanupStackPop(ret.sender, ret.message)) {
        ret.type = MethodType::CleanupStack_Pop;
    } else if (MethodUtils::isCleanupStackPush(ret.sender, ret.message)) {
        ret.type = MethodType::CleanupStack_Push;
    } else if (MethodUtils::isCleanupStackPopAndDestroy(ret.sender, ret.message)) {
        ret.type = MethodType::CleanupStack_PopAndDestroy;
    } else {
    }

    return ret;
}

} // Fang
