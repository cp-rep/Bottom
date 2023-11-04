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

TEST(doesDirectoryExist_FUNCTION, directoryExists_TEST)
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



TEST(doesDirectoryExistFunction, directoryDoesntExist_TEST)
{
  std::string dir1 = "./idontexist";
  std::string dir2 = "./idefinitelydontexist";

  // directory doesn't exist
  EXPECT_EQ(doesDirectoryExist(dir1), false);
  EXPECT_EQ(doesDirectoryExist(dir2), false);  
  EXPECT_NE(doesDirectoryExist(dir1), true);
  EXPECT_NE(doesDirectoryExist(dir2), true);
}



TEST(extractProcComm_FUNCTION, extractCommand_TEST)
{
  std::unordered_map<int, ProcessInfo*> allProcessInfo;
  ProcessInfo* process;
  std::string filePath;

  filePath = _PROC;
  filePath.append("1");
  filePath.append(_COMM);	
  process = new ProcessInfo();
  allProcessInfo.insert(std::make_pair(1, process));
  extractProcPidComm(allProcessInfo, 1, filePath);

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



TEST(removeDeadProcesses_FUNCTION, deleteDeadProcesses_TEST)
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



TEST(returnPhraseLine_FUNCTION, returnPhrase_TEST)
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



TEST(makeDirectory_FUNCTION, makeDirectory_TEST)
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



TEST(countProcessStates_FUNCTION, countStates_TEST)
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
  countProcessStates(allProcessInfo, taskInfo);

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



TEST(extractProcUptime_FUNCTION, extractProcUptime_TEST)
{
  SecondsToTime uptime;
  const std::string uptimePath = "./gtest/proc_uptime.txt";
  std::vector<std::string> uptimeStrings;

  extractProcUptime(uptime,
		    uptimeStrings,		    
		    uptimePath);

  // test that the uptime values were extracted correctly
  EXPECT_EQ(uptimeStrings.at(0), "9360.26");
  EXPECT_NE(uptimeStrings.at(0), "9360.27");
  EXPECT_NE(uptimeStrings.at(0), "");
  EXPECT_EQ(uptimeStrings.at(1), "27505.65");
  EXPECT_NE(uptimeStrings.at(1), "27505.66");
  EXPECT_NE(uptimeStrings.at(1), "");
}



TEST(extractProcLoadavg_FUNCTION, extractProcLoadavg_TEST)
{
  
  std::vector<std::string> loadavgStrings;
  std::string loadavgPath = "./gtest/proc_loadavg.txt";

  extractProcLoadavg(loadavgStrings,
		     loadavgPath);

  // test that values were parsed and extracted correctly
  EXPECT_EQ(loadavgStrings.at(0), "0.02");
  EXPECT_NE(loadavgStrings.at(0), "0.03");
  EXPECT_NE(loadavgStrings.at(0), "");
  EXPECT_EQ(loadavgStrings.at(1), "0.06");
  EXPECT_NE(loadavgStrings.at(1), "0.07");
  EXPECT_NE(loadavgStrings.at(1), "");
  EXPECT_EQ(loadavgStrings.at(2), "0.02");
  EXPECT_NE(loadavgStrings.at(2), "0.03");
  EXPECT_NE(loadavgStrings.at(2), "");
  EXPECT_EQ(loadavgStrings.at(3), "1/129");
  EXPECT_NE(loadavgStrings.at(3), "1/128");
  EXPECT_NE(loadavgStrings.at(3), "");
  EXPECT_EQ(loadavgStrings.at(4), "8951");
  EXPECT_NE(loadavgStrings.at(4), "8952");
  EXPECT_NE(loadavgStrings.at(4), "");    

}



TEST(extractProcStat_FUNCTION, extractProcStat_TEST)
{
  CPUInfo cpuInfo;
  std::string filePath = "./gtest/proc_stat.txt";

  // extract the data from the file path
  extractProcStat(cpuInfo, filePath);

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



TEST(extractProcPidStatus_FUNCTION, extractProcPidStatus_TEST)
{
  std::unordered_map<int, ProcessInfo*> allProcessInfo;
  std::string filePath = "./gtest/proc_pid_status.txt";
  ProcessInfo* process;

  process = new ProcessInfo();
  allProcessInfo.insert(std::make_pair(1, process));

  extractProcPidStatus(allProcessInfo,
		       1,
		       filePath);

  // check that the user was extracted correctly
  EXPECT_EQ(allProcessInfo.at(1)->getUSER(), "root");
  EXPECT_NE(allProcessInfo.at(1)->getUSER(), "rooty");
  EXPECT_NE(allProcessInfo.at(1)->getUSER(), "");

  // check that the virtual memory was extracted correctly
  EXPECT_EQ(allProcessInfo.at(1)->getVIRT(), 21312);
  EXPECT_NE(allProcessInfo.at(1)->getVIRT(), 21313);

  // check that the reserved memory was extracted correctly
  EXPECT_EQ(allProcessInfo.at(1)->getRES(), 13000);
  EXPECT_NE(allProcessInfo.at(1)->getRES(), 13001);

  // check that the shared memory was extracted correctly
  EXPECT_EQ(allProcessInfo.at(1)->getSHR(), 10208);
  EXPECT_NE(allProcessInfo.at(1)->getSHR(), 10209);

  // test processes allocated correctly
  EXPECT_EQ(allProcessInfo.size(), 1);

  std::vector<int> pids;
  pids.push_back(1);
  
  // clean up
  removeDeadProcesses(allProcessInfo, pids);

  // test they cleaned up
  EXPECT_EQ(allProcessInfo.size(), 0);
}



TEST(extractProcPidStat_FUNCTION, extractProcPidStat_TEST)
{
  std::unordered_map<int, ProcessInfo*> allProcessInfo;
  ProcessInfo* process;
  MemInfo memInfo;
  SecondsToTime uptime;
  std::vector<std::string> uptimeStrings;
  const std::string uptimePath = "./gtest/proc_uptime.txt";
  const std::string statPath = "./gtest/proc_pid_stat.txt";  
  
  extractProcUptime(uptime,
		    uptimeStrings,
		    uptimePath);
  process = new ProcessInfo();
  allProcessInfo.insert(std::make_pair(1, process));
  extractProcPidStat(allProcessInfo,
		     memInfo,
		     uptime,
		     1,
		     uptimeStrings,
		     statPath);

  EXPECT_EQ(allProcessInfo.at(1)->getPR(), 20);
  EXPECT_EQ(allProcessInfo.at(1)->getNI(), 0);
  EXPECT_EQ(allProcessInfo.at(1)->getS(), 'S');
  EXPECT_EQ(allProcessInfo.at(1)->getCPUUsage(), 0);
  EXPECT_EQ(allProcessInfo.at(1)->getCpuRawTime(), 9 + 53);

  // test processes allocated correctly
  EXPECT_EQ(allProcessInfo.size(), 1);
  
  std::vector<int> pids;
  pids.push_back(1);
  
  // clean up
  removeDeadProcesses(allProcessInfo, pids);

  // test they cleaned up
  EXPECT_EQ(allProcessInfo.size(), 0);
}



TEST(extractProcMeminfo_FUNCTION, extractProcMeminfo_TEST)
{
  MemInfo memInfo;
  const std::string memInfoPath = "./gtest/proc_meminfo.txt";


  extractProcMeminfo(memInfo,
		     memInfoPath);

  // test that meminfo valus were successfully extracted
  EXPECT_EQ(memInfo.getMemTotal(), 8123912);
  EXPECT_NE(memInfo.getMemTotal(), 8123913);
  EXPECT_NE(memInfo.getMemTotal(), 0);    
  EXPECT_EQ(memInfo.getMemFree(), 7435484);
  EXPECT_NE(memInfo.getMemFree(), 7435485);
  EXPECT_NE(memInfo.getMemFree(), 0);  
  EXPECT_EQ(memInfo.getMemAvailable(), 7641304);
  EXPECT_NE(memInfo.getMemAvailable(), 7641305);
  EXPECT_NE(memInfo.getMemAvailable(), 0);  
  EXPECT_EQ(memInfo.getBuffers(), 31408);
  EXPECT_NE(memInfo.getBuffers(), 31409);
  EXPECT_NE(memInfo.getBuffers(), 0);  
  EXPECT_EQ(memInfo.getCached(), 381092);
  EXPECT_NE(memInfo.getCached(), 381093);
  EXPECT_NE(memInfo.getCached(), 0);    
  EXPECT_EQ(memInfo.getSwapTotal(), 4194300);
  EXPECT_NE(memInfo.getSwapTotal(), 4194301);
  EXPECT_NE(memInfo.getSwapTotal(), 0);  
  EXPECT_EQ(memInfo.getSwapFree(), 4194300);
  EXPECT_NE(memInfo.getSwapFree(), 4194301);
  EXPECT_NE(memInfo.getSwapFree(), 0);
  EXPECT_EQ(memInfo.getSReclaimable(), 25952);
  EXPECT_NE(memInfo.getSReclaimable(), 25953);  
  EXPECT_NE(memInfo.getSReclaimable(), 0);          
}



TEST(findDeadProcesses_FUNCTION, findDeadProcesses_TEST)
{
  std::vector<int> pids = { 3, 4, 5, 7, 10, 11 };
  std::vector<int> pidsOld = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  std::vector<int> pidsDead;
  std::vector<int> pidsDeadResult = {1, 2, 6, 8, 9, 12};
  bool foundDead;

  // case first died, middle died, end died
  foundDead = findDeadProcesses(pids,
				pidsOld,
				pidsDead);
  EXPECT_EQ(foundDead, true);
  EXPECT_EQ(pidsDead, pidsDeadResult);
  
  pids.clear();
  pidsOld.clear();
  pidsDead.clear();
  pidsDeadResult.clear();

  // case no deaths
  pids = { 1, 2};
  pidsOld = { 1, 2};
  foundDead = findDeadProcesses(pids,
				pidsOld,
				pidsDead);
  EXPECT_EQ(foundDead, false);
  EXPECT_EQ(pidsDead, pidsDeadResult);

  pids.clear();
  pidsOld.clear();
  pidsDead.clear();
  pidsDeadResult.clear();

  // case no processes (technically impossible but sanity)
  foundDead = findDeadProcesses(pids,
				pidsOld,
				pidsDead);
  EXPECT_EQ(foundDead, false);
  EXPECT_EQ(pidsDead, pidsDeadResult);

  pids.clear();
  pidsOld.clear();
  pidsDead.clear();
  pidsDeadResult.clear();
  
  // case first loop, no old pids
  pids = { 3, 4, 5, 7, 10, 11 };
  foundDead = findDeadProcesses(pids,
				pidsOld,
				pidsDead);
  EXPECT_EQ(foundDead, false);
  EXPECT_EQ(pidsDead, pidsDeadResult);


  pids.clear();
  pidsOld.clear();
  pidsDead.clear();
  pidsDeadResult.clear();
  
  // case all died
  pidsOld = { 1, 2, 3, 4, 5, 6, 7};
  pidsDeadResult = { 1, 2, 3, 4, 5, 6, 7};
  foundDead = findDeadProcesses(pids,
				pidsOld,
				pidsDead);
  EXPECT_EQ(foundDead, true);
  EXPECT_EQ(pidsDead, pidsDeadResult);


  pids.clear();
  pidsOld.clear();
  pidsDead.clear();
  pidsDeadResult.clear();
  
  // case new processes with deaths
  pids = { 3, 4, 5, 7, 10, 11, 14, 17, 100, 98, 877 };
  pidsOld = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  pidsDeadResult = {1, 2, 6, 8, 9, 12};
  foundDead = findDeadProcesses(pids,
				pidsOld,
				pidsDead);
  EXPECT_EQ(foundDead, true);
  EXPECT_EQ(pidsDead, pidsDeadResult);
}



TEST(returnFirstIntFromLine_FUNCTION, returnFirstIntFromLine_TesT)
{
  std::string line;

  // case first numeric starts string index 0, other values follow by whitespace
  line = "34 f$kj 55";
  EXPECT_EQ(returnFirstIntFromLine(line), 34);

  // case first numeric starts string index 0 other characters directly appended
  line = "34f$kj";
  EXPECT_EQ(returnFirstIntFromLine(line), 34);

  // case first numeric starts string index 0 other characters directly appended
  // with other numeric characters directly appended to those
  line = "34f$kj54";
  EXPECT_EQ(returnFirstIntFromLine(line), 34);

  // case first numeric starts string index 0, no other characters follow
  line = "34";
  EXPECT_EQ(returnFirstIntFromLine(line), 34);    

  // case first numeric starts string index 1, other values follow by whitespace
  line = " 34 f$kj 55";
  EXPECT_EQ(returnFirstIntFromLine(line), 34);

  // case first numeric starts string index 1 other characters directly appended
  line = " 34f$kj";
  EXPECT_EQ(returnFirstIntFromLine(line), 34);

  // case first numeric starts string index 1 other characters directly appended
  // with other numeric characters directly appended to those
  line = " 34f$kj54";
  EXPECT_EQ(returnFirstIntFromLine(line), 34);

  // case first numeric starts string index 0, no other characters follow
  line = " 34";
  EXPECT_EQ(returnFirstIntFromLine(line), 34);    

  // case first numeric starts mid string appended
  line = "w#dn!@j54";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);

  // case first numeric starts mid string appended with whitespace after
  line = "w#dn!@j54 ";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);

  // case first numeric starts mid string appended with whitespace after with
  // another numeric
  line = "w#dn!@j54 43";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);

  // case first numeric starts mid string with more characters and numeric
  // appended after
  line = "w#dn!@j54df43";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);

  // case first numeric starts mid string with whitespace and more characters
  // and numeric appended after  
  line = "w#dn!@j 54df43";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);

  // case first numeric starts mid string with whitespace and more characters
  // and numeric appended after another whitepace
  line = "w#dn!@j 54 df43";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);

  // case first numeric starts mid string with whitespace and whitespace after
  line = "w#dn!@j 54 ";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);

  // repeat of test cases with just numeric characters
  line = "54 100";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);
  line = "54 100 ";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);
  line = "54 100 150";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);
  line = "54 100 150 ";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);
  line = " 54 100";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);
  line = " 54 100 ";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);
  line = " 54 100 150";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);
  line = " 54 100 150 ";
  EXPECT_EQ(returnFirstIntFromLine(line), 54);
}



TEST(returnFileLineByNumber_FUNCTION, returnFileLineByNumber_TEST)
{
  
}
