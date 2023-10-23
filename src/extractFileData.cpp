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



/*
  Function:
   extractProcComm

  Description:

  Input:

  Output:
*/
void extractProcComm(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
		     const int pid)
{
  std::string filePath = _PROC + std::to_string(pid);
  filePath.append(_COMM);
  std::string lineString = returnFileLineByNumber(filePath, 1);
  allProcessInfo[pid]->setCOMMAND(lineString);
} // end of "extractProcComm"




/*
  Function:
   defineTasksLine

  Description:

  Input:

  Output:
*/
void defineTasksLine(const TaskInfo& taskInfo,
		     std::vector<std::string>& allTopLines)
{
  std::string tasksLine;
  
  tasksLine = "Tasks: ";
  tasksLine.append(std::to_string(taskInfo.getTotal()));
  tasksLine.append(" total, ");
  tasksLine.append(std::to_string(taskInfo.getRunning()));
  tasksLine.append(" running, ");
  tasksLine.append(std::to_string(taskInfo.getSleeping()));
  tasksLine.append(" sleeping, ");
  tasksLine.append(std::to_string(taskInfo.getStopped()));
  tasksLine.append(" stopped, ");
  tasksLine.append(std::to_string(taskInfo.getZombie()));
  tasksLine.append(" zombie");

  allTopLines.push_back(tasksLine);
} // end of "defineTasksLine"



/*
  Function:
   defineCPULine

  Description:

  Input:
  
  Output:
*/
void extractProcessStateCount(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
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
	case 'D':
	  unSleep++;
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
  total = taskInfo.calcTotal();
  taskInfo.setSleeping(sleeping);
  taskInfo.setTotal(total);
} // end of "extractProcessStateCount"



/*
  Function:
   defineCPULine

  Description:

  Input:

  Output:
 */
void defineCPULine(const CPUInfo& cpuInfo,
		   std::vector<std::string>& allTopLines)
{
  std::string cpuLine;

  cpuLine = "%CPU(s): ";
  cpuLine.append(doubleToStr(cpuInfo.getAvgUs(), 1));
  cpuLine.append(" us, ");
  cpuLine.append(doubleToStr(cpuInfo.getAvgSy(), 1));
  cpuLine.append(" sy, ");
  cpuLine.append(doubleToStr(cpuInfo.getAvgNi(), 1));  
  cpuLine.append(" ni, ");
  cpuLine.append(doubleToStr(cpuInfo.getAvgId(), 1));    
  cpuLine.append(" id, ");
  cpuLine.append(doubleToStr(cpuInfo.getAvgWa(), 1));      
  cpuLine.append(" wa, ");
  cpuLine.append("N/A");
  cpuLine.append(" si, ");
  cpuLine.append(doubleToStr(cpuInfo.getAvgSt(), 1));  
  cpuLine.append(" st, ");
  allTopLines.push_back(cpuLine);
} // end of "defineCPULine"



/*
  Function:
   extractProcStatData

  Description:

  Input:

  Output:
*/
void extractProcStatData(CPUInfo& cpuInfo)
{
  std::string filePath;
  std::string lineString;
  std::string fileLine;  
  std::vector<std::string> parsedLine;
  int tempInt;
  const double ticks = (double)sysconf(_SC_CLK_TCK);
  
  filePath = _PROC;
  filePath.append(_STAT);
  lineString = returnFileLineByNumber(filePath, 1);
  parsedLine = parseLine(lineString);
  cpuInfo.setUs(convertToInt(parsedLine.at(1)));
  cpuInfo.setNi(convertToInt(parsedLine.at(2)));
  cpuInfo.setSy(convertToInt(parsedLine.at(3)));
  cpuInfo.setId(convertToInt(parsedLine.at(4)));
  cpuInfo.setWa(convertToInt(parsedLine.at(5)));
  cpuInfo.setIrq(convertToInt(parsedLine.at(6)));
  cpuInfo.setSirq(convertToInt(parsedLine.at(7)));
  cpuInfo.setSt(convertToInt(parsedLine.at(8)));
  cpuInfo.setGu(convertToInt(parsedLine.at(9)));
  cpuInfo.setGun(convertToInt(parsedLine.at(10)));
  cpuInfo.setTicks(ticks);
  cpuInfo.setJiffs(cpuInfo.calculateJiffs());
} // end of "extractProcStatData"



/*
  Function:
   extractProcPidStatus

  Description:

  Input:

  Output:
*/
void extractProcPidStatus(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			  MemInfo& memInfo,
			  SecondsToTime& uptime,
			  const int currentPid)
{
  const std::string currentProcessPath = _PROC + std::to_string(currentPid);  
  std::string filePath;
  std::string lineString;
  std::string fileLine;  
  std::vector<std::string> parsedLine;
  int tempInt;

  filePath = currentProcessPath;
  filePath.append(_STATUS);
  lineString = returnPhraseLine(filePath, "Gid");

  // a return value of "-1" is returned upon error. check for error
  if(lineString != "-1")
    {
      struct passwd userData;
      struct passwd* userDataPtr;
      uid_t uidt;
      char buff[1024];

      parsedLine = parseLine(lineString);
      uidt = convertToInt(parsedLine.at(1));
	      
      if(!(getpwuid_r(uidt, &userData, buff, sizeof(buff), &userDataPtr)))
	{
	  allProcessInfo[currentPid]->setUSER(userData.pw_name);
	}
      else
	{
	  allProcessInfo[currentPid]->setUSER(userData.pw_name);
	}
    }
  else
    {
      allProcessInfo[currentPid]->setUSER("-1");
    }

  // get VIRT
  lineString = returnFileLineByPhrase(filePath, "VmSize");
	  
  if(lineString != "-1")
    {
      parsedLine = parseLine(lineString);
      tempInt = convertToInt(parsedLine.at(1));
      allProcessInfo[currentPid]->setVIRT(tempInt);
    }

  // get RES
  lineString = returnFileLineByPhrase(filePath, "VmRSS");

  if(lineString != "-1")
    {
      parsedLine = parseLine(lineString);
      tempInt = convertToInt(parsedLine.at(1));
      allProcessInfo[currentPid]->setRES(tempInt);
    }

  // get SHR
  lineString = returnFileLineByPhrase(filePath, "RssFile");

  if(lineString != "-1")
    {
      parsedLine = parseLine(lineString);
      tempInt = convertToInt(parsedLine.at(1));
      allProcessInfo[currentPid]->setSHR(tempInt);
    }

  // get PR
  filePath = currentProcessPath;
  filePath.append(_STAT);
  lineString = returnFileLineByNumber(filePath, 1);

  if(lineString != "-1")
    {
      double utime = 0;
      double cutime = 0;
      double pstart = 0;
      double percent = 0;

      // get update
      fileLine = returnFileLineByNumber(_UPTIME, 1);
      parsedLine = parseLine(fileLine);
      percent = stringToDouble(parsedLine.at(0));
      uptime.setTotalSeconds(percent);
      allProcessInfo[currentPid]->setCPUUsage(percent);

      // get priority
      lineString = fixStatLine(lineString);
      parsedLine = parseLine(lineString);
      tempInt = convertToInt(parsedLine.at(15));
      allProcessInfo[currentPid]->setPR(tempInt);

      // get NI
      tempInt = convertToInt(parsedLine.at(16));
      allProcessInfo[currentPid]->setNI(tempInt);

      // get S
      allProcessInfo[currentPid]->setS(lineString.at(0));

      // get %CPU for current process

      utime = convertToInt(parsedLine.at(11));
      cutime = convertToInt(parsedLine.at(12));
      pstart = convertToInt(parsedLine.at(19));
      percent = (utime + cutime)/(uptime.getTotalSeconds() - (pstart/100));
      percent = std::ceil(percent * 100);
      percent = percent /100;
      allProcessInfo[currentPid]->setCPUUsage(percent);

      // get TIME+ (CPU time)
      allProcessInfo[currentPid]->setCpuRawTime(utime + cutime);
      SecondsToTime timePlus((utime + cutime)/((double)sysconf(_SC_CLK_TCK)));
      std::string timePlusString = timePlus.returnHHMMSS(timePlus.getHours(),
							 timePlus.getMinutes(),
							 timePlus.getSeconds());
      allProcessInfo.at(currentPid)->setProcessCPUTime(timePlusString);

      // get %MEM
      percent = allProcessInfo[currentPid]->getRES();
      percent = percent/(double)memInfo.getMemTotal();
      percent = std::ceil(percent * 1000.0);
      percent = percent/10;
      allProcessInfo[currentPid]->setMEMUsage(percent);
    }

} // end of "extractProcPidStatus"




/*
  Function:
   extractTopWinData

  Description:

  Input:

  Output:
*/
void extractProcUptimeLoadavg(SecondsToTime& uptime,
			      std::vector<std::string>& allTopLines)
{
  int tempInt;
  std::string fileLine;
  std::vector<std::string> parsedLine;
  std::string tempLine;
  time_t rawtime;
  struct tm* timeinfo;

  fileLine = returnFileLineByNumber(_UPTIME, 1);
  parsedLine = parseLine(fileLine);
  tempInt = convertToInt(parsedLine.at(0));
  uptime.setHours(uptime.convertToHours(tempInt));
  uptime.setMinutes(uptime.convertToMinutes(tempInt));
  uptime.setSeconds(uptime.findRemainingSeconds(tempInt));
  uptime.setTotalSeconds(tempInt);
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  tempLine = uptime.returnHHMMSS(timeinfo->tm_hour,
				 timeinfo->tm_min,
				 timeinfo->tm_sec);
  fileLine = returnFileLineByNumber("/proc/loadavg", 1);
  parsedLine = parseLine(fileLine);
  allTopLines.push_back(createTopLine(tempLine,
				      uptime.getHours()/24,
				      uptime.getHours() % 24,
				      uptime.getMinutes(),
				      parsedLine));
} // end of "extractTopWinData"



/*
  Function:
   createTopLine

  Description:
*/
const std::string createTopLine(const std::string HHMMSS,
				const int numDays,
				const int numHours,
				const int numMinutes,
				const std::vector<std::string> parsedLoadAvg)
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
    tempTopString.append("0");
    tempTopString.append(" users, load average: ");
    tempTopString.append(parsedLoadAvg.at(0));
    tempTopString.append(" ");
    tempTopString.append(parsedLoadAvg.at(1));
    tempTopString.append(" ");
    tempTopString.append(parsedLoadAvg.at(2));

    return tempTopString;
} // end of "creatTopLine"



/*
  Function:
   extractMemInfoData

  Description:

  Input:

  Output:
*/
void extractMemInfoData(MemInfo& memInfo)
{
  std::string fileLine;
  std::vector<std::string> parsedLine;
  
  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 1);
  parsedLine = parseLine(fileLine);
  memInfo.setMemTotal(convertToInt(parsedLine.at(1)));

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 2);
  parsedLine = parseLine(fileLine);
  memInfo.setMemFree(convertToInt(parsedLine.at(1)));

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 3);
  parsedLine = parseLine(fileLine);
  memInfo.setMemAvailable(convertToInt(parsedLine.at(1)));

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 4);
  parsedLine = parseLine(fileLine);
  memInfo.setBuffers(convertToInt(parsedLine.at(1)));	  

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 5);
  parsedLine = parseLine(fileLine);
  memInfo.setCached(convertToInt(parsedLine.at(1)));	  	  

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 15);
  parsedLine = parseLine(fileLine);
  memInfo.setSwapTotal(convertToInt(parsedLine.at(1)));

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 16);
  parsedLine = parseLine(fileLine);
  memInfo.setSwapFree(convertToInt(parsedLine.at(1)));

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 26);
  parsedLine = parseLine(fileLine);

  memInfo.setSReclaimable(convertToInt(parsedLine.at(1)));
  memInfo.setMemUsed(memInfo.calculateMemUsed());
  memInfo.setSwapUsed(memInfo.calculateSwapUsed());
  memInfo.setBuffCache(memInfo.calculateBuffCache());  
} // end of "extractMemInfoData"



/*
  Function:
   findDeadProcesses

  Description:

  Input:

  Output:
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

  Input:

  Output:
*/
void removeDeadProcesses(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			 const std::vector<int>& pidsDead)
{
  for(int i = 0; i < pidsDead.size(); i++)
    {
      if(allProcessInfo.count(pidsDead.at(i)) > 0)
	{
	  delete(allProcessInfo[pidsDead.at(i)]);
	  allProcessInfo.erase(pidsDead.at(i));
	}
    }  
} // end of "removeDeadProcesses"





/*
  Function:
   setStringMiB

  Description:

  Input:

  Output:
*/
const std::string setStringMiB(const std::string memTotal,
			       const std::string memFree,
			       const std::string memUsed,
			       const std::string buffCache)
{
  std::string tempMiB;
  
  tempMiB.append("MiB Mem: ");
  tempMiB.append(memTotal);
  tempMiB.append(" total, ");
  tempMiB.append(memFree);
  tempMiB.append(" free, ");
  tempMiB.append(memUsed);
  tempMiB.append(" used, ");
  tempMiB.append(buffCache);
  tempMiB.append(" buff/cache");

  return tempMiB;
} // end of "setStringMiB"



/*
  Function:
   setStringSwap
  Description:

  Input:

  Output:
*/
const std::string setStringSwap(const std::string swapTotal,
				const std::string swapFree,
				const std::string swapUsed,
				const std::string memAvailable)
{
  std::string tempSwap;
  
  tempSwap.append("MiB Swap: ");
  tempSwap.append(swapTotal);
  tempSwap.append(" total, ");
  tempSwap.append(swapFree);
  tempSwap.append(" free, ");
  tempSwap.append(swapUsed);
  tempSwap.append(" used, ");
  tempSwap.append(memAvailable);
  tempSwap.append(" avail/mem");
  
  return tempSwap;
} // end of "setStringSwap"





/*
  Function:
  returnPhraseLine
   
  Description:
  Opens the file at the file path contained in the parameter fileName and
  proceeds to read the file line by line looking for a string containing
  the "phrase" from the parameter const std::string phrase.

  Input:
  fileName                    - a const std::string of the file path for the
                                file to open and read line by line.
  phrase		      - a const std::string for the phrase to search
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

  return tempLine;

} // end of "returnPhraseLine"



/*
  Function:
  returnFirstIntFromLine
   
  Description:
  Finds the first ASCII numeric character(s) from the line parameter,
  converts them to an int type, and then returns the value.

  Input:
  line                        - a const string that will be scanned
                                for numeric characters.
  
  Output:
  const int             - returns the value extract from the line if
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
  do{
    i++;
  } while(line.at(i) < '0' || line.at(i) > '9');

  // push back until we reach a non numeric character
  while(line.at(i) >= '0' && line.at(i) <= '9')
    {
      temp.push_back(line.at(i));
      i++;
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
  returnValByWhitespaceCount

  Description:
  Traverses a whitespace delimited string and retruns a preceding numeric
  value based upon how many whitespaces have been counted.

  Input:
  line                   - a const string reference containing a comma
                           delimited string.

  numWhiteSpaces         - a const int reference representing the number 
                           of whitespaces to skip before reading a value;

  Output:
  const int              - a const int containing a value read from the
                           parameter line.
 */
const int returnValByWhiteSpaceCount(const std::string& line,
				     const int& numWhiteSpaces)
{
  std::string valString;
  int i = 0;
  int spaceCount = 0;

  do{
    i++;
  } while(line.at(i) != ')');

  for(; i < line.length() && spaceCount != numWhiteSpaces; i++)
    {
      if(line.at(i) == ' ')
	{
	  spaceCount++;
	}
    }

  do{
      valString.push_back(line.at(i));
      i++;
    } while(line.at(i) != ' ');

  return stoi(valString);
} // end of "returnValByWhiteSpace"



/*
  Function:
  returnStringByWhiteSpaceCount
  Description:

  Input:

  Output:

 */
const std::string returnStringByWhiteSpaceCount(const std::string& line,
						 const int& numWhiteSpaces)
{
  std::string valString;
  int i = 0;
  int spaceCount = 0;
  
  for(; i < line.length() && spaceCount != numWhiteSpaces; i++)
    {
      if(line.at(i) == ' ')
	{
	  spaceCount++;
	}
    }

  do{
      valString.push_back(line.at(i));
      i++;
    } while(line.at(i) != ' ');

  return valString;
} // end of "returnStringByWhiteSpace"



/*
  Function:
  getFilesPaths

  Description:
  Returns a vector of found existing file paths based on the path given
  from the parameter dirPath.

  Input:

  Output:
 */
const std::vector<std::string> getFilePaths(const std::string& dirPath)
{
  std::vector<std::string> dirNames;
  return dirNames;
} // end of "getFilePaths"



/*
  Function:
  getFileNames
   
  Description:
  Searches the file path given from the parameter dirPath for files.
  If the path exists and files are found, the file names are stored in
  vector<string> type and returned to the caller.
  
  Input:
  dirPath                - a const string reference representing a file
                           path to a directory.
  
  Output:
  NONE
*/
const std::vector<std::string> getFileNames(const std::string& dirPath)
{
  std::vector<std::string> dirNames;
  return dirNames;
} // end of "getFileNames"



/*
  Function:
  getFolderPaths
   
  Description:
  Searches the file path given from the parameter dirPath for files.
  If the path exists and directories represented by only numeric
  characters are found, their file names are converted to integers
  and returned as a vector<int> type to the caller.

  
  Input:
  dirPath                - a const string reference representing a file
                           path to a directory.  
  Output:
  NONE
*/
const std::string getFolderPaths(const std::string& dirPath)
{
  struct stat dir;

  if(stat(dirPath.c_str(), &dir) == 0 && S_ISDIR(dir.st_mode))
    {
      return "Yes";
    }
  else
    {
      return "No";
    }
} // end of "getNumberedFolders"



/*
  Function:
  testNumericDir

  Description:

  Input:

  Output:
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
} // end of "getNumberedFolders"



/*
  Function:
  parseLine

  Description:

  Input:

  Output:
 */
std::vector<std::string> parseLine(const std::string& str)
{
  std::vector<std::string> parsedString;
  std::string temp;
  
  for(int i = 0; i < str.length(); i++)
    {
      while((str.at(i) == '\t' || str.at(i) == ' ') && i < str.length())
	{
	  if(!temp.empty())
	    {
	      parsedString.push_back(temp);
	      temp.clear();
	    }
	  i++;
	}
      temp.push_back(str.at(i));
    }

  if(!temp.empty())
    {
      parsedString.push_back(temp);
    }

  return parsedString;
} // end of "parseLine"



/*
  Function:
  returnLineFromPipe
  
  Description:
  
  Input:
  
  Output:

 */
const std::string returnLineFromPipe(const std::string& comm,
				     const char* mode,
				     const int& lineNum)
{
  FILE* pipe;
  std::string line;;
  char c = 0;

  pipe = popen(comm.c_str(), mode);

  if(pipe == nullptr)
    {
      perror("popen() failed to open users program.");
      exit(EXIT_FAILURE);
    }

  for(int i = 0; i < lineNum - 1; i++)
    {
      while(fread(&c, sizeof c, 1, pipe))
	{
	  if(c == '\n')
	    break;
	}
    }

  while(fread(&c, sizeof c, 1, pipe))
    {
      if(c == '\n')
	{
	  break;
	}
      else
	{
	  line.push_back(c);
	}
    }

  pclose(pipe);

  return line;
} // end of "returnLineFromPipe"



/*
  Function:
  listDirContents

  Description:

  Input:

  Output:
 */
const std::string listDirContents()
{
  FILE* listFile;
  std::string dirContents;
  char c = 0;

  listFile = popen("ls", "r");

  if(listFile == nullptr)
    {
      perror("popen() failed to open ls program.");
      exit(EXIT_FAILURE);
    }

  while(fread(&c, sizeof c, 1, listFile))
    {
      dirContents.push_back(c);
    }

  pclose(listFile);

  return dirContents;
} // end of "listDirContents"



/*
  Function:
  findNumericDirsPipe

  Description:

  Input:

  Output:
 */
const std::vector<int> findNumericDirsPipe(const std::string& dirPath)
{
  FILE* pipe;
  std::string command = "ls ";
  std::vector<int> dirs;
  std::string fullPath;
  std::string numFolder;
  std::unordered_map<int, int> pids;
  char c = 0;

  command.append(dirPath);
  pipe = popen(command.c_str(), "r");

  if(pipe == nullptr)
    {
      perror("popen() failed to open ls program.");
      exit(EXIT_FAILURE);
    }

  while(fread(&c, sizeof c, 1, pipe))
    {
      if(c >= '0' && c <= '9')
	{
	  numFolder.push_back(c);
	}
      else if(c == '\n')
	{
	  fullPath.clear();
	  fullPath.append(dirPath);
	  fullPath.append(numFolder);

	  if(true == testNumericDir(fullPath))
	    {
	      int val;
	      std::stringstream container(numFolder);
	      container >> val;

	      if(pids[val] == 0)
		{
		  dirs.push_back(val);
		  pids[val]++;
		}
	    }
	  numFolder.clear();
	}
    }

  pclose(pipe);
  
  return dirs;
} // end of "findNumericDirsPipe"



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
}
  


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
  convertToInt

  Description:

  Input:

  Output:
  
 */
const int convertToInt(const std::string str)
{
  int val = 0;
  if(!str.empty())
    {
      std::stringstream container(str);
      container >> val;
    }
  return val;
} // end of "convertToInt"


const double stringToDouble(const std::string str)
{
  double val = 0;
  if(!str.empty())
    {
      std::stringstream container(str);
      container >> val;
    }
  return val;  
}



/*
  Function:
  returnFileLineByPhrase

  Description:


  Input:

  Output:

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

     
} // end of "returnFileLineByNumber"



/*
  Function:
  phraseExists

  Description:

  Input:

  Output:
  
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

  Input:

  Output:
 */
const std::string fixStatLine(const std::string& line)
{
  std::string temp;
  int i;

  for(i = 0; line.at(i) != ')'; i++);
  
  while(line.at(i) == ')')
    {
      i++;
    }

  i++;

  for(int j = i; j < line.size(); j++)
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

  Input:

  Output:
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

  if(valString.at(i) == '.')
    {
      temp.push_back(valString.at(i));
      i++;
      for(int j = 0; j < precision && i < valString.length(); j++, i++)
	{
	  temp.push_back(valString.at(i)); 
	}
    }

  return temp;
} // end of "doubleToStr"
