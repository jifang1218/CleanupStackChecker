//
//  MethodInfo.h
//  CleanupStackChecker
//
//  Created by jifang on 2024-05-13.
//

#ifndef MethodInfo_h
#define MethodInfo_h

#include <string>

namespace Fang {

enum class MethodType {
    Undetermined = 0,
    Safe_Method,
    L_Method,
    LC_Method,
    CleanupStack_Push,
    CleanupStack_Pop,
    CleanupStack_PopAndDestroy
};

struct MethodInfo {
    std::string sender;
    std::string message;
    unsigned int lineNum = -1;
    unsigned int colNum = -1;
    std::string filePath;
    std::string param;
    MethodType type;
    
    bool IsValid() const {
        return (sender.length() > 0
                && message.length() > 0
                && lineNum >= 0
                && colNum >= 0
                && filePath.length() > 0);
    }
};



} // Fang

#endif /* MethodInfo_h */
