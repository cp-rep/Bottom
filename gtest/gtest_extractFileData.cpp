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



TEST(removeDeadProcessesFunction, DeleteDeadProcessesTest)
{
  std::unordered_map<int, ProcessInfo*> allProcessInfo;
  ProcessInfo* process1 = new ProcessInfo();
  ProcessInfo* process2 = new ProcessInfo();
  ProcessInfo* process3 = new ProcessInfo();
  std::vector<int> pids;

  pids.push_back(1);
  pids.push_back(2);
  pids.push_back(3);  

  allProcessInfo.insert(std::make_pair(pids.at(0), process1));
  allProcessInfo.insert(std::make_pair(pids.at(1), process2));
  allProcessInfo.insert(std::make_pair(pids.at(2), process3));

  EXPECT_EQ(allProcessInfo.size(), 3);
  EXPECT_NE(allProcessInfo.at(pids.at(0)), nullptr);
  EXPECT_NE(allProcessInfo.at(pids.at(1)), nullptr);
  EXPECT_NE(allProcessInfo.at(pids.at(2)), nullptr);

  removeDeadProcesses(allProcessInfo, pids);

  EXPECT_EQ(allProcessInfo.size(), 0);
}



TEST(returnPhraseLineFunction, ReturnPhraseTest)
{
  const std::string filePath = "./gtest/meminfo.txt";  
  const std::string fileDoesntExist = "file.file";
  const std::string phrase = "SwapCached";
  const std::string fileLine = "SwapCached:            0 kB";
  const std::string notInFile = "-2";
  
  EXPECT_EQ(returnPhraseLine(filePath, "phrase doesn't exist"), notInFile);
  EXPECT_EQ(returnPhraseLine(filePath, phrase), fileLine);
  EXPECT_EQ(returnPhraseLine(fileDoesntExist, phrase), "-1");

  EXPECT_NE(returnPhraseLine(filePath, "phrase doesn't exist"), "-1");
  EXPECT_NE(returnPhraseLine(filePath, "phrase doesn't exist"), fileLine);
  EXPECT_NE(returnPhraseLine(fileDoesntExist, phrase), fileLine);
}
