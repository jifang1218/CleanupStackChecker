//
//  MethodUtils.hpp
//  CleanupStackChecker
//
//  Created by jifang on 2024-05-13.
//

#ifndef MethodUtils_hpp
#define MethodUtils_hpp

#include <list>
#include <string>

#include "MethodInfo.h"

namespace clang {
class CallExpr;
}

namespace Fang {

/**
 helper class to fetch info from a call expression.
 */
class MethodUtils {
public:
    /**
     it will get class::function(param1...), filepath, line number etc.
     */
    static MethodInfo GetCallInfo(const clang::CallExpr *callExpr);
    
    /**
     check if the current node is a cleanupstack method (push or pop)
     */
    static bool IsCleanupStackMethod(const std::string &sender, const std::string &message);
    
private:
    static bool isCleanupStackPush(const std::string &sender, const std::string &message);
    static bool isCleanupStackPop(const std::string &sender, const std::string &message);
    static bool isCleanupStackPopAndDestroy(const std::string &sender, const std::string &message);
    static bool isLMethod(const std::string &sender, const std::string &message);
    static bool isLCMethod(const std::string &sender, const std::string &message);
    /**
     check if the method is neither Leave method nor LeaveC method.
     */
    static bool isSafeMethod(const std::string &sender, const std::string &message);

private:
    /**
     it contains the instance names. 
     */
    static std::list<std::string> _senders;
};

} // Fang

#endif /* MethodUtils_hpp */
