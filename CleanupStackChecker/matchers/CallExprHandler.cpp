//
//  CallExprHandler.cpp
//  CleanupStackChecker
//
//  Created by jifang on 2024-05-13.
//

#include "CallExprHandler.h"
#include "MethodUtils.h"
#include "ErrorMgr.h"
#include "clang/AST/Decl.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "llvm/Support/SystemUtils.h"
#include <algorithm>

using namespace clang;

namespace Fang {

using namespace std;

const char *CallExprHandler::kCallExprHandlerId = "callExpr";

void CallExprHandler::run(const clang::ast_matchers::MatchFinder::MatchResult &Result) {
    ErrorMgr &errMgr = ErrorMgr::getInstance();
    
    // get all calls
    const CallExpr *callExpr = Result.Nodes.getNodeAs<CallExpr>(CallExprHandler::kCallExprHandlerId);
    MethodInfo info = MethodUtils::GetCallInfo(callExpr);
    
#if 0
    llvm::outs() << "---------------------------------\n";
    llvm::outs() << "sender : " << info.sender << "\n"
                << "message : " << info.message << "\n"
                << "param : " << info.param << "\n";
#endif
    
    switch (info.type) {
        case MethodType::Undetermined: {
            errMgr.Add(info, "undetermined call.");
        } break;
        case MethodType::Safe_Method: {
        } break;
        case MethodType::L_Method: {
            if (!containsSender(info.sender)) {
                errMgr.Add(info, "Missing CleanupStack::Push.");
            }
        } break;
        case MethodType::LC_Method: {
            if (containsSender(info.sender)) {
                errMgr.Add(info, "Duplicated " + info.sender + " on CleanupStack.");
            } else {
                _senders.push_back(info.sender);
            }
        } break;
        case MethodType::CleanupStack_Pop: {
            if (!containsSender(info.param)) {
                errMgr.Add(info, "No " + info.param + "on CleanupStack.");
            } else {
                _senders.erase(find(_senders.begin(), _senders.end(), info.param));   
            }
        } break;
        case MethodType::CleanupStack_Push: {
            if (containsSender(info.param)) {
                errMgr.Add(info, "Duplicated " + info.param + " on CleanupStack.");
            } else {
                _senders.push_back(info.param);
            }
        } break;
        case MethodType::CleanupStack_PopAndDestroy: {
            _senders.clear();
        } break;
        default: {
        } break;
    }
            
}

bool CallExprHandler::containsSender(const std::string &sender) const {
    bool ret = false;

    if (find(_senders.begin(), _senders.end(), sender) != _senders.end()) {
        ret = true;
    }
    
    return ret;
}

} // Fang
