cmake_minimum_required(VERSION 3.5)

project("modern-cpp")

set(CMAKE_C_COMPILER /opt/homebrew/opt/llvm/bin/clang CACHE STRING "Clang compiler") 
set(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm/bin/clang++ CACHE STRING "Clang++ compiler")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Generate compile commands")

set(CMAKE_CXX_STANDARD 23 CACHE STRING "C++ standard to conform to")

find_package(LLVM REQUIRED CONFIG)
find_package(MLIR REQUIRED CONFIG)

message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/bin CACHE PATH "Directory for runtime executables")
set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/lib CACHE PATH "Directory for runtime libraries")
set(MLIR_BINARY_DIR ${CMAKE_BINARY_DIR} CACHE PATH "MLIR build directory")

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
# include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})

link_directories(${LLVM_BUILD_LIBRARY_DIR})
add_definitions(${LLVM_DEFINITIONS})

get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
# set(CMAKE_VERBOSE_MAKEFILE ON)
# Add all Cpp files from the Chapters directory
file(GLOB_RECURSE FEDERICO_FILES FedericoBusato/*.cpp)
add_executable(modernCpp modernCpp.cpp ${FEDERICO_FILES}) 

# target_include_directories(modernCpp PRIVATE FedericoBusato)
# target_sources(modernCpp PRIVATE ${FEDERICO_FILES})
# target_compile_definitions(modernCpp PRIVATE ${LLVM_DEFINITIONS_LIST})
## add_compile_optionsmake(-fmodules-ts -x c++-system-header iostream)
# target_compile_options(modernCpp PRIVATE -fmodules-ts -x c++-system-header iostream)
# target_link_libraries(modernCpp PRIVATE MLIRIR MLIRParser MLIRPass MLIRTransforms MLIRSupport MLIRStandardToLLVM)
# target_link_options(modernCpp PRIVATE -fmodules-ts -x c++-system-header iostream)