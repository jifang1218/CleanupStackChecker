Q: What is this demo for?
A: This demo is used to demonstrate how to perform static analysis on source code using Clang AST.

Brief Introduction:
Clang exposes AST API for users to traverse source code. By traversing Clang AST, developers can perform various code analysis and transformation operations, such as static analysis, refactoring, syntax checking, etc. 
Clang AST provides rich APIs and tools, allowing developers to easily access and manipulate the syntax structure of source code, thereby achieving various code analysis and processing tasks.
This demo checks the usage of CleanupStack in Symbian C++ code. It records incorrect usage and outputs the results.

Prerequisites:
1. Required:
Basic C++, Visitor Pattern, and knowledge of AST.

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
1. Header file lookup failure;
2. Recognition of current file name, etc.
Usage:
CleanupStackChecker <filename>

























Q:这个demo是做什么用的? 
A:这个demo是用来展示如何使用Clang AST对源代码进行静态分析.

简述:
Clang暴露了AST api用来让用户对源代码进行traverse. 通过遍历Clang AST，开发人员可以进行各种代码分析和转换操作，例如静态分析、重构、语法检查等。Clang AST 提供了丰富的 API 和工具，使开发人员能够轻松地访问和操作源代码的语法结构，从而实现各种代码分析和处理任务。
demo检查Symbian C++代码中对CleanupStack的使用. 记录错误的使用并输出结果. 

预备知识:
1. 必须的知识
基本的C++, Visitor pattern, and AST方面的知识. 

2. 可选的知识
编译原理, token分析, 语法分析, bnf范式, CRTP(Curiously Recurring Template Pattern, Aka Static Polymophism pattern), Symbian C++. 

现在开始介绍这个demo. 
Symbian C++中的C Class和Leave Method. 
在 Symbian C++ 中有几种不同的类:
M class --> interface 
T class --> struct
R class --> resource handler
C class --> 生存在堆上的对象

C 类派生自CBase, 是一种遵循 Symbian 平台特定编程规范的类，用于开发 Symbian 平台的应用程序和系统组件。与标准的 C++ 类相比，Symbian C++中的C 类需要遵循 Symbian 平台的内存管理规则和异常处理机制，以及使用Symbian C++ 的异常处理机制来处理错误。
leave用法类似于标准C++中的throw关键字. 在类方法/实例方法中, 根据Symbian C++的Coding Convention, 以L结尾或LC结尾的method在发生错误的时候是会leave的. 在函数发生leave的时候, 系统会 处理/销毁 CleanupStack里的元素.
因此, 在调用L函数之前, 要先把对象推入CleanupStack, 运行成功之后, 从CleanupStack中弹出该对象.
比如:
CleanupStack::Push(someClass);
someClass->DoActionL(); 
CleanupStack::Pop(someClass);

L函数与LC函数的区别:
以LC结尾的函数, 在调用前用户不需要Push入CleanupStack (在LC函数实现内部已经把该对象推入CleanupStack了) 
比如:
someClass->DoActionLC();
CleanupStack::Pop(someClass);

通常LC函数这样实现:
CSomeClass::DoActionLC() {
    CleanupStack::Push(this);
    // do something
}
  
Symbian C++中的CleanupStack简介
Symbian C++ 中的CleanupStack是一种资源管理机制(轻量级异常处理机制)，用于管理局部对象的生命周期，并确保在函数退出时正确清理资源，避免内存泄漏。它通过将对象推入堆栈中管理，在函数退出时自动销毁对象。

在 Symbian C++ 中，使用 CleanupStack 需要遵循以下步骤：
将需要在函数退出时自动销毁的对象推入 CleanupStack 中。这通常通过 CleanupStack::PushL() 函数实现。
在函数退出之前，确保调用 CleanupStack::PopAndDestroy()函数来销毁对象, 或 CleanupStack::Pop()简单把对象指针弹出, 通常在函数的最后执行这个操作。
如果使用了 PushL() 函数，那么在函数退出之前需要调用相同数量的 PopAndDestroy() 或 Pop() 函数来确保正确清理资源。
CleanupStack 可以有效地管理动态分配的对象、临时对象以及需要在函数退出时(或异常发生时)进行清理的其他资源。它是 Symbian C++ 开发中常用的一种资源管理工具，有助于编写健壮和可靠的代码。

备注:
在demo中对CleanupStack做了简化, 约定:
1. CleanupStack::PushL不会leave, 因此将PushL改成Push, 即CleanupStack::Push(someClass); 
2. CleanupStack::PopAndDestroy()会销毁所有CleanupStack中的元素;
3. 约定CleanupStack中不可以多次Push/Pop同一个对象, 也就是说, CleanupStack中不可以保存重复的对象. 
具体用法请参考demo.cpp


demo的结构:
以CheckCleanupStackAction作为入口, 从命令行读取源文件, 通过CheckCleanupStackConsumer中的checker(CallExprHandler)traverse AST, 并通过ErrorMgr收集源码中的错误. 
demo为解释如何通过分析AST结点, 并没有使用现存的matcher, 而手动实现的matcher功能. 

备注:
并没有配置Clang AST的compilation database, 但不影响展示如何遍历AST结点. 
这些可能的问题包括:
1. 头文件查找路径;
2. 当前文件名的识别等等. 

使用方法:
CleanupStackChecker <filename>
