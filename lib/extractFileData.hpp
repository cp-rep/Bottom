/*
  File: 
   extractFileData.hpp

  Description:
   This header file contains functions that interface with files on the
   Linux system for reading and extracting OS data such as process, cpu, or
   memory inforomation. Other functions assist with this process such as
   checking for directories or updating variables/objects that contain
   previously extracted data based on dynamic changes in the OS files.
*/
#ifndef EXTRACTFILEDATA_HPP
#define EXTRACTFILEDATA_HPP
#include <cmath>
#include <cstring>
#include <filesystem>
#include <set>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>
#include "_fileConsts.hpp"
#include "cpuInfo.hpp"
#include "memInfo.hpp"
#include "processInfo.hpp"
#include "taskInfo.hpp"
#include "secondsToTime.hpp"


std::string chToStr(unsigned int value);
std::string intToStr(int value);
std::string uIntToStr(unsigned int value);
std::string doubleToStr(double value, int precision);
const int strToInt(const std::string& str);
const double strToDouble(const std::string str);

const std::string fixStatLine(const std::string& line);
std::vector<std::string> parseLine(const std::string& str);
bool phraseExists(const std::string& line, const std::string& phrase);
const std::string returnFileLineByPhrase(const std::string& filePath,
					 const std::string& phrase);
const std::string returnPhraseLine(const std::string& fileName,
				   const std::string& phrase);
const int returnFirstIntFromLine(const std::string& line);
const std::string returnFileLineByNumber(const std::string& dirPath,
					 const int& lineNumber);
void extractProcLoadavg(std::vector<std::string>& loadAvgStrings,
			const std::string& filePath);
void extractProcMeminfo(MemInfo& memInfo,
			const std::string& filePath);
void extractProcUptime(SecondsToTime& uptime,
		       std::vector<std::string>& uptimeStrings,
		       const std::string& filePath);
void extractProcStat(CPUInfo& cpuInfo,
		     const std::string& filePath);
void extractProcPidStatus(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			  const int currentPid,
			  std::string& filePath,
			  std::set<std::string>& users);			  
void extractProcPidStat(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			MemInfo& memInfo,
			SecondsToTime& uptime,
			const int currentPid,
			const std::vector<std::string>& uptimeStrings,			
			const std::string& filePath);
void extractProcPidComm(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			const int pid,
			const std::string& filePath);
void extractProcessData(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			const std::vector<int>& pids,
			MemInfo& memInfo,
			SecondsToTime& uptime,
			std::vector<std::string>& uptimeStrings,
			std::set<std::string>& users);
void createFileCSV(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
		   const std::string& filePath);
bool doesDirectoryExist(const std::string& dirPath);
bool makeDirectory(const std::string& dirPath);
bool isNumericStr(const std::string& inString);
bool testNumericDir(const std::string& dirPath);
const std::vector<int> findNumericDirs(const std::string& dirPath);
int direntNoRecurse(const struct dirent *name);

const bool findDeadProcesses(const std::vector<int>& pids,
			     const std::vector<int>& pidsOld,
			     std::vector<int>& pidsDead);
void countProcessStates(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			TaskInfo& taskInfo);
void removeDeadProcesses(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			 const std::vector<int>& pidsDead);
#endif
