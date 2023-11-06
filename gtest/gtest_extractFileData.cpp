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

TEST(doesDirectoryExist_FUNCTION, doesDirectoryExist_TEST)
{
  std::string dir1 = "./";
  std::string dir2 = "./gtest";

  // case directory exists
  EXPECT_EQ(doesDirectoryExist(dir1), true);
  EXPECT_EQ(doesDirectoryExist(dir2), true);
  EXPECT_NE(doesDirectoryExist(dir1), false);
  EXPECT_NE(doesDirectoryExist(dir2), false);

  std::string dir3 = "./idontexist";
  std::string dir4 = "./idefinitelydontexist";

  // case directory doesn't exist
  EXPECT_EQ(doesDirectoryExist(dir3), false);
  EXPECT_EQ(doesDirectoryExist(dir4), false);  
  EXPECT_NE(doesDirectoryExist(dir3), true);
  EXPECT_NE(doesDirectoryExist(dir4), true);

  // case empty string
  std::string dir5 = "";
  EXPECT_EQ(doesDirectoryExist(dir5), false);
  EXPECT_NE(doesDirectoryExist(dir5), true);
}



TEST(extractProcComm_FUNCTION, extractProcComm_TEST)
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

  // case command exists (read from PID 1)
  EXPECT_EQ(allProcessInfo.at(1)->getCOMMAND(), "systemd");

  // case command doesn't exist
  EXPECT_NE(allProcessInfo.at(1)->getCOMMAND(), "systemc");  

  // test list shouldn't be empty
  EXPECT_EQ(allProcessInfo.size(), 1);
  
  delete allProcessInfo.at(1);
  allProcessInfo.erase(1);

  // test list should be empty
  EXPECT_EQ(allProcessInfo.size(), 0);
}



TEST(removeDeadProcesses_FUNCTION, removeDeadProcesses_TEST)
{
  std::unordered_map<int, ProcessInfo*> allProcessInfo;
  ProcessInfo* process1 = new ProcessInfo();
  ProcessInfo* process2 = new ProcessInfo();
  ProcessInfo* process3 = new ProcessInfo();
  std::vector<int> pids;

  // case remove allocated processes
  pids.push_back(1);
  pids.push_back(2);
  pids.push_back(3);  

  allProcessInfo.insert(std::make_pair(pids.at(0), process1));
  allProcessInfo.insert(std::make_pair(pids.at(1), process2));
  allProcessInfo.insert(std::make_pair(pids.at(2), process3));

  // test list should hold 3 elements
  EXPECT_EQ(allProcessInfo.size(), 3);

  // test value should point to something
  EXPECT_NE(allProcessInfo.at(pids.at(0)), nullptr);
  EXPECT_NE(allProcessInfo.at(pids.at(1)), nullptr);
  EXPECT_NE(allProcessInfo.at(pids.at(2)), nullptr);

  removeDeadProcesses(allProcessInfo, pids);

  // test list should be empty
  EXPECT_EQ(allProcessInfo.size(), 0);
}



TEST(returnPhraseLine_FUNCTION, returnPhraseLine_TEST)
{
  const std::string filePath = "./gtest/proc_meminfo.txt";  
  const std::string fileDoesntExist = "file.file";
  const std::string phrase = "SwapCached";
  const std::string fileLine = "SwapCached:            0 kB";
  const std::string notInFile = "-2";

  // case string phrase doesn't exist
  EXPECT_EQ(returnPhraseLine(filePath, "phrase doesn't exist"), notInFile);

  // case string phrase should exist
  EXPECT_EQ(returnPhraseLine(filePath, phrase), fileLine);

  // case the file should not exist and therefore return "-1"
  EXPECT_EQ(returnPhraseLine(fileDoesntExist, phrase), "-1");

  // case the filePath should not exist and phrase not exist
  EXPECT_NE(returnPhraseLine(filePath, "phrase doesn't exist"), "-1");

  // case the filePath should exist but phrase not exist
  EXPECT_NE(returnPhraseLine(filePath, "phrase doesn't exist"), fileLine);

  // case the file does not exist and we should not get back the fileLine
  EXPECT_NE(returnPhraseLine(fileDoesntExist, phrase), fileLine);
}



TEST(makeDirectory_FUNCTION, makeDirectory_TEST)
{
  const std::string dirPath = "./testDirectory";
  bool directoryMade;

  // case create directory
  if(doesDirectoryExist(dirPath) == false)
    {
      directoryMade = makeDirectory(dirPath);
      EXPECT_EQ(directoryMade, true);
    }
  // case directory already exists
  else
    {
      directoryMade = makeDirectory(dirPath);
      EXPECT_EQ(directoryMade, false);      
    }
}



TEST(countProcessStates_FUNCTION, countProcessStates_TEST)
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

  // allocate "processses"
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

  // parse the values from file path
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

  // extract data from file path
  extractProcPidStatus(allProcessInfo,
		       1,
		       filePath);

  // test that the user was extracted correctly
  EXPECT_EQ(allProcessInfo.at(1)->getUSER(), "root");
  EXPECT_NE(allProcessInfo.at(1)->getUSER(), "roo");    
  EXPECT_NE(allProcessInfo.at(1)->getUSER(), "rooty");
  EXPECT_NE(allProcessInfo.at(1)->getUSER(), "");

  // test that the virtual memory was extracted correctly
  EXPECT_EQ(allProcessInfo.at(1)->getVIRT(), 21312);
  EXPECT_NE(allProcessInfo.at(1)->getVIRT(), 21313);

  // test that the reserved memory was extracted correctly
  EXPECT_EQ(allProcessInfo.at(1)->getRES(), 13000);
  EXPECT_NE(allProcessInfo.at(1)->getRES(), 13001);

  // test that the shared memory was extracted correctly
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

  // extract and parse uptime, we need it for next function call
  extractProcUptime(uptime,
		    uptimeStrings,
		    uptimePath);
  process = new ProcessInfo();
  allProcessInfo.insert(std::make_pair(1, process));

  // extract data from file path and parse it
  extractProcPidStat(allProcessInfo,
		     memInfo,
		     uptime,
		     1,
		     uptimeStrings,
		     statPath);

  // test data was extracted and parsed successfully
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

  // extract data from file path
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



TEST(returnFirstIntFromLine_FUNCTION, returnFirstIntFromLine_TEST)
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

  // repeat of test cases with just numeric characters and whitespace
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
  const std::string filePath = "./gtest/fileLines.txt";
  const std::string noFile = "";
  const std::string fileDoesntExist = "./doesNotExist.txt";

  // case returning correct results
  // test first line
  EXPECT_EQ(returnFileLineByNumber(filePath, 1), "File line 1.");
  EXPECT_EQ(returnFileLineByNumber(filePath, 2), "File line 2.");
  // test middle line
  EXPECT_EQ(returnFileLineByNumber(filePath, 6), "File line 6.");
  // test skipped lines  
  EXPECT_EQ(returnFileLineByNumber(filePath, 8), "File line 8.");
  EXPECT_EQ(returnFileLineByNumber(filePath, 11), "File line 11.");
  // test last line
  EXPECT_EQ(returnFileLineByNumber(filePath, 12), "And file line 12.");
  // test file lines beyond the total lines in file
  EXPECT_EQ(returnFileLineByNumber(filePath, 13), "");
  EXPECT_EQ(returnFileLineByNumber(filePath, 14), "");  

  // case returning incorrect results
  EXPECT_NE(returnFileLineByNumber(filePath, 1), "File line 1");    
  EXPECT_NE(returnFileLineByNumber(filePath, 1), "File line 2.");
  EXPECT_NE(returnFileLineByNumber(filePath, 0), "File line 1.");

  // case no filepath provided
  EXPECT_EQ(returnFileLineByNumber(noFile, 1), "-1");

  // case filepath doesn't exist
  EXPECT_EQ(returnFileLineByNumber(fileDoesntExist, 1), "-1");  
}



TEST(parseLine_FUNCTION, parseLine_TEST)
{
  std::vector<std::string> parsedString;

  std::string str1 = "the 234 kdfjf98 fantastic #$parse23&^ great";
  std::string str2 = "\tthe 234 kdfjf98 fantastic #$parse23&^ \t great";
  std::string str3 = "\t\t the \t 234   kdfjf98\tfantastic #$parse23&^ \tgreat\t";
  std::string str4 = "\t\tthe\t\t234\tkdfjf98\tfantastic\t#$parse23&^\tgreat\t";
  std::string str5 = "\t \tthe\t \t 234   \t kdfjf98\tfantastic\t #$parse23&^ \tgreat \t";
  std::string str6 = "\t \tthe\t \t 234   \t kdfjf98\tfantastic\t #$parse23&^ \tgreat ";
  std::string str7 = "\t \tthe\t \t 234   \t kdfjf98\tfantastic\t #$parse23&^ \tgreat \t ";
  std::string str8 = "    ";
  std::string str9 = "\t\t\t";
  std::string str10 = "\t \t \t";
  std::string str11 = "\t \t \t ";
  std::string str12 = " \t \t \t ";
  std::string str13 = " \t\t\t ";
  std::string str14 = " \t\t\t";
  std::string str15 = " ";
  std::string str16 = "\t";    
  std::string str17 = "";

  // case mixed with whitespace
  parsedString = parseLine(str1);
  EXPECT_EQ(parsedString.at(0), "the");
  EXPECT_EQ(parsedString.at(1), "234");
  EXPECT_EQ(parsedString.at(2), "kdfjf98");
  EXPECT_EQ(parsedString.at(3), "fantastic");
  EXPECT_EQ(parsedString.at(4), "#$parse23&^");
  EXPECT_EQ(parsedString.at(5), "great");

  // case mixed whitepsace and tabs
  parsedString.clear();
  parsedString  = parseLine(str2);
  EXPECT_EQ(parsedString.at(0), "the");
  EXPECT_EQ(parsedString.at(1), "234");
  EXPECT_EQ(parsedString.at(2), "kdfjf98");
  EXPECT_EQ(parsedString.at(3), "fantastic");
  EXPECT_EQ(parsedString.at(4), "#$parse23&^");
  EXPECT_EQ(parsedString.at(5), "great");

  // case mixed whitespace and tabs with tab at end
  parsedString.clear();
  parsedString  = parseLine(str3);
  EXPECT_EQ(parsedString.at(0), "the");
  EXPECT_EQ(parsedString.at(1), "234");
  EXPECT_EQ(parsedString.at(2), "kdfjf98");
  EXPECT_EQ(parsedString.at(3), "fantastic");
  EXPECT_EQ(parsedString.at(4), "#$parse23&^");
  EXPECT_EQ(parsedString.at(5), "great");

  // case mixed with tabs with tab at end
  parsedString.clear();
  parsedString  = parseLine(str4);
  EXPECT_EQ(parsedString.at(0), "the");
  EXPECT_EQ(parsedString.at(1), "234");
  EXPECT_EQ(parsedString.at(2), "kdfjf98");
  EXPECT_EQ(parsedString.at(3), "fantastic");
  EXPECT_EQ(parsedString.at(4), "#$parse23&^");
  EXPECT_EQ(parsedString.at(5), "great");

  // case mixed white space and tabs with space then tab at end
  parsedString.clear();
  parsedString  = parseLine(str5);
  EXPECT_EQ(parsedString.at(0), "the");
  EXPECT_EQ(parsedString.at(1), "234");
  EXPECT_EQ(parsedString.at(2), "kdfjf98");
  EXPECT_EQ(parsedString.at(3), "fantastic");
  EXPECT_EQ(parsedString.at(4), "#$parse23&^");
  EXPECT_EQ(parsedString.at(5), "great");

  // case mixed white space and tabs with space at end
  parsedString.clear();
  parsedString  = parseLine(str6);
  EXPECT_EQ(parsedString.at(0), "the");
  EXPECT_EQ(parsedString.at(1), "234");
  EXPECT_EQ(parsedString.at(2), "kdfjf98");
  EXPECT_EQ(parsedString.at(3), "fantastic");
  EXPECT_EQ(parsedString.at(4), "#$parse23&^");
  EXPECT_EQ(parsedString.at(5), "great");

  // case mixed white space and tabs with tab and then space at end
  parsedString.clear();
  parsedString  = parseLine(str7);
  EXPECT_EQ(parsedString.at(0), "the");
  EXPECT_EQ(parsedString.at(1), "234");
  EXPECT_EQ(parsedString.at(2), "kdfjf98");
  EXPECT_EQ(parsedString.at(3), "fantastic");
  EXPECT_EQ(parsedString.at(4), "#$parse23&^");
  EXPECT_EQ(parsedString.at(5), "great");


  // case various tests
  // white space only , whitespace + tab, tab only, and empty string
  parsedString.clear();
  parsedString  = parseLine(str8);
  EXPECT_EQ(parsedString.size(), 0);
  parsedString.clear();
  parsedString  = parseLine(str9);
  EXPECT_EQ(parsedString.size(), 0);
  parsedString.clear();
  parsedString  = parseLine(str10);
  EXPECT_EQ(parsedString.size(), 0);
  parsedString.clear();
  parsedString  = parseLine(str11);
  EXPECT_EQ(parsedString.size(), 0);
  parsedString.clear();
  parsedString  = parseLine(str12);
  EXPECT_EQ(parsedString.size(), 0);
  parsedString.clear();
  parsedString  = parseLine(str13);
  EXPECT_EQ(parsedString.size(), 0);
  parsedString.clear();
  parsedString  = parseLine(str14);
  EXPECT_EQ(parsedString.size(), 0);
  parsedString.clear();
  parsedString  = parseLine(str15);
  EXPECT_EQ(parsedString.size(), 0);
  parsedString.clear();
  parsedString  = parseLine(str16);
  EXPECT_EQ(parsedString.size(), 0);
  parsedString.clear();
  parsedString  = parseLine(str17);
  EXPECT_EQ(parsedString.size(), 0);  
}



TEST(stringToInt_FUNCTION, stringToInt_TEST)
{
  const std::string str1 = "";
  const std::string str2 = "0";
  const std::string str3 = "234";
  const std::string str4 = "234j";
  const std::string str5 = " 234 856";

  // case empty string
  EXPECT_EQ(stringToInt(str1), 0);

  // case numeric charcter 0
  EXPECT_EQ(stringToInt(str2), 0);

  // case numeric characters
  EXPECT_EQ(stringToInt(str3), 234);

  // case mixed alpha-numeric characters
  EXPECT_EQ(stringToInt(str4), 0);

  // case mixed numeric characters and whitespace
  EXPECT_EQ(stringToInt(str5), 0);  
}



TEST(stringToDouble_FUNCTION, stringToDouble_TEST)
{
  const std::string str1 = "";
  const std::string str2 = "0";
  const std::string str3 = "234";
  const std::string str4 = "234j";
  const std::string str5 = " 234 856";
  const std::string str6 = "1234.5678";
  const std::string str7 = " 1234.5678";
  const std::string str8 = ".1234.5678";  
  const std::string str9 = "12.34.5678";
  const std::string str10 = "1234..5678";
  const std::string str11 = "1234.5678.";
  const std::string str12 = ".";

  // case empty string
  EXPECT_EQ(stringToDouble(str1), 0);

  // case numeric charcter 0
  EXPECT_EQ(stringToDouble(str2), 0);

  // case numeric characters
  EXPECT_EQ(stringToDouble(str3), 234);

  // case mixed alpha-numeric characters
  EXPECT_EQ(stringToDouble(str4), 0);

  // case mixed numeric characters and whitespace
  EXPECT_EQ(stringToDouble(str5), 0);

  // case numeric characters with '.'
  EXPECT_EQ(stringToDouble(str6), 1234.5678);

  // case prefixed whitespace
  EXPECT_EQ(stringToDouble(str7), 0);

  // case prefixed '.' with another mixed '.'
  EXPECT_EQ(stringToDouble(str8), 0);

  // case multiple mixed '.'
  EXPECT_EQ(stringToDouble(str9), 0);

  // case multiple mixed '.' together
  EXPECT_EQ(stringToDouble(str10), 0);

  // case multiple mixed with '.' at end
  EXPECT_EQ(stringToDouble(str11), 0);

  // case only '.'
  EXPECT_EQ(stringToDouble(str12), 0);    
}



TEST(returnFileLineByPhrase_FUNCTION, returnFileLineByPhrase_TEST)
{
  const std::string filePath1 = "./gtest/proc_pid_status.txt";
  const std::string filePath2 = "";
  const std::string filePath3 = " ";
  const std::string filePath4 = "./gtest";  
  const std::string filePath5 = "./gtest/doesNotExist";

  // case file path exists, phrase exists
  // test phrase starts index 0
  EXPECT_EQ(returnFileLineByPhrase(filePath1,
				   "VmPeak"), "VmPeak:\t   30308 kB");
  // test phrase starts index 0
  EXPECT_EQ(returnFileLineByPhrase(filePath1,
				   "SigBlk"), "SigBlk:\t7fefc1fe28014a03");
  // test phrase starts mid string
  EXPECT_EQ(returnFileLineByPhrase(filePath1,
				   "\t7fef"), "SigBlk:\t7fefc1fe28014a03");
  // test phrase reaches end of string
  EXPECT_EQ(returnFileLineByPhrase(filePath1,
				   "4a03"), "SigBlk:\t7fefc1fe28014a03");
  // test phrase starts mid string
  EXPECT_EQ(returnFileLineByPhrase(filePath1,
				   "gid"), "Tgid:\t1");
  // case empty file path
  EXPECT_EQ(returnFileLineByPhrase(filePath2,
				   "gid"), "-1");
  // case bad file path
  EXPECT_EQ(returnFileLineByPhrase(filePath3,
				   "gid"), "-1");
  // case file path is a folder
  EXPECT_EQ(returnFileLineByPhrase(filePath4,
				   "gid"), "-1");
  // case file doesn't exist bad file path
  EXPECT_EQ(returnFileLineByPhrase(filePath5,
				   "gid"), "-1");  
}



TEST(fixStatLine_FUNCTION, fixStatLine_TEST)
{
  const std::string str1 = "23 (someCommand) R 0 34 56 88...";
  const std::string str2 = "23 ((someCommand)) R 0 34 56 88...";
  const std::string str3 = "23 (((((((someCommand) R 0 34 56 88...";
  const std::string str4 = "23 (((((((someCommand)) R 0 34 56 88...";
  const std::string str5 = "23 (((((((someCommand)))) R 0 34 56 88...";
  const std::string str6 = "23 (someCommand)) R 0 34 56 88...";
  const std::string str7 = "23 (someCommand)))) R 0 34 56 88...";
  const std::string str8 = "23 (someCommand)))))))) R 0 34 56 88...";
  const std::string str9 = "23 ( some Command )))))))) R 0 34 56 88...";
  const std::string str10 = "23 ( some Command )))))))) R 0 34 56 88...";
  const std::string str11 = "23 (some Command)))))))) R 0 34 56 88...";
  const std::string str12 = "23 (some: Command) R 0 34 56 88...";
  const std::string str13 = "23 (some: Command))) R 0 34 56 88...";
  const std::string str14 = "23 (some:Command ))) R 0 34 56 88...";
  const std::string str15 = "23 (some:Command ) R 0 34 56 88...";
  const std::string str16 = "23 (some:Command )";
  const std::string str17 = "23 (some:Command ) ";  
  const std::string str18 = "";

  // various cases for unnecessarily full proofing reading past
  // the command
  EXPECT_EQ(fixStatLine(str1), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str2), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str3), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str4), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str5), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str6), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str7), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str8), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str9), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str10), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str11), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str12), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str13), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str14), "R 0 34 56 88...");
  EXPECT_EQ(fixStatLine(str15), "R 0 34 56 88...");

  // case the file is corrupted after the command value
  EXPECT_EQ(fixStatLine(str16), "-1");
  EXPECT_EQ(fixStatLine(str17), "-1");

  // case empty string
  EXPECT_EQ(fixStatLine(str18), "");
}



TEST(doubleToStr_FUNCTION, doubleToStr_TEST)
{
  double val1 = 123.456789;
  double val2 = 123;
  double val3 = .29485;
  double val4 = 0;  

  // case xxx.xxxx
  EXPECT_EQ(doubleToStr(val1, 0), "123");
  EXPECT_EQ(doubleToStr(val1, 1), "123.4");
  EXPECT_EQ(doubleToStr(val1, 2), "123.45");
  EXPECT_EQ(doubleToStr(val1, 3), "123.456");
  EXPECT_EQ(doubleToStr(val1, 4), "123.4567");
  EXPECT_EQ(doubleToStr(val1, 5), "123.45678");
  EXPECT_EQ(doubleToStr(val1, 6), "123.456789");

  // case xxx
  EXPECT_EQ(doubleToStr(val2, 0), "123");  
  EXPECT_EQ(doubleToStr(val2, 1), "123.0");
  EXPECT_EQ(doubleToStr(val2, 2), "123.00");
  EXPECT_EQ(doubleToStr(val2, 3), "123.000");
  EXPECT_EQ(doubleToStr(val2, 4), "123.0000");
  EXPECT_EQ(doubleToStr(val2, 5), "123.00000");
  EXPECT_EQ(doubleToStr(val2, 6), "123.000000");      
  
  // case 0.xxx
  EXPECT_EQ(doubleToStr(val3, 0), "0");
  EXPECT_EQ(doubleToStr(val3, 1), "0.2");
  EXPECT_EQ(doubleToStr(val3, 2), "0.29");
  EXPECT_EQ(doubleToStr(val3, 3), "0.294");
  EXPECT_EQ(doubleToStr(val3, 4), "0.2948");  
  EXPECT_EQ(doubleToStr(val3, 5), "0.29485");
  EXPECT_EQ(doubleToStr(val3, 6), "0.294850");

  // case 0
  EXPECT_EQ(doubleToStr(val4, 0), "0");
  EXPECT_EQ(doubleToStr(val4, 1), "0.0");
  EXPECT_EQ(doubleToStr(val4, 2), "0.00");
  EXPECT_EQ(doubleToStr(val4, 3), "0.000");
  EXPECT_EQ(doubleToStr(val4, 4), "0.0000");
  EXPECT_EQ(doubleToStr(val4, 5), "0.00000");
  EXPECT_EQ(doubleToStr(val4, 6), "0.000000");        
}



TEST(isNumericString_FUNCTION, isNumericString_TEST)
{
  // case all numeric
  std::string str = "5555";
  EXPECT_EQ(isNumericString(str), true);

  str = "5554";
  EXPECT_EQ(isNumericString(str), true);

  str = "1234567890";
  EXPECT_EQ(isNumericString(str), true);
  
  str = "1";
  EXPECT_EQ(isNumericString(str), true);  

  // case empty string
  str = "";
  EXPECT_EQ(isNumericString(str), false);

  // case mixed characters
  str = "1a";
  EXPECT_EQ(isNumericString(str), false);
  
  str = "a1";
  EXPECT_EQ(isNumericString(str), false);

  str = "1a1";
  EXPECT_EQ(isNumericString(str), false);

  str = " 1";
  EXPECT_EQ(isNumericString(str), false);  

  str = "1 ";
  EXPECT_EQ(isNumericString(str), false);

  str = "\t";
  EXPECT_EQ(isNumericString(str), false);

  str = "\t1";
  EXPECT_EQ(isNumericString(str), false);

  str = "1\t";
  EXPECT_EQ(isNumericString(str), false);


  // test all characters that arent '0'-'9' fail
  for(int i = 0; i < '0'; i++)
    {
      str = i;
      EXPECT_EQ(isNumericString(str), false);
    }

  // test all characters '0'-'9' pass
  for(int i = '0'; i <= '9'; i++)
    {
      str = i;
      EXPECT_EQ(isNumericString(str), true);
    }

  // test that all characters after '9' fail
  for(int i = ':'; i <= 127; i++)
    {
      str = i;
      EXPECT_EQ(isNumericString(str), false);
    }
}
