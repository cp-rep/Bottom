/*
  File: extractFileData.cpp
  Description:
 */
#include "extractFileData.hpp"
#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <pwd.h>
#include <sstream>
#include <unordered_map>
#include <sys/param.h>
#include <sys/stat.h>
#include <iostream>
#include <ncurses.h>



/*
  Function:
   extractProcessData

  Description:

  Input:

  Output:
*/
void extractProcessData(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			const std::vector<int>& pids,
			MemInfo& memInfo,
			SecondsToTime& uptime,
			std::vector<std::string>& uptimeStrings,
			std::set<std::string>& users)
{
  std::string filePath;
  ProcessInfo* process;  

    // update/add process data for still running and new found processes
    for(int i = 0; i < pids.size(); i++)
      {
	// if new process was found, allocate it
	if(allProcessInfo.count(pids.at(i)) == 0)
	  {
	    process = new ProcessInfo();
	    allProcessInfo.insert(std::make_pair(pids.at(i), process));
	  }
	
	// set pid of current process
	allProcessInfo.at(pids.at(i))->setPID(pids.at(i));

	// extract per process data (USER, PR, VIRT...)
	// /proc/[pid]/status
	filePath.clear();
	filePath = _PROC + std::to_string(pids.at(i));
	filePath.append(_STATUS);
	extractProcPidStatus(allProcessInfo,
			     pids.at(i),
			     filePath,
			     users);
	
	// /proc/uptime & /proc/[pid]/stat
	filePath.clear();
	filePath = _PROC + std::to_string(pids.at(i));
	filePath.append(_STAT);
	extractProcPidStat(allProcessInfo,
			   memInfo,
			   uptime,
			   pids.at(i),
			   uptimeStrings,
			   filePath);

	// extract COMMAND
	// /proc/[pid]/comm
	filePath.clear();
	filePath = _PROC + std::to_string(pids.at(i));
	filePath.append(_COMM);
	extractProcPidComm(allProcessInfo,
			   pids.at(i),
			   filePath);
      }  
} // end of "extractProcessData"



/*
  Function:
   CreateFileCSV

  Description:
   Loops through the current dynamically allocated ProcessInfo list and extracts
   the COMMAND associated with each process and outputs the command to a comma
   seperated value list, saving it to the users computer.  If the file already
   exists, it is overwritten.  If it doesn't exist, it is created.

  Input:
   allProcessInfo       - A constant unordored map<int, ProcessInfo*> object type
                          that holds process data found in /proc/[pid]/.
			  related directories. The index key is the corresponding
			  PID for its ProcessInfo value.
			  
   filePath             - A const string type that is the filepath to which append
                          a filename and write the CSV list to and output to the
			  users computer.
  Output:
   NONE
*/
void createFileCSV(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
		   const std::string& filePath)
{
  std::string tempPath = filePath;
  tempPath.append("commands.csv");
  std::ofstream csvOut;
  std::string tempCommand;

  csvOut.open(tempPath);

  for(std::unordered_map<int, ProcessInfo*>::const_iterator it = allProcessInfo.begin();
	it != allProcessInfo.end(); it++)
    {
      tempCommand = it->second->getCOMMAND();
      csvOut << tempCommand;
      csvOut << ", ";
    }
} // end of "createFileCSV"



/*
  Function:
   makeDirectory

  Description:
   Makes a directory based on the incoming directory path provided the parameter.
   If the directory path already exists, a return value of false is returned,
   else, a directory is made at the incoming directory path and a value of
   true is returned.

  Input:
   dirPath              - A const string object type that contains the filepath
                          to which a directory will be created based on a
			  conditional check.

  Output:
   bool                 - A bool type returned as false if the directory already
                          exists, true if a directory is created.
*/
bool makeDirectory(const std::string& dirPath)
{
  if(doesDirectoryExist(dirPath))
    {
      return false;
    }
  else
    {
      mkdir(dirPath.c_str(), 0755);
      return true;
    }
} // end of "makeDirectory"



/*
  Function:
   doesDirectoryExist

  Description:
   Checks if a directory exists based upon the incoming parameter directory path.
   If the directory exists, a value of true is returned, else, a value of
   false is returned.

  Input:
   dirPath              - A const string type containing a filepath to a directory
                          to check for existence.

  Output:
   bool                 - A bool type representing the result of the conditional
                          check of the directories existence.
*/
bool doesDirectoryExist(const std::string& dirPath)
{
  std::filesystem::path directoryPath(dirPath);
  bool isDir = false;
  
  if(std::filesystem::exists(dirPath) && std::filesystem::is_directory(dirPath))
    {
      isDir = true;
    }
  else
    {
      isDir = false;
    }

  return isDir;
} // end of "doesDirectoryExist"



/*
  Function:
   extractProcPidComm

  Description:
   Extracts the command associated with the pid number from the
   /proc/[pid]/comm filepath and stores it in the one of the private
   member variables of the incoming paremter.

  Input:
   allProcessInfo       - An unordored map<int, ProcessInfo*> object type
                          that holds process related data found in
			  /proc/[pid]/. related directories. The index key
			  is the corresponding PID for its ProcessInfo
			  value.
			  
   pid                  - A const int type holding a process id to extract
                          its related command for.  It is used to as a key
			  for the allProcessInfo key/value pairs.

   filePath             - A reference to a constant string object that should
                          contain the full path to the file path
			  /proc/[pid]/comm.
   
  Output:
   NONE
*/
void extractProcPidComm(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
		     const int pid,
		     const std::string& filePath)
{
  std::string lineString = returnFileLineByNumber(filePath, 1);
  allProcessInfo[pid]->setCOMMAND(lineString);
} // end of "extractProcPidComm"



/*
  Function:
   defineTasksLine

  Description:
   Simply creates a string and stores it in a vector of strings that is the incoming
   parameter.
  
  Input:
   allTopLines          - A vector<string> object type that will hold the base strings
                          for outputing data to the screen.

  Output:
   NONE
*/
void defineTasksLine(std::vector<std::string>& allTopLines)
{
  std::string tasksLine;
  tasksLine = "Tasks:     total,     running,     sleeping,     stopped,     zombie";
  allTopLines.push_back(tasksLine);
} // end of "defineTasksLine"



/*
  Function:
   defineMemMiBLine

  Description:
   Simply creates a string and stores it in a vector of strings that is the incoming
   parameter.
  
  Input:
   allTopLines          - A vector<string> object type that will hold the base strings
                          for outputing data to the screen.  
  Output:
   NONE
*/
void defineMemMiBLine(std::vector<std::string>& allTopLines)
{
  std::string memLine;
  memLine.append("MiB Mem :          total,          free,          used,          buff/cache");
  allTopLines.push_back(memLine);
} // end of "defineMemMiBLine"



/*
  Function:
   defineMemSwapLine

  Description:
   Simply creates a string and stores it in a vector of strings that is the incoming
   parameter.
  
  Input:
   allTopLines          - A vector<string> object type that will hold the base strings
                          for outputing data to the screen.  
  Output:
   NONE
*/
void defineMemSwapLine(std::vector<std::string>& allTopLines)
{
  std::string swapLine;
  swapLine.append("MiB Swap:          total,          free,          used,          avail Mem");
  allTopLines.push_back(swapLine);
} // end of "defineMemSwapLine"



/*
  Function:
   defineCpusLine

  Description:
   Simply creates a string and stores it in a vector of strings that is the incoming
   parameter.
  
  Input:
   allTopLines          - A vector<string> object type that will hold the base strings
                          for outputing data to the screen.  
  Output:
   NONE
*/
void defineCpusLine(std::vector<std::string>& allTopLines)
{
  std::string cpusLine;
  cpusLine = "%Cpu(s):      us,      sy,      ni,      id,      wa,      hi,      si,      st";
  allTopLines.push_back(cpusLine);
} // end of "defineCpusLine"



/*
  Function:
   countProcessStates

  Description:
   Loops through all current dynamically allocated ProcessInfo objects and retrieves
   the corresponding processes current state.  That value is used as the runtime
   constant for a switch statement that tallies how many of each process state
   are currently active.  Upon completing the loop, the resulting values are stored
   in the TaskInfo object type parameter.

  Input:
   allProcessInfo       - A const unordored map<int, ProcessInfo*> object type
                          that holds process related data found in
			  /proc/[pid]/. related directories. The index key
			  is the corresponding PID for its ProcessInfo
			  value.
			  
   taskInfo             - An TaskInfo object type that is used for storing, retreiving,
                          and calculating related task process state values.
                          
  Output:
   NONE
*/
void countProcessStates(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			TaskInfo& taskInfo)
{
  unsigned int running = 0;
  unsigned int unSleep = 0;
  unsigned int inSleep = 0;
  unsigned int sleeping = 0;
  unsigned int stopped = 0;
  unsigned int zombie = 0;
  unsigned int idle = 0;
  unsigned int total = 0;

  for(std::unordered_map<int, ProcessInfo*>::const_iterator it = allProcessInfo.begin();
      it != allProcessInfo.end(); it++)
    {
      switch(it->second->getS())
	{
	case 'S':
	  inSleep++;
	  break;
	case 'I':
	  idle++;
	  break;
	case 'T':
	  stopped++;
	  break;
	case 'D':
	  unSleep++;
	  break;
	case 'R':
	  running++;
	  break;
	case 'Z':
	  zombie++;
	  break;
	default:
	  break;
	}
    }

  taskInfo.setRunning(running);
  taskInfo.setUnSleep(unSleep);
  taskInfo.setInSleep(inSleep);
  taskInfo.setStopped(stopped);
  taskInfo.setZombie(zombie);
  taskInfo.setIdle(idle);
  sleeping = taskInfo.calcSleeping();
  taskInfo.setSleeping(sleeping);
  total = taskInfo.calcTotal();
  taskInfo.setTotal(total);
} // end of "countProcessStates"



/*
  Function:
   extractProcStat

  Description:
   Extracts CPU related data from the /proc/stat file and stores it in the
   incoming parameter.

  Input:
   cpuInfo              - A CPUInfo object type that contains member functions
                          for storing, retrieving, and calculating extracted CPU
			  related values.
  Output:
   NONE
*/
void extractProcStat(CPUInfo& cpuInfo,
		     const std::string& filePath)
{
  std::string lineString;
  std::string fileLine;  
  std::vector<std::string> parsedLine;
  int tempInt;
  const double ticks = (double)sysconf(_SC_CLK_TCK);
  
  lineString = returnFileLineByNumber(filePath, 1);
  parsedLine = parseLine(lineString);
  cpuInfo.setUs(stringToInt(parsedLine.at(1)));
  cpuInfo.setNi(stringToInt(parsedLine.at(2)));
  cpuInfo.setSy(stringToInt(parsedLine.at(3)));
  cpuInfo.setId(stringToInt(parsedLine.at(4)));
  cpuInfo.setWa(stringToInt(parsedLine.at(5)));
  cpuInfo.setIrq(stringToInt(parsedLine.at(6)));
  cpuInfo.setSirq(stringToInt(parsedLine.at(7)));
  cpuInfo.setSt(stringToInt(parsedLine.at(8)));
  cpuInfo.setGu(stringToInt(parsedLine.at(9)));
  cpuInfo.setGun(stringToInt(parsedLine.at(10)));
} // end of "extractProcStat"



/*
  Function:
   extractProcPidStatus

  Description:
   Extracts data from the /proc/[pid]/status file and saves it to related
   parameters member data while making necessary calculations to represent
   the member data names that are used for outputting the extracted
   data.
   
  Input:
   allProcessInfo       - A unordored map<int, ProcessInfo*> object type
                          that holds process related data found in
			  /proc/[pid]/. related directories. The index key
			  is the corresponding PID for its ProcessInfo
			  value.
			  
   currentPid           - A constant integer type holding the PID of the current
                          process we are examining in the main program loop.

   filePath             - A reference to a string type that should contain
                          the file path to /proc/[pid]/status			  
  Output:
   NONE
*/
void extractProcPidStatus(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			  const int currentPid,
			  std::string& filePath,
			  std::set<std::string>& users)
{
  std::string lineString;
  std::string fileLine;
  std::vector<std::string> parsedLine;
  int tempInt;

  lineString = returnPhraseLine(filePath, "Gid");

  // set value to  "-1" for current data if the file doesn't exist at the
  // filePath.  This must be checked because processes may stop running
  // and their file paths close
  if(lineString != "-1")
    {
      struct passwd userData;
      struct passwd* userDataPtr;
      uid_t uidt;
      char buff[1024];

      parsedLine = parseLine(lineString);
      uidt = stringToInt(parsedLine.at(1));
	      
      if(!(getpwuid_r(uidt, &userData, buff, sizeof(buff), &userDataPtr)))
	{
	  allProcessInfo.at(currentPid)->setUSER(userData.pw_name);
	}
      else
	{
	  allProcessInfo.at(currentPid)->setUSER("");
	}
    }
  else
    {
      allProcessInfo.at(currentPid)->setUSER("");
    }

  // store user type in set for counting later
  if(users.count(allProcessInfo.at(currentPid)->getUSER()) == 0)
    {
      users.insert(allProcessInfo.at(currentPid)->getUSER());
    }	  
  
  // get VIRT
  lineString = returnFileLineByPhrase(filePath, "VmSize");
	  
  if(lineString != "-1")
    {
      parsedLine = parseLine(lineString);
      tempInt = stringToInt(parsedLine.at(1));
      allProcessInfo.at(currentPid)->setVIRT(tempInt);
    }

  // get RES
  lineString = returnFileLineByPhrase(filePath, "VmRSS");

  if(lineString != "-1")
    {
      parsedLine = parseLine(lineString);
      tempInt = stringToInt(parsedLine.at(1));
      allProcessInfo.at(currentPid)->setRES(tempInt);
    }

  // get SHR
  lineString = returnFileLineByPhrase(filePath, "RssFile");

  if(lineString != "-1")
    {
      parsedLine = parseLine(lineString);
      tempInt = stringToInt(parsedLine.at(1));
      allProcessInfo.at(currentPid)->setSHR(tempInt);
    }
} // end of "extractProcPidStatus"



/*
  Function:
   extractProcPidStat

  Description:
   Extracts data from the /proc/[pid]/stat file and saves it to related
   parameter member data while making necessary calculations to represent
   the member data names that are used for outputting the extracted
   data.
   
  Input:
   allProcessInfo       - A unordored map<int, ProcessInfo*> object type
                          that holds process related data found in
			  /proc/[pid]/. related directories. The index key
			  is the corresponding PID for its ProcessInfo
			  value.   

   memInfo              - A MemInfo object type that has member functions
                          for storing, retrieving, and calculating values
			  for its memory related member variables.

   uptime               - A SecondsToTime object type that has member functions
                          for storing, retrieving, and calculating/converting time
			  related values to store in its member varaibles.

   currentPid           - A constant integer type holding the PID of the current
                          process we are examining in the main program loop.

   filePath             - A reference to a string type that should contain
                          the file path to /proc/[pid]/stat.
  Output:
   NONE
*/
void extractProcPidStat(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			MemInfo& memInfo,
			SecondsToTime& uptime,
			const int currentPid,
			const std::vector<std::string>& uptimeStrings,
			const std::string& filePath)
{
  std::string fileLine;  
  std::string lineString;
  std::vector<std::string> parsedLine;  
  int tempInt;
  
  // get PR
  lineString = returnFileLineByNumber(filePath, 1);

  if(lineString != "-1")
    {
      double utime = 0;
      double stime = 0;
      double cutime = 0;
      double cstime = 0;
      double pstart = 0;
      double percent = 0;
      int startUsage;

      // use uptime values for helping calculate CPU usage
      percent = stringToDouble(uptimeStrings.at(0));      
      uptime.setTotalSeconds(percent);
      allProcessInfo.at(currentPid)->setCPUUsage(percent);

      // get PR
      lineString = fixStatLine(lineString);
      parsedLine = parseLine(lineString);
      tempInt = stringToInt(parsedLine.at(15));
      allProcessInfo.at(currentPid)->setPR(tempInt);

      // get NI
      tempInt = stringToInt(parsedLine.at(16));
      allProcessInfo.at(currentPid)->setNI(tempInt);

      // get S
      allProcessInfo.at(currentPid)->setS(lineString.at(0));

      // get %CPU for current process
      utime = stringToInt(parsedLine.at(11));
      stime = stringToInt(parsedLine.at(12));
      cutime = stringToInt(parsedLine.at(13));
      cstime = stringToInt(parsedLine.at(14));
      pstart = stringToInt(parsedLine.at(19));
      allProcessInfo.at(currentPid)->setUTime(utime);
      allProcessInfo.at(currentPid)->setSTime(stime);
      allProcessInfo.at(currentPid)->setCUTime(cutime);
      allProcessInfo.at(currentPid)->setCSTime(cstime);
      allProcessInfo.at(currentPid)->setPStart(pstart);
      startUsage = (utime + cutime)/(uptime.getTotalSeconds() - (pstart/100));
      allProcessInfo.at(currentPid)->setCPUUsage(startUsage);
      
      

      /*
      percent = std::ceil(percent * 100);
      percent = percent /100;


      double tempDouble = percent;
      int tempInt;
      tempDouble *= 10;
      tempInt = tempDouble;

      if(tempInt != 0)
	{
	  tempDouble = tempInt;
	  tempDouble = tempDouble/10;
	  allProcessInfo.at(currentPid)->setCPUUsage(tempDouble);
	}
      else
	{
	  allProcessInfo.at(currentPid)->setCPUUsage(0);
	}
      */
      // get TIME+ (CPU time)
      allProcessInfo.at(currentPid)->setCpuRawTime(utime + cutime);
      SecondsToTime timePlus((utime + cutime)/((double)sysconf(_SC_CLK_TCK)));
      std::string timePlusString = timePlus.returnHHMMSS(timePlus.getHours(),
							 timePlus.getMinutes(),
							 timePlus.getSeconds());
      allProcessInfo.at(currentPid)->setProcessCPUTime(timePlusString);

      // get %MEM
      percent = allProcessInfo.at(currentPid)->getRES();
      percent = percent/(double)memInfo.getMemTotal();
      percent = std::ceil(percent * 1000.0);
      percent = percent/10;
      allProcessInfo.at(currentPid)->setMEMUsage(percent);
    }
} // end of "extractProcPidStat"



/*
  Function:
   extractProcUptime

  Description:
   Opens the /proc/uptime file for reading and extracts its data.  The data is
   parsed and converted to human readable time values stored in the SecondsToTime
   object parameter.

  Input:
   uptime               - A SecondsToTime object type that has member functions
                          for storing, retrieving, and calculating/converting time
			  related values to store in its member variables.
			  
   filePath             - A reference to a constant string object containing that
                          should contain a file path for the /proc/uptime file.
  Output:
   NONE
*/
void extractProcUptime(SecondsToTime& uptime,
		       std::vector<std::string>& uptimeStrings,		       
		       const std::string& filePath)
{
  int tempInt;
  std::string fileLine;

  fileLine = returnFileLineByNumber(filePath, 1);
  
  if(fileLine != "-1")
    {
      uptimeStrings = parseLine(fileLine);
      tempInt = stoi(uptimeStrings.at(0));
      uptime.setHours(uptime.convertToHours(tempInt));
      uptime.setMinutes(uptime.convertToMinutes(tempInt));
      uptime.setSeconds(uptime.findRemainingSeconds(tempInt));
      uptime.setTotalSeconds(tempInt);
    }
} // end of "extractProcUptime"



/*
  Function:
   extractProcLoadavg

  Description:
   Opens the /proc/loadavg file for reading and extracts its data.  The data
   is parsed and stored in a vector<string> object type that is passed
   back to the caller by reference.

  Input:
   uptime               - A SecondsToTime object type that has member functions
                          for storing, retrieving, and calculating/converting time
			  related values to store in its member variables.
			  
   loadAvgs             - A reference to a vector<string> object type that will be
                          used to store parsed data from the /proc/loadavg file.

   filePath		- A reference to a constant string object type that should
                          contain a path to the /proc/loadavg file.
  Output:
   None
*/
void extractProcLoadavg(std::vector<std::string>& loadAvgStrings,
			const std::string& filePath)
{
  std::string fileLine;
  fileLine = returnFileLineByNumber(filePath, 1);
  loadAvgStrings = parseLine(fileLine);
} // end of "extractProcLoadavg"



/*
  Function:
   createTopLine

  Description:
   Uses incoming parameters to create the output string for the very top
   default line of the Top utility program.  The created line is returned.

  Input:
   HHMMSS               - A const string object type that holds the current
                          military time.
			  
   numDays              - A const int type that holds the number of days the
                          system has been up.

   numHours             - A const int type that holds the number of hours the
                          system has been up.

   numMinutes           - A const int type that holds the number of minutes
                          the system has been up.

   parsedLoadAvg        - A const vector<string> object type that holds the
                          data for the /proc/loadavg file, parsed into a
			  individual strings for each value.

  Output:
   string               - A const string object type that should contain
                          the result of the created top line.
*/
const std::string createTopLine(const std::string HHMMSS,
				const int numDays,
				const int numHours,
				const int numMinutes,
				const std::vector<std::string> parsedLoadAvg,
				const int& numUsers)
{
  std::string tempTopString;
  tempTopString.append("top - ");
  tempTopString.append(HHMMSS);
  tempTopString.append(" up ");

  if(numDays < 1)
    {
      if(numHours < 1)
	{
	  tempTopString.append(std::to_string(numMinutes));
	  tempTopString.append(" min, ");
	}
      else
	{
	  if(numHours < 10)
	    {
	      tempTopString.append(" ");
	    }
	  tempTopString.append(std::to_string(numHours));
	  tempTopString.append(":"); 
	  if(numMinutes < 10)
	    {
	      tempTopString.append("0");
	    }
	  tempTopString.append(std::to_string(numMinutes));
	  tempTopString.append(", ");
	}
    }

  else if(numDays == 1)
    {
      tempTopString.append(std::to_string(numDays));
      tempTopString.append(" day, ");
    }

  else
    {
      tempTopString.append(std::to_string(numDays));      
      tempTopString.append(" days, ");
    }
  
  tempTopString.append(std::to_string(numUsers));

  if(numUsers == 1)
    {
      tempTopString.append(" user,  load average: ");
    }
  else
    {
      tempTopString.append(" users,  load average: ");
    }
  
  tempTopString.append(parsedLoadAvg.at(0));
  tempTopString.append(", ");
  tempTopString.append(parsedLoadAvg.at(1));
  tempTopString.append(", ");
  tempTopString.append(parsedLoadAvg.at(2));

    return tempTopString;
} // end of "createTopLine"



/*
  Function:
   extractProcMemInfo

  Description:
   Extracts data from the /proc/meminfo file and stores it in the
   MemInfo object parameter.

  Input:
   memInfo              - A MemInfo object type that has member functions
                          for storing, retrieving, and calculating values
			  for its memory related member variables.
			  
   filePath		- A reference to a constant string object type that should
                          contain a path to the /proc/meminfo file.			  
  Output:
   NONE
*/
void extractProcMeminfo(MemInfo& memInfo,
			const std::string& filePath)
{
  std::string fileLine;
  std::vector<std::string> parsedLine;

  // extract MemTotal
  fileLine = returnFileLineByNumber(filePath, 1);
  parsedLine = parseLine(fileLine);
  memInfo.setMemTotal(stringToInt(parsedLine.at(1)));

  // extract MemFree
  fileLine = returnFileLineByNumber(filePath, 2);
  parsedLine = parseLine(fileLine);
  memInfo.setMemFree(stringToInt(parsedLine.at(1)));

  // extract MemAvailable
  fileLine = returnFileLineByNumber(filePath, 3);
  parsedLine = parseLine(fileLine);
  memInfo.setMemAvailable(stringToInt(parsedLine.at(1)));

  // extract Buffer
  fileLine = returnFileLineByNumber(filePath, 4);
  parsedLine = parseLine(fileLine);
  memInfo.setBuffers(stringToInt(parsedLine.at(1)));

  // extract Cached
  fileLine = returnFileLineByNumber(filePath, 5);
  parsedLine = parseLine(fileLine);
  memInfo.setCached(stringToInt(parsedLine.at(1)));

  // extract SwapTotal
  fileLine = returnFileLineByNumber(filePath, 15);
  parsedLine = parseLine(fileLine);
  memInfo.setSwapTotal(stringToInt(parsedLine.at(1)));

  // extract SwapFree
  fileLine = returnFileLineByNumber(filePath, 16);
  parsedLine = parseLine(fileLine);
  memInfo.setSwapFree(stringToInt(parsedLine.at(1)));

  // extract SReclaimable and calculate related values
  fileLine = returnFileLineByNumber(filePath, 26);
  parsedLine = parseLine(fileLine);
  memInfo.setSReclaimable(stringToInt(parsedLine.at(1)));
  memInfo.setMemUsed(memInfo.calculateMemUsed());
  memInfo.setSwapUsed(memInfo.calculateSwapUsed());
  memInfo.setBuffCache(memInfo.calculateBuffCache());  
} // end of "extractProcMemInfo"



/*
  Function:
   findDeadProcesses

  Description:
   Loops through the pid lists looking for processes that have died
   during the main program loop between the last time the process list
   was gathered stored in pidsOld, and the currently gathered list stored
   in pids.  The found dead processes are stored in the pidsDead parameter.

  Input:
   pids                 - A reference to a constant vector<int> object type
                          that contains the most recently gathered running
			  process list.
			  
   pidsOld              - A reference to a constant vector<int> object type
                          that contains the process PIDs that were gathered
			  during the previous main program loop.
			  
   pidsDead             - A reference to a vector<int> object type that
                          should be empty and used to store process PIDs
			  from the pidsOld parameter that are not in the
			  pids parameter.  The list is "returned" by
			  reference.
  Output:
   bool                 - True if any dead process were found, false
                          otherwise.
*/
const bool findDeadProcesses(const std::vector<int>& pids,
			     const std::vector<int>& pidsOld,
			     std::vector<int>& pidsDead)
{
  bool foundDead = false;
  for(int i = 0; i < pidsOld.size(); i++)
    {
      bool exists = false;

      for(int j = 0; j < pids.size(); j++)
	{
	  if(pidsOld.at(i) == pids.at(j))
	    {
	      exists = true;
	      break;
	    }
	}

      if(exists == false)
	{
	  foundDead = true;
	  pidsDead.push_back(pidsOld.at(i));
	}
    }

  return foundDead;
} // end of "findDeadProcesses"



/*
  Function:
   removeDeadProcessees

  Description:
   Frees the process data stored in the allProcessInfo object parameter that
   represents processes that were found to have died between the previous
   program loop, and the current program loop.

  Input:
   allProcessInfo       - A unordored map<int, ProcessInfo*> object type
                          that holds process related data found in
			  /proc/[pid]/. related directories. The index key
			  is the corresponding PID for its ProcessInfo
			  value.
			  
   pidsDead             - A reference to a constant vector<int> object type
                          that should hold a list of all the "dead" process
			  IDs.

  Output:
   NONE
*/
void removeDeadProcesses(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			 const std::vector<int>& pidsDead)
{
  for(int i = 0; i < pidsDead.size(); i++)
    {
      if(allProcessInfo.count(pidsDead.at(i)) > 0)
	{
	  delete(allProcessInfo[pidsDead.at(i)]);
	  allProcessInfo[pidsDead.at(i)] = nullptr;
	  allProcessInfo.erase(pidsDead.at(i));
	}
    }  
} // end of "removeDeadProcesses"



/*
  Function:
   returnPhraseLine
   
  Description:
   Opens the file at the file path contained in the parameter fileName and
   proceeds to read the file line by line looking for a string containing
   the "phrase" from the parameter const std::string phrase. This function is
   specific for reading a phrase from the /proc/meminfo and /proc/[pid]/status
   files only (They require reaching a colon as a delimiter to successfully
   extract data.)

  Input:
   fileName                    - a const std::string of the file path for the
                                file to open and read line by line.
   phrase		       - a const std::string for the phrase to search
                                for in each line read.
  
  Output:
   std::string                 - a const std::string containing the line which
                                the phrase was found.
*/
const std::string returnPhraseLine(const std::string& fileName,
				   const std::string& phrase)
{
  std::string tempLine;
  std::string tempPhrase;
  bool found = false; 
  std::ifstream inFile(fileName, std::ifstream::in);   

  // test if the file opened successfully
  if(!inFile.is_open())
    {
      return "-1";
    }

  // read the file line by line looking for the matching phrase
  for(int i = 0;; i++)
    {
      tempPhrase.clear();
      std::getline(inFile, tempLine);

      // check if EoF was read
      if(tempLine == "")
	break;
      
      for(int j = 0; tempLine.at(j) != ':'; j++)
	{
	  tempPhrase.push_back(tempLine.at(j));
	}

      if(tempPhrase == phrase)
	{
	  found = true;
	  break;
	}      	        
    }

  inFile.close();

  if(found == false)
    {
      return "-2";
    }

  else
    {
      return tempLine;
    }

} // end of "returnPhraseLine"



/*
  Function:
   returnFirstIntFromLine
   
  Description:
   Finds the first ASCII numeric character(s) from the line parameter,
   converts them to an int type, and then returns the value.

  Input:
   line                 - a const string that will be scanned
                          for numeric characters.
  
  Output:
   const int            - returns the value extract from the line if
                          successful, else returns -1
*/
const int returnFirstIntFromLine(const std::string& line)
{
  std::string temp;
  int i = 0;

  if(line.empty())
    {
      return 0;
    }
  
  // loop until we reach a numeric character
  while(i < line.size())
    {
      if(line.at(i) < '0' || line.at(i) > '9')
	{
	  i++;
	}
      else
	{
	  break;
	}
    }
  
  // push back numeric characters until we reach a non-numeric character
  while(i < line.size())
    {
      if(line.at(i) >= '0' && line.at(i) <= '9')
	{
	  temp.push_back(line.at(i));
	  i++;
	}
      else
	{
	  break;
	}
    }
  
  if(temp.empty())
    {
      return -1;
    }
  else
    {
      return stoi(temp);
    }
} // end of "returnFirstIntFromLine"



/*
  Function:
   returnFileLineByNumber
   
  Description:
   Returns a specified line from a file of a corresponding line number.

  Input:
   filePath               - a const reference to a string for a full file path.

   lineNumber             - a const reference to an int for a specific line number
                            we want to return.
			   
  Output:
   const string           - a const string containing the desired line we are
                            returning based upon the incoming line number.
*/
const std::string returnFileLineByNumber(const std::string& filePath,
					 const int& lineNumber)
{
  struct stat file;
  std::string tempLine;
  
  if(stat(filePath.c_str(), &file) == 0 && S_ISREG(file.st_mode))
    {
      std::ifstream inFile(filePath, std::ifstream::in);
      
      for(int i = 0; i < lineNumber; i++)
	{
	  std::getline(inFile, tempLine, '\n');
	}

      inFile.close();
      
      return tempLine;
    }
  else
    {
      return "-1";
    }    
} // end of "returnFileLineByNumber"



/*
  Function:
   testNumericDir

  Description:
   This function tests that a directory file name is represented only
   by numeric characters.  This is essential for determining which
   directories are /proc/[pid] directories in the /proc filepath.
   
  Input:
   dirPath              - A reference to a constant string object type
                          that should contain the directory path for
			  testing.

  Output:
   bool                 - A bool type that returns true if the directory
                          is represented by numeric characters only, else
			  false is returned.
 */
bool testNumericDir(const std::string& dirPath)
{
  struct stat dir;
  bool isNumericDir = false;
 
 if(stat(dirPath.c_str(), &dir) == 0 && S_ISDIR(dir.st_mode))
    {
      return true;
    }
  else
    {
      return false;
    }
} // end of "testNumericDir"



/*
  Function:
  parseLine

  Description:
   Using white space and tabs as delimeters, the incoming string is
   parsed to individual strings and stored in a vector<string> object
   type and returned to the caller.

  Input:
   str                  - A reference to a constant string object type
                          that should contain delimited character data
			  to be parsed.

  Output:
   vector<string>       - A vector<string> object type that should
                          contain the parsed values from the str
			  parameter.
 */
std::vector<std::string> parseLine(const std::string& str)
{
  std::vector<std::string> parsedString;
  std::string temp;
  
  for(int i = 0; i < str.length(); i++)
    {
      while((str.at(i) == '\t' || str.at(i) == ' ') && i < str.length())
	{
	  if( (str.at(i) == '\t' && i == str.length() - 1) ||
	      (str.at(i) == ' ' && i == str.length() - 1))
	    {
	      break;
	    }
	  
	  if(!temp.empty())
	    {
	      parsedString.push_back(temp);
	      temp.clear();
	    }
	  i++;
	}

      if((str.at(i) != '\t') &&
	 (str.at(i) != ' '))
	{
	  temp.push_back(str.at(i));
	}
    }

  if(!temp.empty())
    {
      parsedString.push_back(temp);
    }

  return parsedString;
} // end of "parseLine"



/*
  Function:
   direntNoRecurse

   Description:
    A helper function used as an argument to the dirent.h scandir function.
    Returning a value of 1 tells that function to not recurse further down.

    Input:
     name               - a const pointer to a dirent.h structure

    Output:
     int                - value that tells the scandir function not to recurse
    
 */
int direntNoRecurse(const struct dirent *name)
{
  return 1;
} // end of "direntNoRecurse"
  


/*
  Function:
   findNumericDirs

   Description:
    Uses the <dirent.h> library to find all directories at the target 
    directory that contain only numbers and return them as a vector<int> 
    to the caller.

    Input:
     dirpath            - a const string type representing the target 
                          directory to search for numeric directories in.

    Output:
     const std::vector<int>
                        - the list of found numeric directories
 */
const std::vector<int> findNumericDirs(const std::string& dirPath)
{
  struct dirent **dirNames;
  std::vector<int> tempDirs;
  int numDirs = scandir("/proc/", &dirNames, direntNoRecurse, alphasort);

  while(numDirs--)
    {
      std::string fullPath = "/proc/";
      std::string fileInPath;
      fileInPath = dirNames[numDirs]->d_name;
      fullPath.append(fileInPath);
      
      if(true == testNumericDir(fullPath))
	{
	  int val;
	  
	  std::stringstream container(fileInPath);
	  container >> val;
	  
	  if(val != 0)
	    {
	      tempDirs.push_back(val);
	    }
	}
      
      free(dirNames[numDirs]);
    }

  free(dirNames);

  return tempDirs;
} // end of "findNumericDirs"



/*
  Function:
   stringToInt

  Description:
   Converts an incoming string to an int type iff the string contains
   only numeric characters.

  Input:
   str                  - A constant string object type that should
                          contain the numeric characters we wish to
			  convert to an integer type and return it.

  Output:
   int                  - A constant integer type that should contain
                          the result of the conversion.
*/
const int stringToInt(const std::string str)
{
  int val = 0;
  
  if(!str.empty())
    {
      for(int i = 0; i < str.length(); i++)
	{
	  if(str.at(i) < '0' || str.at(i) > '9')
	    {
	      return 0;
	    }
	}
      
      std::stringstream container(str);
      container >> val;
    }
  
  return val;
} // end of "stringToInt"



/*
  Function:
   stringToDouble

  Description:
   Converts an incoming string to a double type iff the string contains
   only numeric contains (excluding the period).

  Input:
   str                  - A constant string type that should represent
                          a floating point value we wish to convert from
			  a string to a double type and return it.

  Output:
   double               - A constant double type that is the result of
                          the conversion.
 */
const double stringToDouble(const std::string str)
{
  double val = 0;
  double dotCount = 0;
  
  if(!str.empty())
    {
      for(int i = 0; i < str.length(); i++)
	{
	  if((str.at(i) < '0' || str.at(i) > '9') && str.at(i) != '.')
	    {
	      return 0;
	    }
	  
	  if(str.at(i) == '.')
	    {
	      dotCount++;

	      if(dotCount > 1)
		{
		  return 0;
		}
	    }
	}
      
      std::stringstream container(str);
      container >> val;
    }
  
  return val;  
} // end of "stringToDouble"



/*
  Function:
   returnFileLineByPhrase

  Description:
   Retrieves lines of text from a file line by line, saving them to
   a string, and then uses that string as an argument for the phraseExists()
   function to see if the incoming "phrase" parameter is contained in the
   line. If the phrase is found, the file line string that contained the
   parameter phrase is returned to the caller.

  Input:
   filePath             - A reference to a constant string object type that
                          contains the file path for the file we will be
			  opening for reading.
			  
   phrase               - A reference to a constant string object type that
                          contains a string of characters(phrase) we will be
			  looking for in the file we opened for reading.

  Output:
   string               - A constant string type that contains the entire
                          file line that the phrase was found on. Else, the
			  string "-1" is returned.
*/
const std::string returnFileLineByPhrase(const std::string& filePath,
					 const std::string& phrase)
{
  struct stat file;
  std::string tempLine;
  bool exists = false;
  
  if(stat(filePath.c_str(), &file) == 0 && S_ISREG(file.st_mode))
    {
      std::ifstream inFile(filePath, std::ifstream::in);
      
      while(std::getline(inFile, tempLine, '\n'))
	{
	  if(phraseExists(tempLine, phrase))
	    {
	      exists = true;
	      break;
	    }
	}

      inFile.close();      
    }

  if(exists)
    {
      return tempLine;
    }
  else
    {
      return "-1";
    }

     
} // end of "returnFileLineByPhrase"



/*
  Function:
   phraseExists

  Description:
   Scans an incoming string for a matching string dubbed "phrase".

  Input:
   line                 - A reference to a constant string type that
                          contains a line of characters extracted
			  from a file.
  
   phrase               - A reference to a constant string type that
                          contains the string of characters(phrase)
			  we're searching for in the line parameter.

  Output:
   bool                 - A result of true if the phrase existed in
                          the line, false otherwise.
*/
bool phraseExists(const std::string& line, const std::string& phrase)
{
  std::string temp;
  bool phraseExists = false;

  for(int i = 0; i < line.length(); i++)
    {
      if(line.at(i) == phrase.at(0))
	{
	  for(int j = 0; j < phrase.length() && i + j < line.length(); j++)
	    {
	      if(line.at(i + j) == phrase.at(j))
		{
		  temp.push_back(phrase.at(j));
		}
	    }
	}

      if(temp == phrase)
	{
	  phraseExists = true;
	  break;
	}
      else
	{
	  temp.clear();
	}
    }

  return phraseExists;
} // end of "phraseExists"



/*
  Function:
   fixStatLine

  Description:
   The incoming /proc/[pid]/stat needs to be parsed for process data.
   The command is the second "value" delimited by whitespace.  The command
   always ends in a ')', but sometimes the command itself contains
   parenthesese. This function truncates the first portion of the string
   returning the first element that is not a whitespace or a ')' character
   after the last ')' character.

  Input:
   line                 - A reference to a constant string object type that
                          holds the /proc/[pid]/stat line that shal be
			  truncated.

  Output:
   string               - The resulting truncated stat line string.
 */
const std::string fixStatLine(const std::string& line)
{
  std::string temp;
  int i;

  if(line.empty())
    {
      return "";
    }
  
  for(i = 0; line.at(i) != '('; i++);

  while(i < line.length() && line.at(i) != ')')
    {
      i++;
    }

  while(i < line.length() && line.at(i) != ' ')
    {
      i++;
    }

  if(i < line.length())
    {
      i++;
    }

  for(int j = i; j < line.length(); j++)
    {
      temp.push_back(line.at(j));
    }
  
  if(temp.empty())
    {
      return "-1";
    }
  else
    {
      return temp;
    }
} // end of "fixStatLine"



/*
  Function:
   doubleToStr

  Description:
   Converts an incoming double type to a string.  The second parameter
   determines the amount of "precision" there are in decimal places
   to append.

  Input:
   val                  - A reference to a constant double type that
                          will be converted to a string.

   precision            - A reference to a constant integer type that
                          determines the number of decimal places the
			  caller chose to store in the string.
  Output:
   string               - A const string object type that is the result
                          of the double to string conversion.
*/
const std::string doubleToStr(const double& val, const int& precision)
{
  std::string valString = std::to_string(val);
  std::string temp;

  int i;
  for(i = 0; i < valString.length() && valString.at(i) != '.'; i++)
    {
      temp.push_back(valString.at(i));
    }

  if(precision > 0)
      {
      if(i != valString.length() && valString.at(i) == '.')
	{
	  temp.push_back(valString.at(i));
	  i++;
      
	  for(int j = 0; j < precision && i < valString.length(); j++, i++)
	    {
	      temp.push_back(valString.at(i));
	    }
	}
    }
  
  return temp;
} // end of "doubleToStr"




/*
  Function:
   isNumericString

  Description:
   Traverses a string and checks that all characters are numeric characters.
   Returns true if only numeric characters are found, false otherwise.

  Input:
   inString             - A reference to a constant string object that
                          holds ASCII characters to be tested if they
			  are numeric or not.
  
  Output:
   bool                 - A bool object that is true if all characters
                          in the inString were numeric, false otherwise.
*/
bool isNumericString(const std::string& inString)
{

  if(inString.empty())
    {
      return false;
    }
  
  for(std::string::const_iterator it = inString.begin();
      it != inString.end(); it++)
    {
      if(*it < '0' || *it > '9')
	{
	  return false;
	}
    }

  return true;
} // end of "isNumericString"
