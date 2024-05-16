#include "CleanupStack.h"
#include "CBase.h"

namespace Fang {

using namespace std;

void CleanupStack::Push(CBase *pCObj) {
    CleanupStack::_objs.push(pCObj);
}

CBase *CleanupStack::Pop(CBase *pCObj) {
    CBase *ret = nullptr;
    
    ret = CleanupStack::_objs.top();
    CleanupStack::_objs.pop();

	return ret;
}

void CleanupStack::PopAndDestroy() {
    for (CBase *_obj : _objs) {
        delete _obj;
    }
    
    _objs.clear();

} // Fang

