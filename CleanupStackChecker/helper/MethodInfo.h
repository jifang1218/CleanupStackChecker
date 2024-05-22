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
    // for static method, it is class name
    // for instance method, it is instance name
    std::string sender;
    
    // method name
    std::string message;
    
    // file info
    unsigned int lineNum = -1;
    unsigned int colNum = -1;
    std::string filePath;
    
    // the 1st parameter of a method(if the method has 1 or more parameters)
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
