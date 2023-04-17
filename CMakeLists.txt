# check that the minimum version of cmake is 3.14
cmake_minimum_required(VERSION 3.14)

# define the project name
project(Gtest LANGUAGES CXX)

# set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# require the standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# disable the .cxx extension requirement
set(CMAKE_CXX_EXTENSIONS OFF)

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# find the gcov program to analyze results with ctest
find_program(GCOV_PATH gcov)

# locate the direcotry containinng program source files for corresponding
# CMakeLists file
add_subdirectory(src)

# enable testing for this directory and below
enable_testing()

# add directory that contains gtest test files
add_subdirectory(gtest)
