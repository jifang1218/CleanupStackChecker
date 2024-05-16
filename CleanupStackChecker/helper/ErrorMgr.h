//
//  ErrorMgr.hpp
//  CleanupStackChecker
//
//  Created by jifang on 2024-05-15.
//

#ifndef ErrorMgr_h
#define ErrorMgr_h

#include "MethodInfo.h"
#include <string>
#include <utility>
#include <vector>
#include <mutex>

namespace Fang {

class ErrorMgr {
public:
    static ErrorMgr &getInstance() {
        if (!instance) {
            std::lock_guard<std::mutex> lock(mutex);
            if (!instance) {
                instance = new ErrorMgr();
            }
        }
        return *instance;
    }

    ErrorMgr(const ErrorMgr&) = delete;
    ErrorMgr &operator=(const ErrorMgr&) = delete;
    
public:
    void Output() const;
    void Add(const MethodInfo &methodInfo, const std::string &message);
    
private:
    ErrorMgr() {}
    ~ErrorMgr() {}
    
private:
    static ErrorMgr *instance;
    static std::mutex mutex;
    
    std::vector<std::pair<MethodInfo, std::string>> errors;
};

} // Fang

#endif /* ErrorMgr_h */
