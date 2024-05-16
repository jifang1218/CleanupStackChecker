project(CleanupStackChecker)

cmake_minimum_required(VERSION 3.20)

set(CLANG_ROOT "/usr/local/clang-18.1.4")
set(CLANG_CFG_ROOT "${CLANG_ROOT}/lib/cmake")
#message("jifang======== ${CLANG_ROOT}")
#message("jifang======== ${CLANG_CFG_ROOT}")

# set module search path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CLANG_CFG_ROOT}/clang/;${CLANG_CFG_ROOT}/llvm/")

# include clang and llvm
include(AddClang)
include(AddLLVM)

#if(0)
set(LLVM_LINK_COMPONENTS
  Support
  )
#endif

execute_process(
    COMMAND which clang
    OUTPUT_VARIABLE CLANG_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND which clang++
    OUTPUT_VARIABLE CLANGXX_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(CMAKE_C_COMPILER ${CLANG_PATH})
set(CMAKE_CXX_COMPILER ${CLANGXX_PATH})

set(LLVM_DIR "${CLANG_CFG_ROOT}/llvm")
#message("jifang=========== ${LLVM_DIR}")


#message("jifang=========== ${CMAKE_SYSTEM_NAME}")

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    execute_process(
        COMMAND xcrun --show-sdk-path
        OUTPUT_VARIABLE SDK_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
	#message("jifang=====mac, ${SDK_PATH}")
endif()

# load llvm module
find_package(LLVM REQUIRED CONFIG)
#message("jifang===== ${LLVM_INCLUDE_DIRS}")
#message("jifang===== ${LLVM_LIBRARY_DIRS}")
message("jifang===== ${LLVM_AVAILABLE_LIBS}")

# -I and -L
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_compile_options(-isysroot ${SDK_PATH})
endif()

add_compile_options(-fno-rtti -std=c++17 -stdlib=libc++)

add_clang_executable(
	CleanupStackChecker 
	CleanupStackChecker/CheckCleanupStackAction.cpp 
	CleanupStackChecker/CheckCleanupStackConsumer.cpp
	CleanupStackChecker/main.cpp
	CleanupStackChecker/helper/ErrorMgr.cpp 
	CleanupStackChecker/helper/MethodUtils.cpp
	CleanupStackChecker/matchers/CallExprHandler.cpp
)

#target_link_libraries(test ${LLVM_AVAILABLE_LIBS}
target_link_libraries(CleanupStackChecker 
  PRIVATE
  clangAST
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  LLVMSupport
  clangASTMatchers
  LLVMFrontendOpenMP
)


