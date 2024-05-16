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

class MethodUtils {
public:
    static MethodInfo GetCallInfo(const clang::CallExpr *callExpr);
    static bool IsCleanupStackMethod(const std::string &sender, const std::string &message);
    
private:
    static bool isCleanupStackPush(const std::string &sender, const std::string &message);
    static bool isCleanupStackPop(const std::string &sender, const std::string &message);
    static bool isCleanupStackPopAndDestroy(const std::string &sender, const std::string &message);
    static bool isLMethod(const std::string &sender, const std::string &message);
    static bool isLCMethod(const std::string &sender, const std::string &message);
    static bool isSafeMethod(const std::string &sender, const std::string &message);

private:
    static std::list<std::string> _senders;
};

} // Fang

#endif /* MethodUtils_hpp */
