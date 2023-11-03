/*
  File: 
   extractFileData.hpp

  Description:
*/
#ifndef EXTRACTFILEDATA_HPP
#define EXTRACTFILEDATA_HPP
#include <cmath>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include "_fileConsts.hpp"
#include "cpuInfo.hpp"
#include "memInfo.hpp"
#include "processInfo.hpp"
#include "taskInfo.hpp"
#include "secondsToTime.hpp"


void createFileCSV(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
		   const std::string& filePath);
bool makeDirectory(const std::string& dirPath);
bool doesDirectoryExist(const std::string& dirPath);
const std::string returnPhraseLine(const std::string& fileName,
				   const std::string& phrase);
const int returnFirstIntFromLine(const std::string& line);
const std::string returnFileLineByNumber(const std::string& dirPath,
					 const int& lineNumber);
bool testNumericDir(const std::string& dirPath);
const std::string returnFileLineByPhrase(const std::string& filePath,
					 const std::string& phrase);
std::vector<std::string> parseLine(const std::string& str);
const int returnValByWhiteSpaceCount(const std::string& line,
				     const int& numWhiteSpaces);
const std::string returnStringByWhiteSpaceCount(const std::string& line,
						 const int& numWhiteSpaces);
bool phraseExists(const std::string& line, const std::string& phrase);
const int stringToInt(const std::string str);
const double stringToDouble(const std::string str);
const std::string doubleToStr(const double& val, const int& precision);
const std::vector<int> findNumericDirs(const std::string& dirPath);
int direntNoRecurse(const struct dirent *name);
const std::string fixStatLine(const std::string& line);
const bool findDeadProcesses(const std::vector<int>& pids,
			     const std::vector<int>& pidsOld,
			     std::vector<int>& pidsDead);
void removeDeadProcesses(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			 const std::vector<int>& pidsDead);
void extractProcUptime(SecondsToTime& uptime,
		       std::vector<std::string>& uptimeStrings,
		       const std::string& filePath);		       
void extractProcLoadavg(std::vector<std::string>& loadAvgStrings,
			const std::string& filePath);
void extractMemInfoData(MemInfo& memInfo);
const std::string createTopLine(const std::string HHMMSS,
				const int numDays,
				const int numHours,
				const int numMinutes,
				const std::vector<std::string> parsedLoadAvg);
void extractProcPidStatus(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			  const int currentPid,
			  std::string& filePath);
void extractProcPidStat(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			MemInfo& memInfo,
			SecondsToTime& uptime,
			const int currentPid,
			const std::vector<std::string>& uptimeStrings,			
			const std::string& filePath);
void extractProcStatData(CPUInfo& cpuInfo,
			 const std::string& filePath);
void defineCpusLine(std::vector<std::string>& allTopLines);
void defineMemSwapLine(std::vector<std::string>& allTopLines);
void defineMemMiBLine(std::vector<std::string>& allTopLines);
void countProcessStates(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			TaskInfo& taskInfo);
void defineTasksLine(std::vector<std::string>& allTopLines);
void extractProcPidComm(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			const int pid,
			const std::string& filePath);		     
#endif
