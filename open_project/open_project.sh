#!/bin/bash

emacs -nw ./CMakeLists.txt ./makefile ./gtest/CMakeLists.txt ./gtest/*.cpp ./lib/*.hpp ./src/CMakeLists.txt ./src/*.cpp
