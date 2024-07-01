cmake_minimum_required(VERSION 3.20)

set(PROJ_NAME CleanupStackChecker)
project(${PROJ_NAME} VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# *.cpp, *.h
file(GLOB_RECURSE SOURCES "*.cpp" "*.h")
# exclude temporary files in CMakeFiles directory.
list(FILTER SOURCES EXCLUDE REGEX "/CMakeFiles/")
list(FILTER SOURCES EXCLUDE REGEX "/CleanupStackChecker\\/test/")

set(CLANG_CFG_ROOT "/usr/local/clang/lib/cmake")

# set module search path
list(APPEND CMAKE_PREFIX_PATH ${CLANG_CFG_ROOT}/clang ${CLANG_CFG_ROOT}/llvm)
list(APPEND CMAKE_MODULE_PATH ${CLANG_CFG_ROOT}/clang ${CLANG_CFG_ROOT}/llvm)

# include clang and llvm
include(AddClang)
include(AddLLVM)

# load llvm module
find_package(LLVM REQUIRED CONFIG)
find_package(CLANG REQUIRED CONFIG)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    execute_process(
        COMMAND xcrun --show-sdk-path
        OUTPUT_VARIABLE SDK_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
	add_compile_options(-isysroot ${SDK_PATH})
	add_compile_options(-fno-rtti -stdlib=libc++)
endif()


add_clang_executable(
	${PROJ_NAME}
	${SOURCES}
)

target_include_directories(${PROJ_NAME}
	PRIVATE
	${LLVM_INCLUDE_DIRS}
	${CLANG_INCLUDE_DIRS}
)

target_link_directories(${PROJ_NAME} 
	PRIVATE
	${CLANG_LIBRARY_DIRS}
	${LLVM_LIBRARY_DIRS}
)

# -l
target_link_libraries(${PROJ_NAME}
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

