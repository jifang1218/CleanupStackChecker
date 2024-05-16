//
//  CallExprHandler.hpp
//  CleanupStackChecker
//
//  Created by jifang on 2024-05-13.
//

#ifndef CallExprHandler_hpp
#define CallExprHandler_hpp

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <list>
#include <string>
#include <vector>

namespace Fang {

class ErrorMgr;

class CallExprHandler : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
    static const char *kCallExprHandlerId;
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
    
private:
    bool containsSender(const std::string &sender) const;
    
private:
    std::vector<std::string> _senders; // save senders/params.
};

} // Fang

#endif /* CallExprHandler_hpp */
