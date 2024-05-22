#ifndef CLEANUPSTACK_H_
#define CLEANUPSTACK_H_

#include <stack>

namespace Fang {

class CBase;

/**
 Simulate the Symbian's Exception handling component. 
 */
class CleanupStack {
public:
    static void Push(CBase *pCObj);
    static CBase *Pop(CBase *pCObj);
    static void PopAndDestroy();

private:
    static std::stack<CBase *> _objs;
};

} // Fang

#endif // CLEANUPSTACK_H_
 
