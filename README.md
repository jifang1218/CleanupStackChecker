Q: What is this demo for?  
A: This demo is used to demonstrate how to perform static analysis on source code using Clang AST.  
  
Brief Introduction:  
Clang exposes AST API for users to traverse source code. By traversing Clang AST, developers can perform various code analysis and transformation operations, such as static analysis, refactoring, syntax checking, etc.   
Clang AST provides rich APIs and tools, allowing developers to easily access and manipulate the syntax structure of source code, thereby achieving various code analysis and processing tasks.  
This demo checks the usage of CleanupStack in Symbian C++ code. It records incorrect usage and outputs the results.  
  
Prerequisites:  
1. Required:  
Basic C++, Visitor Pattern, and AST.  
2. Optional:  
Compiler theory, token analysis, syntax analysis, BNF expression, CRTP (Curiously Recurring Template Pattern, also known as Static Polymorphism Pattern), Symbian C++.  
  
Now let's start introducing this demo.  
  
C Class and Leave Method in Symbian C++:  
In Symbian C++, there are several types of classes:  
M class --> interface  
T class --> struct  
R class --> resource handler  
C class --> objects residing on the heap  
  
C classes derive from CBase(CBase is flat) and are classes that adhere to Symbian platform-specific programming specifications, used to develop applications and system components for the Symbian platform.   
Compared to standard C++ classes, C classes in Symbian C++ need to follow the memory management rules and exception handling mechanisms of the Symbian platform, as well as using the exception handling mechanism of Symbian C++ to handle errors.  
  
The usage of leave is similar to the throw keyword in standard C++. According to the Symbian C++ Coding Convention, methods ending with L or LC will leave when an error occurs. When leave occurs in a function, the system will handle/destroy elements in the CleanupStack.  
Therefore, before calling L functions, the object needs to be pushed onto the CleanupStack, and after successful execution, the object is popped from the CleanupStack.  
For example:  
CleanupStack::Push(someClass);  
someClass->DoActionL();  
CleanupStack::Pop(someClass);  
  
Difference between L and LC functions:  
Functions ending with LC do not require the user to Push into the CleanupStack before calling (the object is pushed into the CleanupStack internally within the LC function).  
For example:  
someClass->DoActionLC();  
CleanupStack::Pop(someClass);  
  
Usually, LC functions are implemented like this:  
CSomeClass::DoActionLC() {  
    CleanupStack::Push(this);  
    // do something  
}  
  
Introduction to CleanupStack in Symbian C++  
CleanupStack in Symbian C++ is a resource management mechanism (lightweight exception handling mechanism) used to manage the lifecycle of local objects and ensure proper cleanup of resources when functions exit, avoiding memory leaks.   
It manages objects by pushing them onto the stack for management and automatically destroying them when the function exits.  
  
In Symbian C++, using the CleanupStack requires the following steps:  
Push the objects that need to be automatically destroyed when the function exits onto the CleanupStack. This is usually done using the CleanupStack::PushL() function.  
Before the function exits, make sure to call the CleanupStack::PopAndDestroy() function to destroy the objects, or simply call CleanupStack::Pop() to pop the object pointer. This is typically done at the end of the function.  
If the PushL() function is used, the same number of PopAndDestroy() or Pop() functions need to be called before the function exits to ensure proper cleanup of resources.  
The CleanupStack can effectively manage dynamically allocated objects, temporary objects, and other resources that need to be cleaned up when functions exit (or when exceptions occur).   
It is a commonly used resource management tool in Symbian C++ development, helping to write robust and reliable code.  
  
Note:  
CleanupStack has been simplified in the demo, with the following conventions:  
1. CleanupStack::PushL does not leave, so PushL is changed to Push, i.e., CleanupStack::Push(someClass);  
2. CleanupStack::PopAndDestroy() will destroy all elements in the CleanupStack;  
3. It is agreed that duplicate objects cannot be pushed/popped into/from the CleanupStack, i.e., the CleanupStack cannot contain duplicate objects.  
Please refer to demo.cpp for the usage.  
  
Demo Structure:  
Using CheckCleanupStackAction as the entry point, read the source file from the command line, traverse the AST through the checker (CallExprHandler) in CheckCleanupStackConsumer, and collect errors in the source code through ErrorMgr.  
The demo explains how to traverse AST nodes, and does not use existing matchers but implements matcher functionality manually.  
  
Note:  
The compilation database for Clang AST is not configured, but it does not affect the demonstration of how to traverse AST nodes.  
These possible issues include:  
1. System header file lookup failure;  
2. Recognition of current file name, etc.  
     
Usage:  
CleanupStackChecker   filename  
  
