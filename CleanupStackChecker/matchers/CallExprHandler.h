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

/**
 an AST match finder callback class. 
 */
class CallExprHandler : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
    // the ID of the handler.
    static const char *kCallExprHandlerId;
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
    
private:
    bool containsSender(const std::string &sender) const;
    
private:
    std::vector<std::string> _senders; // class/instance names.
};

} // Fang

#endif /* CallExprHandler_hpp */
