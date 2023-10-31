/*
  File: gtest_extractFileData.cpp
  
  Description:
  Google Unit Tests for the function implementations of the extractFileData.hpp class.
*/
#include <gtest/gtest.h>
#include "extractFileData.hpp"
#include "secondsToTime.hpp"
#include "processInfo.hpp"
#include "cpuInfo.hpp"
#include "taskInfo.hpp"


TEST(doesDirectoryExistFunction, DirectoryExists)
{
  std::string dir1 = "./";
  std::string dir2 = "./gtest";
  
  EXPECT_EQ(doesDirectoryExist(dir1), true);
  EXPECT_EQ(doesDirectoryExist(dir2), true);  
}


TEST(doesDirectoryExistFunction, DirectoryDoesntExist)
{
  std::string dir = "./idontexist";
  
  EXPECT_EQ(doesDirectoryExist(dir), false);
  EXPECT_NE(doesDirectoryExist(dir), true);
}
