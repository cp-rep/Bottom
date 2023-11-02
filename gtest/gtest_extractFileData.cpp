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
  std::string dir3 = "./notADirectory";  

  // directory exists
  EXPECT_EQ(doesDirectoryExist(dir1), true);
  EXPECT_EQ(doesDirectoryExist(dir2), true);
  EXPECT_NE(doesDirectoryExist(dir1), false);
  EXPECT_NE(doesDirectoryExist(dir2), false);      
}



TEST(doesDirectoryExistFunction, DirectoryDoesntExistTest)
{
  std::string dir1 = "./idontexist";
  std::string dir2 = "./idefinitelydontexist";

  // directory doesn't exist
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

  // command exists (read from PID 1)
  EXPECT_EQ(allProcessInfo.at(1)->getCOMMAND(), "systemd");

  // command doesn't exist
  EXPECT_NE(allProcessInfo.at(1)->getCOMMAND(), "systemc");  

  // list shouldn't be empty
  EXPECT_EQ(allProcessInfo.size(), 1);
  
  delete allProcessInfo.at(1);
  allProcessInfo.erase(1);

  // list should be empty
  EXPECT_EQ(allProcessInfo.size(), 0);
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

  // list should hold 3 elements
  EXPECT_EQ(allProcessInfo.size(), 3);

  // each value should point to something
  EXPECT_NE(allProcessInfo.at(pids.at(0)), nullptr);
  EXPECT_NE(allProcessInfo.at(pids.at(1)), nullptr);
  EXPECT_NE(allProcessInfo.at(pids.at(2)), nullptr);

  removeDeadProcesses(allProcessInfo, pids);

  // list should be empty
  EXPECT_EQ(allProcessInfo.size(), 0);
}



TEST(returnPhraseLineFunction, ReturnPhraseTest)
{
  const std::string filePath = "./gtest/meminfo.txt";  
  const std::string fileDoesntExist = "file.file";
  const std::string phrase = "SwapCached";
  const std::string fileLine = "SwapCached:            0 kB";
  const std::string notInFile = "-2";

  // string phrase doesn't exist
  EXPECT_EQ(returnPhraseLine(filePath, "phrase doesn't exist"), notInFile);

  // string phrase should exist
  EXPECT_EQ(returnPhraseLine(filePath, phrase), fileLine);

  // the file should not exist and therefore return "-1"
  EXPECT_EQ(returnPhraseLine(fileDoesntExist, phrase), "-1");

  // the filePath should not exist and phrase not exist
  EXPECT_NE(returnPhraseLine(filePath, "phrase doesn't exist"), "-1");

  // the filePath should exist but phrase not exist
  EXPECT_NE(returnPhraseLine(filePath, "phrase doesn't exist"), fileLine);

  // the file does not exist and we should not get back the fileLine
  EXPECT_NE(returnPhraseLine(fileDoesntExist, phrase), fileLine);
}



TEST(makeDirectoryFunction, MakeDirectoryTest)
{
  const std::string dirPath = "./testDirectory";
  bool directoryMade;

  // create directory case
  if(doesDirectoryExist(dirPath) == false)
    {
      directoryMade = makeDirectory(dirPath);
      EXPECT_EQ(directoryMade, true);
    }
  // directory already exists case
  else
    {
      directoryMade = makeDirectory(dirPath);
      EXPECT_EQ(directoryMade, false);      
    }
}



TEST(extractProcessStateCountFunction, ExtractCountsTest)
{
  TaskInfo taskInfo;
  std::unordered_map<int, ProcessInfo*> allProcessInfo;
  ProcessInfo* process1 = new ProcessInfo();
  ProcessInfo* process2 = new ProcessInfo();
  ProcessInfo* process3 = new ProcessInfo();
  ProcessInfo* process4 = new ProcessInfo();
  ProcessInfo* process5 = new ProcessInfo();
  ProcessInfo* process6 = new ProcessInfo();
  ProcessInfo* process7 = new ProcessInfo();
  ProcessInfo* process8 = new ProcessInfo();
  ProcessInfo* process9 = new ProcessInfo();  
  std::vector<int> pids;

  pids.push_back(1);
  pids.push_back(2);
  pids.push_back(3);
  pids.push_back(4);
  pids.push_back(5);
  pids.push_back(6);
  pids.push_back(7);
  pids.push_back(8);
  pids.push_back(9);  
  allProcessInfo.insert(std::make_pair(pids.at(0), process1));
  allProcessInfo.insert(std::make_pair(pids.at(1), process2));
  allProcessInfo.insert(std::make_pair(pids.at(2), process3));
  allProcessInfo.insert(std::make_pair(pids.at(3), process4));
  allProcessInfo.insert(std::make_pair(pids.at(4), process5));
  allProcessInfo.insert(std::make_pair(pids.at(5), process6));
  allProcessInfo.insert(std::make_pair(pids.at(6), process7));
  allProcessInfo.insert(std::make_pair(pids.at(7), process8));
  allProcessInfo.insert(std::make_pair(pids.at(8), process9));

  // set the values
  allProcessInfo.at(pids.at(0))->setS('S');
  allProcessInfo.at(pids.at(1))->setS('S');
  allProcessInfo.at(pids.at(2))->setS('I');
  allProcessInfo.at(pids.at(3))->setS('T');
  allProcessInfo.at(pids.at(4))->setS('D');
  allProcessInfo.at(pids.at(5))->setS('R');  
  allProcessInfo.at(pids.at(6))->setS('Z');
  allProcessInfo.at(pids.at(7))->setS('Z');  
  allProcessInfo.at(pids.at(8))->setS('Z');

  // check values set properly
  EXPECT_EQ(allProcessInfo.at(pids.at(0))->getS(), 'S');
  EXPECT_EQ(allProcessInfo.at(pids.at(1))->getS(), 'S');
  EXPECT_EQ(allProcessInfo.at(pids.at(2))->getS(), 'I');
  EXPECT_EQ(allProcessInfo.at(pids.at(3))->getS(), 'T');
  EXPECT_EQ(allProcessInfo.at(pids.at(4))->getS(), 'D');
  EXPECT_EQ(allProcessInfo.at(pids.at(5))->getS(), 'R');
  EXPECT_EQ(allProcessInfo.at(pids.at(6))->getS(), 'Z');
  EXPECT_EQ(allProcessInfo.at(pids.at(7))->getS(), 'Z');
  EXPECT_EQ(allProcessInfo.at(pids.at(8))->getS(), 'Z');

  // call the function
  extractProcessStateCount(allProcessInfo, taskInfo);

  // test the results were properly tallied and calculated  in
  // the TaskInfo object
  EXPECT_EQ(taskInfo.getInSleep(), 2);
  EXPECT_EQ(taskInfo.getIdle(), 1);
  EXPECT_EQ(taskInfo.getStopped(), 1);
  EXPECT_EQ(taskInfo.getUnSleep(), 1);  
  EXPECT_EQ(taskInfo.getRunning(), 1);
  EXPECT_EQ(taskInfo.getZombie(), 3);
  EXPECT_EQ(taskInfo.getSleeping(), 4);
  EXPECT_EQ(taskInfo.getTotal(), 5);

  // test processes allocated correctly
  EXPECT_EQ(allProcessInfo.size(), 9);
  
  // clean up
  removeDeadProcesses(allProcessInfo, pids);

  // test they cleaned up
  EXPECT_EQ(allProcessInfo.size(), 0);
}



TEST(extractProcStatDataFunction, ExtractProcStatDataTest)
{
  CPUInfo cpuInfo;
  std::string filePath = "./gtest/stat.txt";

  // extract the data from the file path
  extractProcStatData(cpuInfo, filePath);

  // test the values were extracted correctly
  EXPECT_EQ(cpuInfo.getUs(), 11429);
  EXPECT_EQ(cpuInfo.getNi(), 159);
  EXPECT_EQ(cpuInfo.getSy(), 4336);
  EXPECT_EQ(cpuInfo.getId(), 2230907);
  EXPECT_EQ(cpuInfo.getWa(), 828);
  EXPECT_EQ(cpuInfo.getIrq(), 2057);  
  EXPECT_EQ(cpuInfo.getSirq(), 1780);  
  EXPECT_EQ(cpuInfo.getSt(), 0);
  EXPECT_EQ(cpuInfo.getGu(), 1);
  EXPECT_EQ(cpuInfo.getGun(), 2);
  EXPECT_EQ(cpuInfo.getJiffs(), 2251499);  
}
