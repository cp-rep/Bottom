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



/*
  Function:
   CreateFileCSV

  Description:

  Input:

  Output:
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

  Output:
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

  Output:
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

  Input:

  Output:
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

  Input:

  Output:
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

  Input:

  Output:
*/
void defineCpusLine(std::vector<std::string>& allTopLines)
{
  std::string cpusLine;
  cpusLine = "%Cpu(s):      us,      sy,      ni,      id,      wa,      hi,      si,      st";
  allTopLines.push_back(cpusLine);
} // end of "defineCpusLine"



/*
  Function:
   extractProcessStateCount

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
      uidt = stringToInt(parsedLine.at(1));
	      
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
      tempInt = stringToInt(parsedLine.at(1));
      allProcessInfo[currentPid]->setVIRT(tempInt);
    }

  // get RES
  lineString = returnFileLineByPhrase(filePath, "VmRSS");

  if(lineString != "-1")
    {
      parsedLine = parseLine(lineString);
      tempInt = stringToInt(parsedLine.at(1));
      allProcessInfo[currentPid]->setRES(tempInt);
    }

  // get SHR
  lineString = returnFileLineByPhrase(filePath, "RssFile");

  if(lineString != "-1")
    {
      parsedLine = parseLine(lineString);
      tempInt = stringToInt(parsedLine.at(1));
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
      tempInt = stringToInt(parsedLine.at(15));
      allProcessInfo[currentPid]->setPR(tempInt);

      // get NI
      tempInt = stringToInt(parsedLine.at(16));
      allProcessInfo[currentPid]->setNI(tempInt);

      // get S
      allProcessInfo[currentPid]->setS(lineString.at(0));

      // get %CPU for current process

      utime = stringToInt(parsedLine.at(11));
      cutime = stringToInt(parsedLine.at(12));
      pstart = stringToInt(parsedLine.at(19));
      percent = (utime + cutime)/(uptime.getTotalSeconds() - (pstart/100));
      /*
      percent = std::ceil(percent * 100);
      percent = percent /100;
      */
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
  tempInt = stringToInt(parsedLine.at(0));
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
    tempTopString.append(" 0");
    tempTopString.append(" users,  load average: ");
    tempTopString.append(parsedLoadAvg.at(0));
    tempTopString.append(", ");
    tempTopString.append(parsedLoadAvg.at(1));
    tempTopString.append(", ");
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
  memInfo.setMemTotal(stringToInt(parsedLine.at(1)));

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 2);
  parsedLine = parseLine(fileLine);
  memInfo.setMemFree(stringToInt(parsedLine.at(1)));

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 3);
  parsedLine = parseLine(fileLine);
  memInfo.setMemAvailable(stringToInt(parsedLine.at(1)));

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 4);
  parsedLine = parseLine(fileLine);
  memInfo.setBuffers(stringToInt(parsedLine.at(1)));	  

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 5);
  parsedLine = parseLine(fileLine);
  memInfo.setCached(stringToInt(parsedLine.at(1)));	  	  

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 15);
  parsedLine = parseLine(fileLine);
  memInfo.setSwapTotal(stringToInt(parsedLine.at(1)));

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 16);
  parsedLine = parseLine(fileLine);
  memInfo.setSwapFree(stringToInt(parsedLine.at(1)));

  fileLine = returnFileLineByNumber(_PROC_MEMINFO, 26);
  parsedLine = parseLine(fileLine);

  memInfo.setSReclaimable(stringToInt(parsedLine.at(1)));
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
   Traverses an incoming string counting each whitespace character.  When the
   count of whitespaces is reached, the next non whitespace elements are
   appended to a new string until a new white space character is found.
   That string is returned to the caller.

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

  Output:
  
 */
const int stringToInt(const std::string str)
{
  int val = 0;
  if(!str.empty())
    {
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

  Output:
  
 */
const double stringToDouble(const std::string str)
{
  double val = 0;
  if(!str.empty())
    {
      std::stringstream container(str);
      container >> val;
    }
  return val;  
} // end of "stringToDouble"



/*
  Function:
   returnFileLineByPhrase

  Description:
   Retrieves lines of text from a file line by line, saves that line to
   a string, and then sends that string off to the phraseExists() function
   to see if the incoming "phrase" parameter is contained in that line.
   If the phrase is found, the file line string that contained the
   parameter phrase is returned to the caller.

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
   Scans an incoming string for a matching string dubbed "phrase".

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
   The incoming /proc/[pid]/stat needs to be parsed for process data.
   The command is the second "value" delimited by whitespace.  The command
   always ends in a ')', but sometimes the command itself contains parenthesese.
   This function truncates the first portion of the string returning the first
   element that is not a whitespace or a ')' character after the last ')' character.

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
   Converts an incoming double type to a string.  The second parameter
   determines the amount of "precision" there are in decimal places
   to append.

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
