/*
  File: 
   extractFileData.hpp

  Description:
*/
#ifndef EXTRACTFILEDATA_HPP
#define EXTRACTFILEDATA_HPP
#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>
#include "_fileConsts.hpp"
#include "cpuInfo.hpp"
#include "memInfo.hpp"
#include "processInfo.hpp"
#include "taskInfo.hpp"
#include "secondsToTime.hpp"



// read from files
const std::string returnPhraseLine(const std::string& fileName,
				   const std::string& phrase);
const int returnFirstIntFromLine(const std::string& line);
const std::string returnFileLineByNumber(const std::string& dirPath,
					 const int& lineNumber);

const std::vector<std::string> getFilePaths(const std::string& dirPath);
const std::vector<std::string> getFileNames(const std::string& dirPath);
const std::string getFolderPaths(const std::string& dirPath);
bool testNumericDir(const std::string& dirPath);
const std::string returnFileLineByPhrase(const std::string& filePath,
					 const std::string& phrase);

// parse from strings
std::vector<std::string> parseLine(const std::string& str);
const int returnValByWhiteSpaceCount(const std::string& line,
				     const int& numWhiteSpaces);
const std::string returnStringByWhiteSpaceCount(const std::string& line,
						 const int& numWhiteSpaces);
bool phraseExists(const std::string& line, const std::string& phrase);
const int convertToInt(const std::string str);
const double stringToDouble(const std::string str);
const std::string doubleToStr(const double& val, const int& precision);

// read from popen outputs
const std::string returnLineFromPipe(const std::string& comm,
				     const char* mode,
				     const int& lineNum);
const std::string listDirContents();
const std::vector<int> findNumericDirsPipe(const std::string& dirPath);
const std::vector<int> findNumericDirs(const std::string& dirPath);
int direntNoRecurse(const struct dirent *name);

// create strings
const std::string fixStatLine(const std::string& line);
const std::string setStringSwap(const std::string swapTotal,
				const std::string swapFree,
				const std::string swapUsed,
				const std::string memAvailable);
const std::string setStringMiB(const std::string memTotal,
			       const std::string memFree,
			       const std::string memUsed,
			       const std::string buffCache);
const bool findDeadProcesses(const std::vector<int>& pids,
			     const std::vector<int>& pidsOld,
			     std::vector<int>& pidsDead);
void removeDeadProcesses(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			 const std::vector<int>& pidsDead);
void extractProcUptimeLoadavg(SecondsToTime& uptime,
			      std::vector<std::string>& allTopLines);
void getMiB(MemInfo& memInfo);
void extractMemInfoData(MemInfo& memInfo);
const std::string createTopLine(const std::string HHMMSS,
				const int numDays,
				const int numHours,
				const int numMinutes,
				const std::vector<std::string> parsedLoadAvg);
void extractProcPidStatus(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			  MemInfo& memInfo,
			  SecondsToTime& uptime,
			  const int currentPid);
void extractProcStatData(CPUInfo& cpuInfo);
void defineCPULine(const CPUInfo& cpuInfo,
		   std::vector<std::string>& allTopLines);
void extractProcessStateCount(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			      TaskInfo& taskInfo);
void defineTasksLine(const TaskInfo& taskInfo,
		     std::vector<std::string>& allTopLines);
void extractProcComm(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
		     const int pid);
#endif
