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


TEST(doesDirectoryExistFunction, DirectoryExistsTest)
{
  std::string dir1 = "./";
  std::string dir2 = "./gtest";
  
  EXPECT_EQ(doesDirectoryExist(dir1), true);
  EXPECT_EQ(doesDirectoryExist(dir2), true);
  EXPECT_NE(doesDirectoryExist(dir1), false);
  EXPECT_NE(doesDirectoryExist(dir2), false);    
}


TEST(doesDirectoryExistFunction, DirectoryDoesntExistTest)
{
  std::string dir1 = "./idontexist";
  std::string dir2 = "./idefinitelydontexist";


  EXPECT_EQ(doesDirectoryExist(dir1), false);
  EXPECT_EQ(doesDirectoryExist(dir2), false);  
  EXPECT_NE(doesDirectoryExist(dir1), true);
  EXPECT_NE(doesDirectoryExist(dir2), true);  
}



TEST(extractProcCommFunction, ExtractCommandTest)
{
  std::unordered_map<int, ProcessInfo*> allProcessInfo;
  ProcessInfo* process;
  
  process = new ProcessInfo();
  allProcessInfo.insert(std::make_pair(1, process));
  extractProcComm(allProcessInfo, 1);

  EXPECT_EQ(allProcessInfo.at(1)->getCOMMAND(), "systemd");
  EXPECT_NE(allProcessInfo.at(1)->getCOMMAND(), "systemc");  

  delete allProcessInfo.at(1);
  allProcessInfo.erase(1);
}
