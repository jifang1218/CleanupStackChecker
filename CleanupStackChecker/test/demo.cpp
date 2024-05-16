#include "CSomeClass.h"
#include "CleanupStack.h"

using namespace Fang;

int main() {
    // positive cases
	CSomeClass *c1 = new CSomeClass();
	c1->DoSomeAction(); // ok, safe method.
    
    CleanupStack::Push(c1);
    c1->DoSomeAction(); // ok, c1 can be pushed & popped
    CleanupStack::Pop(c1);

	CleanupStack::Push(c1);
	c1->DoSomeActionL(); // ok, to invoke leavable method, we must push c1 to cleanup stack first,
	CleanupStack::Pop(c1); // pop it
    
    CleanupStack::Push(c1); // ok, to invoke leavable method, we must push c1 to cleanup stack first,
    c1->DoSomeActionL(); // no need to pop c1 as we will destroy them later.
    
    // reset above
    CleanupStack::PopAndDestroy(); // destroy all items.
    
    /*------------------------------------------------------------------------------------------------*/
	
    c1->DoSomeActionLC(); // ok, as -LC will put itself to cleanup stack first.
	CleanupStack::Pop(c1); // pop it
    
    c1->DoSomeActionLC(); // ok, again, no need to pop c1 as we will destroy them later.
    
    // reset above
    CleanupStack::PopAndDestroy(); // destroy all items, c1 is deallocated.
    
    /*------------------------------------------------------------------------------------------------*/
    
    // negative cases
    CSomeClass *c2 = new CSomeClass();
    
    c2->DoSomeActionL(); // fail, must put c2 to cleanup stack, as DoSomeActionL might fail/leave.
    
    CleanupStack::Push(c2); // fail, pushed twice, then c2 will be dealloced twice
    CleanupStack::Push(c2);
    c2->DoSomeActionL();
    CleanupStack::Pop(c2);
    
    // reset above
    CleanupStack::PopAndDestroy(); // destroy all items.
    
    /*------------------------------------------------------------------------------------------------*/
    
    CleanupStack::Push(c2); // fail, pushed twice,
    c2->DoSomeActionLC();    // as CleanupStack::Push, DoSomeActionLC do the same thing.
    //CleanupStack::Pop(c2); // we leave c2 on the stack
        
    // teardown
    // we can delete c1/c2 manually
    // or use CleanupStack::PopAndDestroy to deallocate all items if they are in cleanup stack.
    CleanupStack::PopAndDestroy(); // this will delete c2. 
    
    //delete c2;

    return 0;
}

