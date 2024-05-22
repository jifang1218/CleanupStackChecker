cmake_minimum_required(VERSION 3.20)
project(CleanupStackChecker)

set(CLANG_ROOT "/usr/local/clang")
set(CLANG_CFG_ROOT "${CLANG_ROOT}/lib/cmake")

# set module search path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CLANG_CFG_ROOT}/clang/;${CLANG_CFG_ROOT}/llvm/")

# include clang and llvm
include(AddClang)
include(AddLLVM)

set(LLVM_DIR "${CLANG_CFG_ROOT}/llvm")


# load llvm module
find_package(LLVM REQUIRED CONFIG)
#message("jifang===== ${LLVM_AVAILABLE_LIBS}")

# -I and -L
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    execute_process(
        COMMAND xcrun --show-sdk-path
        OUTPUT_VARIABLE SDK_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
	add_compile_options(-isysroot ${SDK_PATH})
	add_compile_options(-fno-rtti -stdlib=libc++)
endif()

add_compile_options(-std=c++17)

add_clang_executable(
	CleanupStackChecker 
	CleanupStackChecker/CheckCleanupStackAction.cpp 
	CleanupStackChecker/CheckCleanupStackConsumer.cpp
	CleanupStackChecker/main.cpp
	CleanupStackChecker/helper/ErrorMgr.cpp 
	CleanupStackChecker/helper/MethodUtils.cpp
	CleanupStackChecker/matchers/CallExprHandler.cpp
)

# -l
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


