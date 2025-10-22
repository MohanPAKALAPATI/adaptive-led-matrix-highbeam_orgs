cmake_minimum_required(VERSION 3.10)

project(AdaptiveLEDMatrixHighbeam VERSION 1.0.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Options
option(BUILD_ARDUINO "Build Arduino LED Controller" OFF)
option(BUILD_PYTHON "Build Python vehicle detection module" ON)
option(BUILD_EXAMPLES "Build example applications" ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add subdirectories
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Information message
message(STATUS "")
message(STATUS "====================================")
message(STATUS "Adaptive LED Matrix High Beam Build")
message(STATUS "====================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Arduino: ${BUILD_ARDUINO}")
message(STATUS "Build Python: ${BUILD_PYTHON}")
message(STATUS "Build Examples: ${BUILD_EXAMPLES}")
message(STATUS "====================================")
message(STATUS "")

# Installation
install(FILES README.md DESTINATION share/doc/adaptive-led-highbeam)
