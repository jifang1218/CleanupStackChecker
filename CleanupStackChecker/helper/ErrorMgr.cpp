//
//  ErrorMgr.cpp
//  CleanupStackChecker
//
//  Created by jifang on 2024-05-15.
//

#include "ErrorMgr.h"
#include <string>
#include <iostream>

namespace Fang {

using namespace std;

ErrorMgr* ErrorMgr::instance = nullptr;
std::mutex ErrorMgr::mutex;

void ErrorMgr::Output() const {
    for (const auto &err : errors) {
        cout << "At file: " + err.first.filePath
        << ", line " << err.first.lineNum
        << + " " + err.first.sender
        << "::" + err.first.message + " : "
        << err.second
        << endl;
    }
}

void ErrorMgr::Add(const MethodInfo &methodInfo, const std::string &message) {
    pair<MethodInfo, string> item(methodInfo, message);
    errors.push_back(item);
}

} // Fang
