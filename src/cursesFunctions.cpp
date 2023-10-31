/*
  File:
   cursesFunctions.cpp

  Description:
   A collection of function declarations for manipulating CursesWindow objects.
   This includes creating, deleting, moving, and sorting the WINDOWs or their
   data.  Some functions for making necessary related calculations are
   also included.  
 */
#include "cursesFunctions.hpp"
#include <algorithm>



/*
  Function:
   initializeCurses

  Description:
*/
void initializeCurses()
{
  initscr();

  if(has_colors())
    {
      start_color();
      init_pair(_WHITE_TEXT, COLOR_WHITE, COLOR_BLACK);
      init_pair(_BLACK_TEXT, COLOR_BLACK, COLOR_WHITE);
    }
  
  curs_set(0);
  timeout(0);
  noecho();
  cbreak();
  keypad(stdscr, true);
  nodelay(stdscr, true);
} // end of "initializeCurses"



/*
  Function:
   initializeWindows
   
  Description:
*/
void initializeWindows(std::unordered_map<int, CursesWindow*>& wins,		       
		       MainWindow& mainWin,
		       TopWindow& topWin,
		       TasksWindow& tasksWin,
		       CpuWindow& cpuWin,
		       MemWindow& memWin,
		       PIDWindow& PIDWin,
		       USERWindow& USERWin,
		       PRWindow& PRWin,
		       NIWindow& NIWin,
		       VIRTWindow& VIRTWin,
		       RESWindow& RESWin,
		       SHRWindow& SHRWin,
		       SWindow& SWin,
		       PercentCPUWindow& PercentCPUWin,
		       PercentMEMWindow& PercentMEMWin,
		       TIMEWindow& TIMEWin,
		       COMMANDWindow& COMMANDWin,
		       TasksTotalWindow& tasksTotalWin,
		       TasksRunningWindow& tasksRunningWin,
		       TasksStoppedWindow& tasksStoppedWin,
		       TasksSleepingWindow& tasksSleepingWin,
		       TasksZombieWindow& tasksZombieWin,
		       CpuUsWindow& cpuUsWin,
		       CpuSyWindow& cpuSyWin,
		       CpuNiWindow& cpuNiWin,
		       CpuIdWindow& cpuIdWin,
		       CpuWaWindow& cpuWaWin,
		       CpuHiWindow& cpuHiWin,
		       CpuSiWindow& cpuSiWin,
		       CpuStWindow& cpuStWin,
		       MiBMemTotalWindow& miBMemTotalWin,
		       MiBMemFreeWindow& miBMemFreeWin,
		       MiBMemUsedWindow& miBMemUsedWin,
		       MiBBuffCacheWindow& miBBuffCacheWin,
		       MiBSwapTotalWindow& miBSwapTotalWin,
		       MiBSwapFreeWindow& miBSwapFreeWin,
		       MiBSwapUsedWindow& miBSwapUsedWin,
		       MiBMemAvailWindow& miBMemAvailWin)
{
  int numLines;
  int numCols;
  int startY = 0;
  int startX = 0;
  getmaxyx(stdscr, numLines, numCols);

  mainWin.defineWindow(stdscr,
		       "Main",
		       numLines,
		       numCols,
		       startY,
		       startX);
  numLines = 1;
  numCols = numCols;
  startY = _YOFFSET - 6;
  startX = 0;
  topWin.defineWindow(newwin(numLines,
			     numCols,
			     startY,
			     startX),
		      "top",
		      numLines,
		      numCols,
		      startY,
		      startX);
  // define tasks window
  numLines = 1;
  numCols = numCols;
  startY = _YOFFSET - 5;
  startX = 0;
  tasksWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),
			"Tasks",
			numLines,
			numCols,
			startY,
			startX);
  // define cpu window
  numLines = 1;
  numCols = numCols;
  startY = _YOFFSET - 4;
  startX = 0;
  cpuWin.defineWindow(newwin(numLines,
			     numCols,
			     startY,
			     startX),
		      "CPU",
		      numLines,
		      numCols,
		      startY,
		      startX);
  // define mem window
  numLines = 2;
  numCols = numCols;
  startY = _YOFFSET - 3;
  startX = 0;  
  memWin.defineWindow(newwin(numLines,
			     numCols,
			     startY,
			     startX),
		      "MEM",
		      numLines,
		      numCols,
		      startY,
		      startX);
  // define PID window
  numLines = mainWin.getNumLines() -
    memWin.getNumLines() -
    cpuWin.getNumLines() -
    tasksWin.getNumLines() -
    topWin.getNumLines() - 1;
  numCols = 7;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = 0;
  PIDWin.defineWindow(newwin(numLines,
			     numCols,
			     startY,
			     startX),
		      "    PID",
		      numLines,
		      numCols,
		      startY,
		      startX);
  // define USER window
  numCols = 8;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() + 1;
  USERWin.defineWindow(newwin(numLines,
			      numCols,
			      startY,
			      startX),
		       "USER    ",
		       numLines,
		       numCols,
		       startY,
		       startX);
  // define PR window
  numCols = 3;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() + 2;
  PRWin.defineWindow(newwin(numLines,
			    numCols,
			    startY,
			    startX),
		     " PR",
		     numLines,
		     numCols,
		     startY,
		     startX);
  // define NI window
  numCols = 3;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() + 3;
  NIWin.defineWindow(newwin(numLines,
			    numCols,
			    startY,
			    startX),
		     " NI",
		     numLines,
		     numCols,
		     startY,
		     startX);
  // define VIRT window
  numCols = 7;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() + 4;
  VIRTWin.defineWindow(newwin(numLines,
			      numCols,
			      startY,
			      startX),
		       "   VIRT",
		       numLines,
		       numCols,
		       startY,
		       startX);
  // define RES window
  numCols = 6;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() + 5;
  RESWin.defineWindow(newwin(numLines,
			     numCols,
			     startY,
			     startX),
		      "   RES",
		      numLines,
		      numCols,
		      startY,
		      startX);
  // define SHR window
  numCols = 6;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() + 6;
  SHRWin.defineWindow(newwin(numLines,
			     numCols,
			     startY,
			     startX),
		      "   SHR",
		      numLines,
		      numCols,
		      startY,
		      startX);
  // define S window
  numCols = 1;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() +
    SHRWin.getNumCols() + 7;
  SWin.defineWindow(newwin(numLines,
			   numCols,
			   startY,
			   startX),
		    "S",
		    numLines,
		    numCols,
		    startY,
		    startX);
  // define %CPU window
  numCols = 5;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() +
    SHRWin.getNumCols() + 
    SWin.getNumCols() + 8;
  PercentCPUWin.defineWindow(newwin(numLines,
				    numCols,
				    startY,
				    startX),
			     " %CPU",
			     numLines,
			     numCols,
			     startY,
			     startX);
  // define %MEM window
  numCols = 5;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() +
    SHRWin.getNumCols() + 
    SWin.getNumCols() +
    PercentCPUWin.getNumCols() + 9;
  PercentMEMWin.defineWindow(newwin(numLines,
				    numCols,
				    startY,
				    startX),
			     " %MEM",
			     numLines,
			     numCols,
			     startY,
			     startX);
  // define TIME+ window
  numCols = 9;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() +
    SHRWin.getNumCols() + 
    SWin.getNumCols() +
    PercentCPUWin.getNumCols() + 
    PercentMEMWin.getNumCols() + 10;  
  TIMEWin.defineWindow(newwin(numLines,
			      numCols,
			      startY,
			      startX),
		       "    TIME+",
		       numLines,
		       numCols,
		       startY,
		       startX);
  // define COMMAND window
  numCols = 48;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() +
    SHRWin.getNumCols() + 
    SWin.getNumCols() +
    PercentCPUWin.getNumCols() + 
    PercentMEMWin.getNumCols() +
    TIMEWin.getNumCols() + 11;
  COMMANDWin.defineWindow(newwin(numLines,
				 numCols,
				 startY,
				 startX), 
			  "COMMAND",
			  numLines,
			  numCols,
			  startY,
			  startX);
  COMMANDWin.fixCOMMANDWinName();
  // define TasksTotalWindow
  numCols = 4;
  numLines = 1;
  startY = 1;
  startX = 6;
  tasksTotalWin.defineWindow(newwin(numLines,
				    numCols,
				    startY,
				    startX),
			     "total",
			     numLines,
			     numCols,
			     startY,
			     startX);
  // define TasksRunningWindow
  numCols = 4;
  numLines = 1;
  startY = 1;
  startX = 17;
  tasksRunningWin.defineWindow(newwin(numLines,
				    numCols,
				    startY,
				    startX),
			     "running",
			     numLines,
			     numCols,
			     startY,
			     startX);
  // define TasksSleepingWindow
  numCols = 4;
  numLines = 1;
  startY = 1;
  startX = 30;
  tasksSleepingWin.defineWindow(newwin(numLines,
				    numCols,
				    startY,
				    startX),
			     "sleeping",
			     numLines,
			     numCols,
			     startY,
			     startX);
  // define TasksStoppedWindow
  numCols = 4;
  numLines = 1;
  startY = 1;
  startX = 44;
  tasksStoppedWin.defineWindow(newwin(numLines,
				    numCols,
				    startY,
				    startX),
			       "stopped",
			       numLines,
			       numCols,
			       startY,
			       startX);
  // define TasksZombieWindow
  numCols = 4;
  numLines = 1;
  startY = 1;
  startX = 57;
  tasksZombieWin.defineWindow(newwin(numLines,
				       numCols,
				       startY,
				     startX),
			      "zombie",
			      numLines,
			      numCols,
			      startY,
			      startX);
  // define cpu user time window
  numCols = 5;
  numLines = 1;
  startY = 2;
  startX = 8;
  cpuUsWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),
			"us",
			numLines,
			numCols,
			startY,
			startX);
  // define cpu system time window
  numCols = 5;
  numLines = 1;
  startY = 2;
  startX = 17;
  cpuSyWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),
			"sy",
			numLines,
			numCols,
			startY,
			startX);
  // define cpu user nice time window
  numCols = 5;
  numLines = 1;
  startY = 2;
  startX = 26;
  cpuNiWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),
			"ni",
			numLines,
			numCols,
			startY,
			startX);
  // define cpu idle time window
  numCols = 5;
  numLines = 1;
  startY = 2;
  startX = 35;
  cpuIdWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),
			"id",
			numLines,
			numCols,
			startY,
			startX);
  // define cpu wait time window
  numCols = 5;
  numLines = 1;
  startY = 2;
  startX = 44;
  cpuWaWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),
			"wa",
			numLines,
			numCols,
			startY,
			startX);
  // define cpu hardware interrupt time window
  numCols = 5;
  numLines = 1;
  startY = 2;
  startX = 53;
  cpuHiWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),  
			"hi",
			numLines,
			numCols,
			startY,
			startX);
  // define cpu software interrupt time window
  numCols = 5;
  numLines = 1;
  startY = 2;
  startX = 62;
  cpuSiWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),  
			"Si",
			numLines,
			numCols,
			startY,
			startX);
  // define cpu steal time window
  numCols = 5;
  numLines = 1;
  startY = 2;
  startX = 71;
  cpuStWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),  
			"St",
			numLines,
			numCols,
			startY,
			startX);

  // define MiB mem total window
  numCols = 9;
  numLines = 1;
  startY = 3;
  startX = 9;
  miBMemTotalWin.defineWindow(newwin(numLines,
				     numCols,
				     startY,
				     startX),  
			      "total",
			      numLines,
			      numCols,
			      startY,
			      startX);
  // define MiB mem free window
  numCols = 9;
  numLines = 1;
  startY = 3;
  startX = 25;
  miBMemFreeWin.defineWindow(newwin(numLines,
				    numCols,
				    startY,
				    startX),  
			     "free",
			     numLines,
			     numCols,
			     startY,
			     startX);
  // define MiB mem Used window
  numCols = 9;
  numLines = 1;
  startY = 3;
  startX = 40;
  miBMemUsedWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),  
			"used",
			numLines,
			numCols,
			startY,
			startX);
  // define cpu steal time window
  numCols = 9;
  numLines = 1;
  startY = 3;
  startX = 55;
  miBBuffCacheWin.defineWindow(newwin(numLines,
				      numCols,
				      startY,
				      startX),  
			       "buff/cache",
			       numLines,
			       numCols,
			       startY,
			       startX);
  // define MiB swap total window
  numCols = 9;
  numLines = 1;
  startY = 4;
  startX = 9;
  miBSwapTotalWin.defineWindow(newwin(numLines,
				      numCols,
				      startY,
				      startX),  
			       "total",
			       numLines,
			       numCols,
			       startY,
			       startX);
  // define MiB swap free window
  numCols = 9;
  numLines = 1;
  startY = 4;
  startX = 25;
  miBSwapFreeWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),  
			      "free",
			      numLines,
			      numCols,
			      startY,
			      startX);
  // define MiB swap used window
  numCols = 9;
  numLines = 1;
  startY = 4;
  startX = 40;
  miBSwapUsedWin.defineWindow(newwin(numLines,
			       numCols,
			       startY,
			       startX),  
			      "used",
			      numLines,
			      numCols,
			      startY,
			      startX);
  // define MiB Swap avail mem window
  numCols = 9;
  numLines = 1;
  startY = 4;
  startX = 55;
  miBMemAvailWin.defineWindow(newwin(numLines,
				     numCols,
				     startY,
				     startX),  
			      "avil Mem",
			      numLines,
			      numCols,
			      startY,
			      startX);

  // store all windows in hash map
  wins.insert(std::make_pair(_MAINWIN,&mainWin));
  wins.insert(std::make_pair(_TOPWIN, &topWin));
  wins.insert(std::make_pair(_TASKSWIN, &tasksWin));
  wins.insert(std::make_pair(_CPUWIN, &cpuWin));
  wins.insert(std::make_pair(_MEMWIN, &memWin));
  wins.insert(std::make_pair(_PIDWIN, &PIDWin));
  wins.insert(std::make_pair(_USERWIN, &USERWin));
  wins.insert(std::make_pair(_PRWIN, &PRWin));
  wins.insert(std::make_pair(_NIWIN, &NIWin));
  wins.insert(std::make_pair(_VIRTWIN, &VIRTWin));
  wins.insert(std::make_pair(_RESWIN, &RESWin));
  wins.insert(std::make_pair(_SHRWIN, &SHRWin));
  wins.insert(std::make_pair(_SWIN, &SWin));
  wins.insert(std::make_pair(_PROCCPUWIN, &PercentCPUWin));
  wins.insert(std::make_pair(_PROCMEMWIN, &PercentMEMWin));
  wins.insert(std::make_pair(_PROCTIMEWIN, &TIMEWin));
  wins.insert(std::make_pair(_COMMANDWIN, &COMMANDWin));
  wins.insert(std::make_pair(_TASKSTOTAL, &tasksTotalWin));
  wins.insert(std::make_pair(_TASKSRUNNING, &tasksRunningWin));
  wins.insert(std::make_pair(_TASKSSLEEPING,&tasksSleepingWin));
  wins.insert(std::make_pair(_TASKSSTOPPED, &tasksStoppedWin));
  wins.insert(std::make_pair(_TASKSZOMBIE, &tasksZombieWin));
  wins.insert(std::make_pair(_CPUUSWIN, &cpuUsWin));
  wins.insert(std::make_pair(_CPUSYWIN, &cpuSyWin));
  wins.insert(std::make_pair(_CPUNIWIN, &cpuNiWin));
  wins.insert(std::make_pair(_CPUIDWIN, &cpuIdWin));
  wins.insert(std::make_pair(_CPUWAWIN, &cpuWaWin));
  wins.insert(std::make_pair(_CPUHIWIN, &cpuHiWin));
  wins.insert(std::make_pair(_CPUSIWIN, &cpuSiWin));
  wins.insert(std::make_pair(_CPUSTWIN, &cpuStWin));
  wins.insert(std::make_pair(_MIBTOTALWIN, &miBMemTotalWin));
  wins.insert(std::make_pair(_MIBFREEWIN, &miBMemFreeWin));
  wins.insert(std::make_pair(_MIBUSEDWIN, &miBMemUsedWin));
  wins.insert(std::make_pair(_MIBBUFFCACHEWIN, &miBBuffCacheWin));
  wins.insert(std::make_pair(_MIBSWAPTOTALWIN, &miBSwapTotalWin));
  wins.insert(std::make_pair(_MIBSWAPFREEWIN, &miBSwapFreeWin));
  wins.insert(std::make_pair(_MIBSWAPUSEDWIN, &miBSwapUsedWin));
  wins.insert(std::make_pair(_MIBMEMAVAILWIN, &miBMemAvailWin));  
} // end of "initializeWindows"



/*
  Function:
  refreshAllWins

  Description:
*/
void refreshAllWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  std::unordered_map<int, CursesWindow*>::const_iterator it = wins.begin();
  std::vector<int> tempWins;

  // store all currently initialized window indexes
  for(it = wins.begin(); it != wins.end(); it++)
    {
      if(it->second->getWindow() != nullptr)
	{
	  tempWins.push_back(it->first);
	}
    }

  // sort them in ascending order
  std::sort(tempWins.begin(), tempWins.end());

  // refresh the initialized windows
  for(std::vector<int>::iterator vecIt = tempWins.begin();
      vecIt != tempWins.end();
      vecIt++)
    {
      wnoutrefresh(wins.at(*vecIt)->getWindow());
    }
  
} // end of "refreshAllWins"



/*
  Function:
  clearAllWins

  Description:
*/
void clearAllWins(const std::unordered_map<int, CursesWindow*>& wins)
{

  for(int i = _MAINWIN; i <= _TASKSZOMBIE; i++)
    {
      werase(wins.at(i)->getWindow());
    }  
} // end of "clearAllWins"



/*
  Function:
  clearTopWins

  Description:
*/
void clearTopWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  for(int i = _TOPWIN; i <= _MEMWIN; i++)
    {
      werase(wins.at(i)->getWindow());
    }  
} // end of "clearBottomWins"



/*
  Function:
  clearBottomWins

  Description:

  Input:

  Output:
*/
void clearBottomWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      werase(wins.at(i)->getWindow());
    }
} // end of "clearBottomWins"



/*
  Function:
   boldOnAllTopWins

  Description:

  Input:

  Output:
*/
void boldOnAllTopWins(std::unordered_map<int, CursesWindow*>& wins,
		     int attrs)
{
  for(int i = _TASKSTOTAL; i <= _MIBMEMAVAILWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "boldOnAllTopWins"



/*
  Function:
   boldOffAllTopWins

  Description:

  Input:

  Output:
*/
void boldOffAllTopWins(std::unordered_map<int, CursesWindow*>& wins,
		     int attrs)
{
  for(int i = _TASKSTOTAL; i <= _TASKSZOMBIE; i++)
    {
      wattron(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "boldOffAllTopWins"



/*
  Function:
   boldOnTasksWins

  Description:

  Input:

  Output:
*/
void boldOnTasksWins(std::unordered_map<int, CursesWindow*>& wins,
		     int attrs)
{
  for(int i = _TASKSTOTAL; i <= _TASKSZOMBIE; i++)
    {
      wattron(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "boldOnTasksWins"



/*
  Function:
   boldOffTasksWins

  Description:

  Input:

  Output:
*/
void boldOffTasksWins(const std::unordered_map<int, CursesWindow*>& wins,
		      int attrs)
{
  for(int i = _TASKSTOTAL; i <= _TASKSZOMBIE; i++)
    {
      wattroff(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "boldOffTasksWins"



/*
  Function:
   boldOnCpusWins

  Description:

  Input:

  Output:
 */
void boldOnCpusWins(std::unordered_map<int, CursesWindow*>& wins,
		     int attrs)
{
  for(int i = _CPUUSWIN; i <= _CPUSTWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "boldOnCpusWins"




/*

  Function:
   boldOffCpusWins

  Description:

  Input:

  Output:
*/
void boldOffCpusWins(std::unordered_map<int, CursesWindow*>& wins,
		     int attrs)
{
  for(int i = _CPUUSWIN; i <= _CPUSTWIN; i++)
    {
      wattroff(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "boldOffCpusWins




/*
  Function:
   boldOnMemWins

  Description:

  Input:

  Output:
*/
void boldOnMemWins(std::unordered_map<int, CursesWindow*>& wins,
		     int attrs)
{
  for(int i = _MIBTOTALWIN; i <= _MIBMEMAVAILWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "boldOnMemWins"




/*
  Function:
   boldOffMemWins

  Description:

  Input:

  Output:
*/
void boldOffMemWins(std::unordered_map<int, CursesWindow*>& wins,
		     int attrs)
{
  for(int i = _MIBTOTALWIN; i <= _MIBMEMAVAILWIN; i++)
    {
      wattroff(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "boldOffMemWins"



/*
  Function:
   attronBottomWins

  Description:

  Input:

  Output:
*/
void attronBottomWins(const std::unordered_map<int, CursesWindow*>& wins, int attrs)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), COLOR_PAIR(attrs));
    }
} // end of "attronBottomWins"



/*
  Function:
  attroffBottomWins

  Description:

  Input:

  Output:
*/
void attroffBottomWins(const std::unordered_map<int, CursesWindow*>& wins,
		       int attrs)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      wattroff(wins.at(i)->getWindow(), COLOR_PAIR(attrs));
    }  
} // end of "atroffBottomWins"



/*
  Function:
   printTasksData

  Description:

  Input:

  Output:
*/
void printTasksData(const std::unordered_map<int, CursesWindow*>& wins,
		    const TaskInfo& taskInfo)
{
  std::string outString;

  outString = std::to_string(taskInfo.getTotal());
  mvwaddstr(wins.at(_TASKSTOTAL)->getWindow(),
	    0,
	    wins.at(_TASKSTOTAL)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = std::to_string(taskInfo.getRunning());
  mvwaddstr(wins.at(_TASKSRUNNING)->getWindow(),
	    0,
	    wins.at(_TASKSRUNNING)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = std::to_string(taskInfo.getSleeping());
  mvwaddstr(wins.at(_TASKSSLEEPING)->getWindow(),
	    0,
	    wins.at(_TASKSSLEEPING)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = std::to_string(taskInfo.getStopped());
  mvwaddstr(wins.at(_TASKSSTOPPED)->getWindow(),
	    0,
	    wins.at(_TASKSSTOPPED)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = std::to_string(taskInfo.getZombie());
  mvwaddstr(wins.at(_TASKSZOMBIE)->getWindow(),
	    0,
	    wins.at(_TASKSZOMBIE)->getNumCols() - outString.length(),
	    outString.c_str());
} // end of "printTasksData"



/*
  Function:
   printCpusData

  Description:

  Input:

  Output:
*/
void printCpusData(const std::unordered_map<int, CursesWindow*>& wins,
		   const CPUInfo& cpuInfo)
{
  std::string outString;

  outString = doubleToStr(cpuInfo.getAvgUs(), 1);
  mvwaddstr(wins.at(_CPUUSWIN)->getWindow(),
	    0,
	    wins.at(_CPUUSWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  
  outString = doubleToStr(cpuInfo.getAvgSy(), 1);
  mvwaddstr(wins.at(_CPUSYWIN)->getWindow(),
	    0,
	    wins.at(_CPUSYWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(cpuInfo.getAvgNi(), 1);
  mvwaddstr(wins.at(_CPUNIWIN)->getWindow(),
	    0,
	    wins.at(_CPUNIWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(cpuInfo.getAvgId(), 1);
  mvwaddstr(wins.at(_CPUIDWIN)->getWindow(),
	    0,
	    wins.at(_CPUIDWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(cpuInfo.getAvgWa(), 1);
  mvwaddstr(wins.at(_CPUWAWIN)->getWindow(),
	    0,
	    wins.at(_CPUWAWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  
  outString = doubleToStr(cpuInfo.getAvgHi(), 1);
  mvwaddstr(wins.at(_CPUHIWIN)->getWindow(),
	    0,
	    wins.at(_CPUHIWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  //outString = std::to_string(cpuInfo.getAvgSi());
  outString = "0.0";
  mvwaddstr(wins.at(_CPUSIWIN)->getWindow(),
	    0,
	    wins.at(_CPUSIWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(cpuInfo.getAvgSt(), 1);
  mvwaddstr(wins.at(_CPUSTWIN)->getWindow(),
	    0,
	    wins.at(_CPUSTWIN)->getNumCols() - outString.length(),
	    outString.c_str());
} // end of "printCpusData"



/*
  Function:
   printMemMiBData

  Description:

  Input:

  Output:
*/
void printMemMiBData(const std::unordered_map<int, CursesWindow*>& wins,
		     const MemInfo& memInfo)
{
  std::string outString;
  outString = doubleToStr(KiBToMiB(memInfo.getMemTotal()), 1);
  mvwaddstr(wins.at(_MIBTOTALWIN)->getWindow(),
	    0,
	    wins.at(_MIBTOTALWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  
  outString = doubleToStr(KiBToMiB(memInfo.getMemFree()), 1);
  mvwaddstr(wins.at(_MIBFREEWIN)->getWindow(),
	    0,
	    wins.at(_MIBFREEWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(KiBToMiB(memInfo.getMemUsed()), 1);
  mvwaddstr(wins.at(_MIBUSEDWIN)->getWindow(),
	    0,
	    wins.at(_MIBUSEDWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(KiBToMiB(memInfo.getBuffCache()), 1);
  mvwaddstr(wins.at(_MIBBUFFCACHEWIN)->getWindow(),
	    0,
	    wins.at(_MIBBUFFCACHEWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(KiBToMiB(memInfo.getSwapTotal()), 1);
  mvwaddstr(wins.at(_MIBSWAPTOTALWIN)->getWindow(),
	    0,
	    wins.at(_MIBSWAPTOTALWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  
  outString = doubleToStr(KiBToMiB(memInfo.getSwapFree()), 1);
  mvwaddstr(wins.at(_MIBSWAPFREEWIN)->getWindow(),
	    0,
	    wins.at(_MIBSWAPFREEWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(KiBToMiB(memInfo.getSwapUsed()), 1);
  mvwaddstr(wins.at(_MIBSWAPUSEDWIN)->getWindow(),
	    0,
	    wins.at(_MIBSWAPUSEDWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(KiBToMiB(memInfo.getMemAvailable()), 1);
  mvwaddstr(wins.at(_MIBMEMAVAILWIN)->getWindow(),
	    0,
	    wins.at(_MIBMEMAVAILWIN)->getNumCols() - outString.length(),
	    outString.c_str());
} // end of "printMemMiBData"



/*
  Function:
   printTopWins

  Description:

  Input:

  Output:
*/
void printTopWins(const std::unordered_map<int, CursesWindow*>& wins,
		  const std::vector<std::string>& allTopLines)
{
  mvwaddstr(wins.at(_TOPWIN)->getWindow(),
	    0,
	    0,
	    allTopLines.at(0).c_str());
  mvwaddstr(wins.at(_TASKSWIN)->getWindow(),
	    0,
	    0,
	    allTopLines.at(1).c_str());
  mvwaddstr(wins.at(_CPUWIN)->getWindow(),
	    0,
	    0,
	    allTopLines.at(2).c_str());
  mvwaddstr(wins.at(_MEMWIN)->getWindow(),
	    0,
	    0,
	    allTopLines.at(3).c_str());
  mvwaddstr(wins.at(_MEMWIN)->getWindow(),
	    1,
	    0,
	    allTopLines.at(4).c_str());
} // end of "printTopWins"



/*
  Function:
  printWindowNames

  Description:

  Input:

  Output:
*/
void printWindowNames(const std::unordered_map<int, CursesWindow*>& wins)
{
  std::string outString;

  // PID
  outString = wins.at(_PIDWIN)->getWindowName();
  mvwaddstr(wins.at(_PIDWIN)->getWindow(),
	    0,
	    wins.at(_PIDWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  // USER
  outString = wins.at(_USERWIN)->getWindowName();
  mvwaddstr(wins.at(_USERWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
  // PR
  outString = wins.at(_PRWIN)->getWindowName();
  mvwaddstr(wins.at(_PRWIN)->getWindow(),
	    0,
	    wins.at(_PRWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  // NI
  outString = wins.at(_NIWIN)->getWindowName();
  mvwaddstr(wins.at(_NIWIN)->getWindow(),
	    0,
	    wins.at(_NIWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  // VIRT
  outString = wins.at(_VIRTWIN)->getWindowName();
  mvwaddstr(wins.at(_VIRTWIN)->getWindow(),
	    0,
	    wins.at(_VIRTWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  // RES
  outString = wins.at(_RESWIN)->getWindowName();
  mvwaddstr(wins.at(_RESWIN)->getWindow(),
	    0,
	    wins.at(_RESWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  // SHR
  outString = wins.at(_SHRWIN)->getWindowName();
  mvwaddstr(wins.at(_SHRWIN)->getWindow(),
	    0,
	    wins.at(_SHRWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  // S
  outString = wins.at(_SWIN)->getWindowName();
  mvwaddstr(wins.at(_SWIN)->getWindow(),
	    0,
	    wins.at(_SWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  // %CPU
  outString = wins.at(_PROCCPUWIN)->getWindowName();
  mvwaddstr(wins.at(_PROCCPUWIN)->getWindow(),
	    0,
	    wins.at(_PROCCPUWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  // %MEM
  outString = wins.at(_PROCMEMWIN)->getWindowName();
  mvwaddstr(wins.at(_PROCMEMWIN)->getWindow(),
	    0,
	    wins.at(_PROCMEMWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  // TIME+
  outString = wins.at(_PROCTIMEWIN)->getWindowName();
  mvwaddstr(wins.at(_PROCTIMEWIN)->getWindow(),
	    0,
	    wins.at(_PROCTIMEWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  // COMMAND
  outString = wins.at(_COMMANDWIN)->getWindowName();
  mvwaddstr(wins.at(_COMMANDWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
} // end of "printWindowNames"



/*
  Function:
   printProcs

  Description:
   Prints the bottom windows that contain process related data to the screen
   (PID, USER, PR, NI...). The control structures ensure that all printing is
   done in allocated screen space for the CursesWindow objects, both in
   "row/column" screen position as well as memory.

   A simple loop is used to iterate over all the CursesWindow objects to
   print their data.
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values 0-16, or the
			  constants in file _cursesWinConsts.hpp.

   procData             - A reference to a constant unordered map
                          <int, ProcessInfo*> type. procData contains
			  pointers to objects that contain the data for
			  all currently allocated processes. This data
			  can be indexed by the incoming pidList.

   pidList              - A reference to a constant vector<int> type that
                          is a list of the PIDs for all currently allocated
			  processes.

   shiftY               - A reference to a constant integer that represents
                          the window row position to print the next line to
			  the screen. It continually gets incremented until
			  all incoming PIDs have been traversed and printed.

   shiftX               - A reference to a constant ingeger that represents
                          the current shift state position of the bottom
			  windows. It is used as a control structure to
			  ensure only the currently allocated windows
			  are printed and in their correct row/col positions
			  to the MainWindow.
  Output:
   NONE
*/
void printProcs(const std::unordered_map<int, CursesWindow*>& wins,
		const std::unordered_map<int, ProcessInfo*>& procData,
		const std::vector<int>& pidList,
		const int shiftY,
		const int shiftX)
{
  std::string outString;

  for(int i = 0; i < pidList.size() - 1; i++)
    {
      int posY = i + shiftY;

      // ensure nothing is printed over the column titles
      if(posY != 0)
	{
	  // PID
	  if(shiftX <= _PIDWIN && wins.at(_PIDWIN)->getWindow() != nullptr)
	    {
	      outString = std::to_string(procData.at(pidList.at(i))->getPID());
	      mvwaddstr(wins.at(_PIDWIN)->getWindow(),
			posY,
			wins.at(_PIDWIN)->getNumCols() - outString.length(),
			outString.c_str());	
	    }
	  // USER      
	  if(shiftX <= _USERWIN && wins.at(_USERWIN)->getWindow() != nullptr)
	    {
	      outString = procData.at(pidList.at(i))->getUSER();
	      mvwaddstr(wins.at(_USERWIN)->getWindow(),
			posY,
			0,
			outString.c_str());
	    }
	  // PR
	  if(shiftX <= _PRWIN && wins.at(_PRWIN)->getWindow() != nullptr)
	    {
	      const int tempPRVal = procData.at(pidList.at(i))->getPR();
	      if(tempPRVal == -100)
		{
		  outString = "rt";
		}
	      else
		{
		  outString = std::to_string(tempPRVal);
		}

	      mvwaddstr(wins.at(_PRWIN)->getWindow(),
			posY,
			wins.at(_PRWIN)->getNumCols() - outString.length(),
			outString.c_str());
	    }	  
	  // NI
	  if(shiftX <= _NIWIN && wins.at(_NIWIN)->getWindow() != nullptr)
            {
	      outString = std::to_string(procData.at(pidList.at(i))->getNI());
	      mvwaddstr(wins.at(_NIWIN)->getWindow(),
			posY,
			wins.at(_NIWIN)->getNumCols() - outString.length(),
			outString.c_str());
            }
	  // VIRT
	  if(shiftX <= _VIRTWIN && wins.at(_VIRTWIN)->getWindow() != nullptr)
            {
	      outString = std::to_string(procData.at(pidList.at(i))->getVIRT());
	      mvwaddstr(wins.at(_VIRTWIN)->getWindow(),
			posY,
			wins.at(_VIRTWIN)->getNumCols() - outString.length(),
			outString.c_str());
            }
	  // RES
	  if(shiftX <= _RESWIN && wins.at(_RESWIN)->getWindow() != nullptr)
            {
	      outString = std::to_string(procData.at(pidList.at(i))->getRES());
	      mvwaddstr(wins.at(_RESWIN)->getWindow(),
			posY,
			wins.at(_RESWIN)->getNumCols() - outString.length(),
			outString.c_str());
            }
	  // SHR
	  if(shiftX <= _SHRWIN && wins.at(_SHRWIN)->getWindow() != nullptr)
            {
	      outString = std::to_string(procData.at(pidList.at(i))->getSHR());
	      mvwaddstr(wins.at(_SHRWIN)->getWindow(),
			posY,
			wins.at(_SHRWIN)->getNumCols() - outString.length(),
			outString.c_str());
            }
	  // S
	  if(shiftX <= _SWIN && wins.at(_SWIN)->getWindow() != nullptr)
	    {
	      mvwaddch(wins.at(_SWIN)->getWindow(),
		       posY,
		       0,
		       procData.at(pidList.at(i))->getS());
            }
	  // %CPU
	  if(shiftX <= _PROCCPUWIN && wins.at(_PROCCPUWIN)->getWindow() != nullptr)
            {

	      outString = doubleToStr(procData.at(pidList.at(i))->getCPUUsage(), 1);
	      mvwaddstr(wins.at(_PROCCPUWIN)->getWindow(),
			posY,
			wins.at(_PROCCPUWIN)->getNumCols() - outString.length(),
			outString.c_str());
            }
	  // %MEM
	  if(shiftX <= _PROCMEMWIN && wins.at(_PROCMEMWIN)->getWindow() != nullptr)
            {
	      outString = doubleToStr(procData.at(pidList.at(i))->getMEMUsage(), 1);
	      mvwaddstr(wins.at(_PROCMEMWIN)->getWindow(),
			posY,
			wins.at(_PROCMEMWIN)->getNumCols() - outString.length(),
			outString.c_str());
            }
	  // TIME+
	  if(shiftX <= _PROCTIMEWIN && wins.at(_PROCTIMEWIN)->getWindow() != nullptr)
	    {
	      outString = procData.at(pidList.at(i))->getProcessCPUTime();
	      mvwaddstr(wins.at(_PROCTIMEWIN)->getWindow(),
			posY,
			wins.at(_PROCTIMEWIN)->getNumCols() - outString.length(),
			outString.c_str());
            }
	  // COMMAND
	  if(shiftX <= _COMMANDWIN && wins.at(_COMMANDWIN)->getWindow() != nullptr)
            {
	      outString = procData.at(pidList.at(i))->getCOMMAND();
	      mvwaddstr(wins.at(_COMMANDWIN)->getWindow(),
			posY,
			0,
			outString.c_str());
            } 
	}
    }
} // end of "printProcs"



/*
  Function:
   createColorLine

  Description:
   Creates a string of white space chacaters with length of the incoming
   parameter and returns it to the caller.
   
  Input:
   len                  - A reference to a constant integer type which holds
                          the total length of whitespace characters to
			  define.

  Output:
   const std::string    - The resulting string of whitespace characters.
*/
const std::string createColorLine(const int& len)
{
  std::string temp;
  for(int i = 0; i < len; i++)
    {
      temp.push_back(' ');
    }

  return temp;
} // end of "createColorLine"



/*
  Function:
   printColorLine

  Description:
   Prints a solid color line at the position of the incoming "row" variable's
   position to the incoming CursesWindow indexed by the incoming "window"
   variable.
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values 0-16, or the
			  constants in file _cursesWinConsts.hpp.

   row                  - A reference to a constant integer that holds
                          the Y-Position to print the color line to the
			  desired CursesWindow object's window.

   attr                 - A reference to a constant integer that holds the
                          color combination to print.

   window               - A reference to a constant integer that holds the
                          index value of the CursesWindow object to print
			  the color line to.

   colorLine            - A reference to a constant string object which is
                          a string of whitespaces that should be the
			  total number of columns of the window to print
			  it to.
			  
  Output:
   NONE
*/
void printColorLine(const std::unordered_map<int, CursesWindow*>& wins,
		    const int& row,
		    const int& attrs,
		    const int& window,
		    const std::string& colorLine)
{
  wattron(wins.at(window)->getWindow(), COLOR_PAIR(attrs));
  mvwaddstr(wins.at(window)->getWindow(),
	    row,
	    0,
	    colorLine.c_str());
  wattroff(wins.at(window)->getWindow(), COLOR_PAIR(attrs));
} // end of "printColorLine"



/*
  Function:
   shiftBottomWinsLeft

  Description:
   Shifts all the bottom windows left one shift aligning the new first
   window at the leftmost column of the MainWindow screen.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values 0-16, or the
			  constants in file _cursesWinConsts.hpp.
			  
   shiftX               - The current shift state of the bottom windows.
			  
  Output:
   NONE  
*/
void shiftBottomWinsLeft(std::unordered_map<int, CursesWindow*>& wins,
			 const int& shiftX)
{
  int totalShifts = 0;
  int currWin = shiftX;
  int startX = 0;

  // delete the current window at x-position "0" freeing it from memory
  wins.at(currWin)->deleteWindow();

  // move the window index forward to the first window that that needs moving
  // starting at the X-Position of the previously deleted window
  currWin++;

  // get the total number of needed right shifts
  totalShifts = _COMMANDWIN - shiftX; // = getTotalShifts(wins, shiftX + 1);

  for(int i = 0; i < totalShifts; i++, currWin++)
    {
      // set the starting window to the 0 x-position
      if(i == 0)
	{
	  startX = 0;
	}
      // set the proceeding windows to their new starting x-positions
      // which is the starting position of the last window + that windows
      // total number of columns + space (1)
      else
	{
	  startX = wins.at(currWin - 1)->getStartX() +
	           wins.at(currWin - 1)->getNumCols() +
	           1;
	}
      // move the windows until the total shifts have been reached
      wins.at(currWin)->setStartX(startX);
      mvwin(wins.at(currWin)->getWindow(),
	    wins.at(currWin)->getStartY(),
	    wins.at(currWin)->getStartX());
    }  
} // end of "shiftBottomWinsLeft"



/*
  Function:
   shiftBottomWinsRight

  Description:
   Shifts all the bottom windows right one shift aligning the new first
   window at the leftmost column of the MainWindow screen.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values 0-16, or the
			  constants in file _cursesWinConsts.hpp.  
			  
   shiftX               - The current shift state of the bottom windows.
			  
  Output:
   NONE
*/
void shiftBottomWinsRight(std::unordered_map<int, CursesWindow*>& wins,
			  const int& shiftX)
{
  int currWin = shiftX;
  int totalShifts = 0;
  
  // delete the current window at x-position "0" freeing it from memory  
  wins.at(shiftX - 1)->setStartX(0);

  // get the total number of needed shifts
  totalShifts = _COMMANDWIN - shiftX + 1;

  // shift the windows
  for(int i = 0; i < totalShifts; i++, currWin++)
    {
      // get the new starting position of the current window
      wins.at(currWin)->setStartX(wins.at(currWin - 1)->getStartX() +
				  wins.at(currWin - 1)->getNumCols() +
				  1);
      // move the window to the new starting position
      mvwin(wins.at(currWin)->getWindow(),
	    wins.at(currWin)->getStartY(),
	    wins.at(currWin)->getStartX());
    }

  // create the starting window now that the windows have been shifted
  wins.at(shiftX - 1)->createWindow(wins.at(shiftX - 1)->getNumLines(),
				    wins.at(shiftX - 1)->getNumCols(),
				    wins.at(shiftX - 1)->getStartY(),
				    wins.at(shiftX - 1)->getStartX());
} // end of "shiftBottomWinsRight"



/*
  Function:
   drawBoxes

  Description:
   Draws a box for every "WINDOW" that is currently initialized and stored
   in the "wins" object.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values 0-16, or the
			  constants in file _cursesWinConsts.hpp.  
  Output:
   NONE
*/
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins)
{
  char val = 'a';

  for(int i = 0; i < wins.size(); i++, val++)
    {
      if(wins.at(i)->getWindow() != nullptr)
	{
	  box(wins.at(i)->getWindow(), val, val);
	}
    }
} // end of "drawBoxes"
