/*
  File:
   cursesFunctions.cpp

  Description:
   Function implementations for the cursesFunctions.hpp header file.
*/
#include "cursesFunctions.hpp"
#include <algorithm>



/*
  Function:
  initializeCurses

  Description:
   Initializes the curses stdscr and curses datastructures.  This function
   should be called at the beginning of the Bottom program to set Bottom to
   its functional interface.

  Input:
   NONE

  Output:
   NONE
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
   initializeStartingWindows
   
  Description:
  
  Input:
   wins                 - A reference to an unordered map that will be used to store
                          each CursesWindow object defined in this function.  The
                          key is from _cursesWinConsts.hpp and will match the 
                          corresponding CursesWindow object as value.
  Output:
   NONE
*/
void initializeStartingWindows(std::unordered_map<int, CursesWindow*>& wins)
{
  for(int i = _MAINWIN; i <= _MEMGRAPHWIN; i++)
    {
      CursesWindow* newWindow = new CursesWindow();
      wins.insert(std::make_pair(i, newWindow));
    }  
} // end of "initializeStartingWindows"



/*
  Function:

  Description:

  Input:

  Output:
*/
void defineStartingWindows(std::unordered_map<int, CursesWindow*>& wins)
{
  int numLines;
  int numCols;
  int startY = 0;
  int startX = 0;
  
  getmaxyx(stdscr, numLines, numCols);

  wins.at(_MAINWIN)->defineWindow(stdscr,
				  "Main",
				  numLines,
				  numCols,
				  startY,
				  startX);
  numLines = 1;
  numCols = numCols - 100;
  startY = _YOFFSET - 6;
  startX = 0;

  wins.at(_TOPWIN)->defineWindow(newwin(numLines,
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
  wins.at(_TASKSWIN)->defineWindow(newwin(numLines,
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
  wins.at(_CPUWIN)->defineWindow(newwin(numLines,
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
  wins.at(_MEMWIN)->defineWindow(newwin(numLines,
					numCols,
					startY,
					startX),
				 "MEM",
				 numLines,
				 numCols,
				 startY,
				 startX);

  // define PID window
  numLines = wins.at(_MAINWIN)-> getNumLines() -
    wins.at(_MEMWIN)->getNumLines() -
    wins.at(_CPUWIN)->getNumLines() -
    wins.at(_TASKSWIN)->getNumLines() -
    wins.at(_TOPWIN)->getNumLines() - 1;
  numCols = 7;
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = 0;
  wins.at(_PIDWIN)->defineWindow(newwin(numLines,
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
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = wins.at(_PIDWIN)->getNumCols() + 1;
  wins.at(_USERWIN)->defineWindow(newwin(numLines,
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
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = wins.at(_PIDWIN)->getNumCols() +
    wins.at(_USERWIN)->getNumCols() + 2;
  wins.at(_PRWIN)->defineWindow(newwin(numLines,
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
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = wins.at(_PIDWIN)->getNumCols() +
    wins.at(_USERWIN)->getNumCols() +
    wins.at(_PRWIN)->getNumCols() + 3;
  wins.at(_NIWIN)->defineWindow(newwin(numLines,
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
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = wins.at(_PIDWIN)->getNumCols() +
    wins.at(_USERWIN)->getNumCols() +
    wins.at(_PRWIN)->getNumCols() +
    wins.at(_NIWIN)->getNumCols() + 4;
  wins.at(_VIRTWIN)->defineWindow(newwin(numLines,
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
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = wins.at(_PIDWIN)->getNumCols() +
    wins.at(_USERWIN)->getNumCols() +
    wins.at(_PRWIN)->getNumCols() +
    wins.at(_NIWIN)->getNumCols() + 
    wins.at(_VIRTWIN)->getNumCols() + 5;    
  wins.at(_RESWIN)->defineWindow(newwin(numLines,
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
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = wins.at(_PIDWIN)->getNumCols() +
    wins.at(_USERWIN)->getNumCols() +
    wins.at(_PRWIN)->getNumCols() +
    wins.at(_NIWIN)->getNumCols() + 
    wins.at(_VIRTWIN)->getNumCols() +
    wins.at(_RESWIN)->getNumCols() + 6;
  wins.at(_SHRWIN)->defineWindow(newwin(numLines,
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
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = wins.at(_PIDWIN)->getNumCols() +
    wins.at(_USERWIN)->getNumCols() +
    wins.at(_PRWIN)->getNumCols() +
    wins.at(_NIWIN)->getNumCols() + 
    wins.at(_VIRTWIN)->getNumCols() +
    wins.at(_RESWIN)->getNumCols() +
    wins.at(_SHRWIN)->getNumCols() + 7;
  wins.at(_SWIN)->defineWindow(newwin(numLines,
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
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = wins.at(_PIDWIN)->getNumCols() +
    wins.at(_USERWIN)->getNumCols() +
    wins.at(_PRWIN)->getNumCols() +
    wins.at(_NIWIN)->getNumCols() + 
    wins.at(_VIRTWIN)->getNumCols() +
    wins.at(_RESWIN)->getNumCols() +
    wins.at(_SHRWIN)->getNumCols() +
    wins.at(_SWIN)->getNumCols() + 8;
  wins.at(_PROCCPUWIN)->defineWindow(newwin(numLines,
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
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = wins.at(_PIDWIN)->getNumCols() +    
    wins.at(_USERWIN)->getNumCols() +
    wins.at(_PRWIN)->getNumCols() +
    wins.at(_NIWIN)->getNumCols() + 
    wins.at(_VIRTWIN)->getNumCols() +
    wins.at(_RESWIN)->getNumCols() +
    wins.at(_SHRWIN)->getNumCols() +
    wins.at(_SWIN)->getNumCols() +     
    wins.at(_PROCCPUWIN)->getNumCols() + 9;
  wins.at(_PROCMEMWIN)->defineWindow(newwin(numLines,
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
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = wins.at(_PIDWIN)->getNumCols() +
    wins.at(_USERWIN)->getNumCols() +
    wins.at(_PRWIN)->getNumCols() +
    wins.at(_NIWIN)->getNumCols() + 
    wins.at(_VIRTWIN)->getNumCols() +
    wins.at(_RESWIN)->getNumCols() +
    wins.at(_SHRWIN)->getNumCols() +
    wins.at(_SWIN)->getNumCols() +     
    wins.at(_PROCCPUWIN)->getNumCols() +    
    wins.at(_PROCMEMWIN)->getNumCols() + 10;  
  wins.at(_PROCTIMEWIN)->defineWindow(newwin(numLines,
					     numCols,
					     startY,
					     startX),
				      "    TIME+",
				      numLines,
				      numCols,
				      startY,
				      startX);
  // define COMMAND window
  std::string commandLine = "COMMAND";
  numCols = 48;
  startY = wins.at(_MEMWIN)->getStartY() + _YOFFSET - 3;
  startX = wins.at(_PIDWIN)->getNumCols() +    
    wins.at(_USERWIN)->getNumCols() +
    wins.at(_PRWIN)->getNumCols() +
    wins.at(_NIWIN)->getNumCols() + 
    wins.at(_VIRTWIN)->getNumCols() +
    wins.at(_RESWIN)->getNumCols() +
    wins.at(_SHRWIN)->getNumCols() +
    wins.at(_SWIN)->getNumCols() +     
    wins.at(_PROCCPUWIN)->getNumCols() +    
    wins.at(_PROCMEMWIN)->getNumCols() +
    wins.at(_PROCTIMEWIN)->getNumCols() + 11;
  for(int i = commandLine.length(); i < numCols; i++)
    {
      commandLine.push_back(' ');
    }
  wins.at(_COMMANDWIN)->defineWindow(newwin(numLines,
					    numCols,
					    startY,
					    startX), 
				     commandLine,
				     numLines,
				     numCols,
				     startY,
				     startX);
  // define TasksTotalWindow
  numCols = 4;
  numLines = 1;
  startY = 1;
  startX = 6;
  wins.at(_TASKSTOTAL)->defineWindow(newwin(numLines,
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
  wins.at(_TASKSRUNNING)->defineWindow(newwin(numLines,
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
  wins.at(_TASKSSLEEPING)->defineWindow(newwin(numLines,
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
  wins.at(_TASKSSTOPPED)->defineWindow(newwin(numLines,
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
  wins.at(_TASKSZOMBIE)->defineWindow(newwin(numLines,
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
  wins.at(_CPUUSWIN)->defineWindow(newwin(numLines,
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
  wins.at(_CPUSYWIN)->defineWindow(newwin(numLines,
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
  wins.at(_CPUNIWIN)->defineWindow(newwin(numLines,
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
  wins.at(_CPUIDWIN)->defineWindow(newwin(numLines,
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
  wins.at(_CPUWAWIN)->defineWindow(newwin(numLines,
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
  wins.at(_CPUHIWIN)->defineWindow(newwin(numLines,
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
  wins.at(_CPUSIWIN)->defineWindow(newwin(numLines,
					  numCols,
					  startY,
					  startX),  
				   "si",
				   numLines,
				   numCols,
				   startY,
				   startX);
  // define cpu steal time window
  numCols = 5;
  numLines = 1;
  startY = 2;
  startX = 71;
  wins.at(_CPUSTWIN)->defineWindow(newwin(numLines,
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
  wins.at(_MIBTOTALWIN)->defineWindow(newwin(numLines,
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
  wins.at(_MIBFREEWIN)->defineWindow(newwin(numLines,
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
  wins.at(_MIBUSEDWIN)->defineWindow(newwin(numLines,
					    numCols,
					    startY,
					    startX),  
				     "used",
				     numLines,
				     numCols,
				     startY,
				     startX);
  // define buff cache window
  numCols = 9;
  numLines = 1;
  startY = 3;
  startX = 55;
  wins.at(_MIBBUFFCACHEWIN)->defineWindow(newwin(numLines,
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
  wins.at(_MIBSWAPTOTALWIN)->defineWindow(newwin(numLines,
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
  wins.at(_MIBSWAPFREEWIN)->defineWindow(newwin(numLines,
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
  wins.at(_MIBSWAPUSEDWIN)->defineWindow(newwin(numLines,
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
  wins.at(_MIBMEMAVAILWIN)->defineWindow(newwin(numLines,
						numCols,
						startY,
						startX),  
					 "avil Mem",
					 numLines,
					 numCols,
					 startY,
					 startX);
  // define cpu graph
  numLines = 14;
  numCols = (((wins.at(_MAINWIN)->getNumCols() -
	       wins.at(_COMMANDWIN)->getNumCols() -
	       wins.at(_COMMANDWIN)->getStartX())/2) - 2);
  if(numCols %2 != 0)
    {
      numCols++;
    }
  startY = _YOFFSET + 1;
  startX = wins.at(_MAINWIN)->getNumCols() - numCols;
  wins.at(_CPUGRAPHWIN)->defineWindow(newwin(numLines,
					     numCols,
					     startY,
					     startX),  
				      "cpuGraph",
				      numLines,
				      numCols,
				      startY,
				      startX);
  // define mem graph
  startY = startY + numLines;
  wins.at(_MEMGRAPHWIN)->defineWindow(newwin(numLines,
					     numCols,
					     startY,
					     startX),  
				      "memGraph",
				      numLines,
				      numCols,
				      startY,
				      startX);
} // end of "defineStartingWindows"



/*
  Function:
   updateWindowDimensions

  Description:
   Updates the currently allocated process window sizes in the case of
   a terminal resize that would impact their output or functionality.

  Input:
   wins                 - A reference to an unordered map that will be used to store
                          each CursesWindow object defined in this function.  The
                          key is from _cursesWinConsts.hpp and will match the 
                          corresponding CursesWindow object as value.
  Output:
   NONE
*/
void updateWindowDimensions(std::unordered_map<int, CursesWindow*>& wins,
			    const int& shiftX,
			    const int& shiftY)
{
  int numLines;
  int numCols;
  
  getmaxyx(stdscr, numLines, numCols);
  wins.at(_MAINWIN)->setNumLines(numLines);
  wins.at(_MAINWIN)->setNumCols(numCols);
  bool deleted = false;

  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      // if window resize is too few columns or lines for the current windows
      if( (wins.at(i)->getNumCols() + wins.at(i)->getStartX() > numCols) ||
	  (numLines != wins.at(_COMMANDWIN)->getNumLines() + _YOFFSET) )
	{
	  // delete them
	  wins.at(i)->deleteWindow();
	  wins.at(i)->setWindow(nullptr);
	  deleted = true;
	}
    }

  // sanity check
  if(deleted == true)
    {
      for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
	{
	  // check if a window should be allocated
	  if( (wins.at(i)->getWindow() == nullptr) && (shiftX <= i) &&
	      (numLines > _YOFFSET) )
	    {
	      int len = wins.at(i)->getNumCols() + wins.at(i)->getStartX();
	      if(len <= numCols)
		{
		  wins.at(i)->defineWindow(newwin(numLines - _YOFFSET,
						  wins.at(i)->getNumCols(),
						  wins.at(i)->getStartY(),
						  wins.at(i)->getStartX()),
					   wins.at(i)->getWindowName(),
					   numLines - _YOFFSET,
					   wins.at(i)->getNumCols(),
					   wins.at(i)->getStartY(),
					   wins.at(i)->getStartX());
		}
	    }
	}
    }
} // end of "updateWindowDimensions"



/*
  Function:
   refreshAllWins

  Description:
   Refreshes all currently active and defined CursesWindow objects.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by values in the file
                          _cursesWinConsts.hpp.                
  Output:
   NONE
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
   Clears all currently active and defined CursesWindow object screens. All
   "erased" data is stored in the screen buffer waiting for a call to refresh()
   to erase it.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by values in the file
                          _cursesWinConsts.hpp.              
  Output:
   NONE
*/
void clearAllWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  std::unordered_map<int, CursesWindow*>::const_iterator it;
  for(it = wins.begin(); it != wins.end(); it++)
    {
      werase(it->second->getWindow());
    }
} // end of "clearAllWins"



/*
  Function:
   clearTopWins

  Description:
   Clears currently active and defined CursesWindow object screens for the top
   five "windows". All "erased" data is  stored in the screen buffer waiting for a 
   call to refresh() to erase it.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by values in the file
                          _cursesWinConsts.hpp.            
  Output:
   NONE
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
   Clears currently active and defined CursesWindow object screens for the bottom
   windows "PID, USER, PR, NI.."  All "erased" data is  stored in the screen buffer 
   waiting for a call to refresh() to erase it.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by values in the file
                          _cursesWinConsts.hpp.          
  Output:
   NONE
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
   Sets the bold attribute ON for currently active and defined CursesWindow object screens 
   for the top five "windows" values only.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by values in the file
                          _cursesWinConsts.hpp.        
  Output:
   NONE
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
   Sets the bold attribute OFF for currently active and defined CursesWindow object screens 
   for the top five "windows" values only.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by values in the file
                          _cursesWinConsts.hpp.      
  Output:
   NONE
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
   Sets the bold attribute ON for the "Tasks window" values.

  Input:
   wins                 - A reference to a const unordered map
                         <int, CursesWindow*> type. wins contains pointers
                         to all currently allocated CursesWindow objects
                         that can be indexed by values in the file
                         _cursesWinConsts.hpp.    
  Output:
   NONE
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
   Sets the bold attribute OFF for the "Tasks window" values.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.  
  Output:
   NONE
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
   Sets the bold attribute ON for the "CPU window" values.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.

  Output:
   NONE
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
   Sets the bold attribute OFF for the "CPU window" values.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.                        
  Output:
   NONE
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
   Sets the bold attribute ON for the "MEM window" values.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.                      
  Output:
   NONE
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
   Sets the bold attribute OFF for the "MEM window" values.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.                    
  Output:
   NONE
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
   colorOnBottomWins

  Description:
   Sets the a color pair attribute ON for the bottom windows.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.                  

  colorPair             - An integer that represents a color pair initialized in
                          the initializeCurses() function in this file.  The
			  pre-defined parameter value is defined in
			  _cursesWinConsts.hpp.
  Output:
   NONE
*/
void colorOnBottomWins(const std::unordered_map<int, CursesWindow*>& wins,
		       int colorPair)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), COLOR_PAIR(colorPair));
    }
} // end of "colorOnBottomWins"



/*
  Function:
   colorOffBottomWins

  Description:
   Sets the a color pair attribute OFF for the bottom windows.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.                

  colorPair             - An integer that represents a color pair initialized in
                          the initializeCurses() function in this file.  The
			  pre-defined parameter value is defined in
			  _cursesWinConsts.hpp.
  Output:
   NONE
*/
void colorOffBottomWins(const std::unordered_map<int, CursesWindow*>& wins,
			int colorPair)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      wattroff(wins.at(i)->getWindow(), COLOR_PAIR(colorPair));
    }  
} // end of "colorOffBottomWins"



void attrOnBottomWins(const std::unordered_map<int, CursesWindow*>& wins,
		      int attr)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), attr);
    }  
} // end of "colorOffBottomWins"




void attrOffBottomWins(const std::unordered_map<int, CursesWindow*>& wins,
		       int attr)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      wattroff(wins.at(i)->getWindow(), attr);
    }  
} // end of "colorOffBottomWins"


  
/*
  Function:
   printTasksData

  Description:
   Prints the data values stored in the taskInfo parameter to the corresponding
   tasks data windows (_TASKSTOTAL/RUNNING/SLEEPING/STOPPED) from the
   _cursesWinConsts.hpp header file. All "printed" data is stored in the screen 
   buffer waiting for a call to refresh() to print it.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.              
			  
  taskInfo              - A constant reference to a TaskInfo object that contains
                          data to be printed to the tasks windows.
  Output:
   NONE
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
   Prints the data values stored in the cpuInfo parameter to the corresponding
   cpu data windows (_CPUUSWIN,SYWIN,NIWIN...) from the _cursesWinConsts.hpp header 
   file. All "printed" data is stored in the screen buffer waiting for a call
   to refresh() to print it.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.            
			  
  cpuInfo               - A constant reference to a CPUInfo object that contains
                          data to be printed to the cpu windows.
  Output:
   NONE
*/
void printCpusData(const std::unordered_map<int, CursesWindow*>& wins,
		   const CPUUsage& cpuUsage)
{
  std::string outString;

  
  outString = doubleToStr(cpuUsage.us, 1);
  mvwaddstr(wins.at(_CPUUSWIN)->getWindow(),
	    0,
	    wins.at(_CPUUSWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  
  outString = doubleToStr(cpuUsage.sy, 1);  
  mvwaddstr(wins.at(_CPUSYWIN)->getWindow(),
	    0,
	    wins.at(_CPUSYWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(cpuUsage.ni, 1);
  mvwaddstr(wins.at(_CPUNIWIN)->getWindow(),
	    0,
	    wins.at(_CPUNIWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(cpuUsage.id, 1);
  mvwaddstr(wins.at(_CPUIDWIN)->getWindow(),
	    0,
	    wins.at(_CPUIDWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(cpuUsage.wa, 1);
  mvwaddstr(wins.at(_CPUWAWIN)->getWindow(),
	    0,
	    wins.at(_CPUWAWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(cpuUsage.irq, 1);
  mvwaddstr(wins.at(_CPUHIWIN)->getWindow(),
	    0,
	    wins.at(_CPUHIWIN)->getNumCols() - outString.length(),
	    outString.c_str());


  outString = doubleToStr(cpuUsage.sirq, 1);
  mvwaddstr(wins.at(_CPUSIWIN)->getWindow(),
	    0,
	    wins.at(_CPUSIWIN)->getNumCols() - outString.length(),
	    outString.c_str());

  outString = doubleToStr(cpuUsage.st, 1);
  mvwaddstr(wins.at(_CPUSTWIN)->getWindow(),
	    0,
	    wins.at(_CPUSTWIN)->getNumCols() - outString.length(),
	    outString.c_str());
} // end of "printCpusData"



/*
  Function:
   printMemMiBData

  Description:
   Prints the data values stored in the memInfo parameter to the corresponding
   memMiB data windows (_MIBTOTALWIN,FREEWIN,USEDWIN...) from the _cursesWinConsts.hpp 
   header file.  All "printed" data is stored in the screen buffer waiting for a call
   to refresh() to print it.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.          
			  
  memInfo               - A constant reference to a MemInfo object that contains
                          data to be printed to the MiB Mem/Swap windows.
  Output:
   NONE
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
   Prints the five defined top lines. All "printed" data is stored in the screen 
   buffer waiting for a call to refresh() to print it. All "printed" data is stored 
   in the screen buffer waiting for a call to refresh() to print it.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.        

   allTopLines          - A constant refrence to a vector<string> object type that 
                          should contain lines to be printed to the corresponding
                          CursesWindow object. In use, these lines are...
                          "Top, Tasks, %CPU(s), MiB Mem, MiB Swap"
  Output:
   NONE
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
   Prints the window names for the columns "PID, USER, PR, NI...". All "printed" data 
   is stored in the screen buffer waiting for a call to refresh() to print it.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.      

  Output:
   NONE
*/
void printWindowNames(const std::unordered_map<int, CursesWindow*>& wins,
		      const int& shiftY,
		      const int& shiftX)
{
  std::string outString;
  if(shiftX <= _PIDWIN && wins.at(_PIDWIN)->getWindow() != nullptr)
    {
      // PID
      outString = wins.at(_PIDWIN)->getWindowName();
      mvwaddstr(wins.at(_PIDWIN)->getWindow(),
		0,
		wins.at(_PIDWIN)->getNumCols() - outString.length(),
		outString.c_str());
    }
  // USER
  if(shiftX <= _USERWIN && wins.at(_USERWIN)->getWindow() != nullptr)
    {
      outString = wins.at(_USERWIN)->getWindowName();
      mvwaddstr(wins.at(_USERWIN)->getWindow(),
		0,
		0,
		outString.c_str());
    }
  // PR
  if(shiftX <= _PRWIN && wins.at(_PRWIN)->getWindow() != nullptr)
    {
      outString = wins.at(_PRWIN)->getWindowName();
      mvwaddstr(wins.at(_PRWIN)->getWindow(),
		0,
		wins.at(_PRWIN)->getNumCols() - outString.length(),
		outString.c_str());
    }
  // NI
  if(shiftX <= _NIWIN && wins.at(_NIWIN)->getWindow() != nullptr)
    {
      outString = wins.at(_NIWIN)->getWindowName();
      mvwaddstr(wins.at(_NIWIN)->getWindow(),
		0,
		wins.at(_NIWIN)->getNumCols() - outString.length(),
		outString.c_str());
    }
  // VIRT
  if(shiftX <= _VIRTWIN && wins.at(_VIRTWIN)->getWindow() != nullptr)
    {
      outString = wins.at(_VIRTWIN)->getWindowName();
      mvwaddstr(wins.at(_VIRTWIN)->getWindow(),
		0,
		wins.at(_VIRTWIN)->getNumCols() - outString.length(),
		outString.c_str());
    }
  // RES
  if(shiftX <= _RESWIN && wins.at(_RESWIN)->getWindow() != nullptr)
    {
      outString = wins.at(_RESWIN)->getWindowName();
      mvwaddstr(wins.at(_RESWIN)->getWindow(),
		0,
		wins.at(_RESWIN)->getNumCols() - outString.length(),
		outString.c_str());
    } 
  // SHR
  if(shiftX <= _SHRWIN && wins.at(_SHRWIN)->getWindow() != nullptr)
     {
      outString = wins.at(_SHRWIN)->getWindowName();
      mvwaddstr(wins.at(_SHRWIN)->getWindow(),
		0,
		wins.at(_SHRWIN)->getNumCols() - outString.length(),
		outString.c_str());
    } 
  // S
  if(shiftX <= _SWIN && wins.at(_SWIN)->getWindow() != nullptr)
    {
      outString = wins.at(_SWIN)->getWindowName();
      mvwaddstr(wins.at(_SWIN)->getWindow(),
		0,
		wins.at(_SWIN)->getNumCols() - outString.length(),
		outString.c_str());
    }
  // %CPU
  if(shiftX <= _PROCCPUWIN && wins.at(_PROCCPUWIN)->getWindow() != nullptr)
    {
      outString = wins.at(_PROCCPUWIN)->getWindowName();
      mvwaddstr(wins.at(_PROCCPUWIN)->getWindow(),
		0,
		wins.at(_PROCCPUWIN)->getNumCols() - outString.length(),
		outString.c_str());
    } 
  // %MEM
  if(shiftX <= _PROCMEMWIN && wins.at(_PROCMEMWIN)->getWindow() != nullptr)
    {
      outString = wins.at(_PROCMEMWIN)->getWindowName();
      mvwaddstr(wins.at(_PROCMEMWIN)->getWindow(),
		0,
		wins.at(_PROCMEMWIN)->getNumCols() - outString.length(),
		outString.c_str());
    } 
  // TIME+
  if(shiftX <= _PROCTIMEWIN && wins.at(_PROCTIMEWIN)->getWindow() != nullptr)
    {
      outString = wins.at(_PROCTIMEWIN)->getWindowName();
      mvwaddstr(wins.at(_PROCTIMEWIN)->getWindow(),
		0,
		wins.at(_PROCTIMEWIN)->getNumCols() - outString.length(),
		outString.c_str());
    } 
  // COMMAND
  if(shiftX <= _COMMANDWIN && wins.at(_COMMANDWIN)->getWindow() != nullptr)
    {

      outString = wins.at(_COMMANDWIN)->getWindowName();
      mvwaddstr(wins.at(_COMMANDWIN)->getWindow(),
		0,
		0,
		outString.c_str());
    }
} // end of "printWindowNames"



/*
  Function:
   printProcs

  Description:
   Prints the bottom windows that contain process related data to the screen
   (PID, USER, PR, NI...). The control structures ensure that all printing is
   done in allocated screen space for the CursesWindow objects, both in
   "row/column" screen position as well as memory.  The if statements not only
   test that the window exists before attempting to print, but they also
   test the dynamic dimensions of the screen before printing in case there
   is any window resizing done with the program is active.

   A simple loop is used to iterate over all the CursesWindow objects to
   print their data.
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.    

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
		const int shiftX,
		const int& sortState,
		const bool& highlight)
{
  std::string outString;
  
  for(int i = 0; i < pidList.size(); i++)
    {
      int posY = i + shiftY;
      // ensure nothing is printed over the column titles
      if(posY != 0)
	{
	  if(procData.at(pidList.at(i))->getS() == 'R'||
	     procData.at(pidList.at(i))->getS() == 'Z')
	    {
	      attrOnBottomWins(wins, A_BOLD);
	    }
	  
	  // PID
	  if(highlight == true && sortState == _PIDWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	      
	  outString = std::to_string(procData.at(pidList.at(i))->getPID());
	  mvwaddstr(wins.at(_PIDWIN)->getWindow(),
		    posY,
		    wins.at(_PIDWIN)->getNumCols() - outString.length(),
		    outString.c_str());
	  // USER
	  if(highlight == true && sortState == _USERWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	      
	  outString = procData.at(pidList.at(i))->getUSER();
	  mvwaddstr(wins.at(_USERWIN)->getWindow(),
		    posY,
		    0,
		    outString.c_str());
	  // PR
	  if(highlight == true && sortState == _PRWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	      
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
	  // NI
	  if(shiftX <= _NIWIN && wins.at(_NIWIN)->getWindow() != nullptr)
	    if(highlight == true && sortState == _NIWIN)
	      {
		wattron(wins.at(sortState)->getWindow(),
			A_BOLD); 
	      }
	      
	  outString = std::to_string(procData.at(pidList.at(i))->getNI());
	  mvwaddstr(wins.at(_NIWIN)->getWindow(),
		    posY,
		    wins.at(_NIWIN)->getNumCols() - outString.length(),
		    outString.c_str());
	  // VIRT
	  if(highlight == true && sortState == _VIRTWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	      
	  outString = std::to_string(procData.at(pidList.at(i))->getVIRT());
	  mvwaddstr(wins.at(_VIRTWIN)->getWindow(),
		    posY,
		    wins.at(_VIRTWIN)->getNumCols() - outString.length(),
		    outString.c_str());
	  // RES
	  if(highlight == true && sortState == _RESWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	  outString = std::to_string(procData.at(pidList.at(i))->getRES());
	  mvwaddstr(wins.at(_RESWIN)->getWindow(),
		    posY,
		    wins.at(_RESWIN)->getNumCols() - outString.length(),
		    outString.c_str());
	  // SHR
	  if(highlight == true && sortState == _SHRWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	      
	  outString = std::to_string(procData.at(pidList.at(i))->getSHR());
	  mvwaddstr(wins.at(_SHRWIN)->getWindow(),
		    posY,
		    wins.at(_SHRWIN)->getNumCols() - outString.length(),
		    outString.c_str());
	  // S
	  if(highlight == true && sortState == _SWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	      
	  mvwaddch(wins.at(_SWIN)->getWindow(),
		   posY,
		   0,
		   procData.at(pidList.at(i))->getS());
	  // %CPU
	  if(highlight == true && sortState == _PROCCPUWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	      
	  outString = doubleToStr(procData.at(pidList.at(i))->getCPUUsage(), 1);
	  mvwaddstr(wins.at(_PROCCPUWIN)->getWindow(),
		    posY,
		    wins.at(_PROCCPUWIN)->getNumCols() - outString.length(),
		    outString.c_str());
	  // %MEM
	  if(highlight == true && sortState == _PROCMEMWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	      
	  outString = doubleToStr(procData.at(pidList.at(i))->getMEMUsage(), 1);
	  mvwaddstr(wins.at(_PROCMEMWIN)->getWindow(),
		    posY,
		    wins.at(_PROCMEMWIN)->getNumCols() - outString.length(),
		    outString.c_str());

	  // TIME+

	  if(highlight == true && sortState == _PROCTIMEWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	      
	  outString = procData.at(pidList.at(i))->getProcessCPUTime();
	  mvwaddstr(wins.at(_PROCTIMEWIN)->getWindow(),
		    posY,
		    wins.at(_PROCTIMEWIN)->getNumCols() - outString.length(),
		    outString.c_str());

	  // COMMAND
	  if(highlight == true && sortState == _COMMANDWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	      
	  outString = procData.at(pidList.at(i))->getCOMMAND();

	  size_t maxLen = wins.at(_COMMANDWIN)->getNumCols();
	  if(maxLen > outString.length())
	    {
	      outString = outString.substr(0, maxLen);
	    }
	  
	  mvwaddstr(wins.at(_COMMANDWIN)->getWindow(),
		    posY,
		    0,
		    outString.c_str());

	  attrOffBottomWins(wins, A_BOLD);
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
			  define in the string.

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
   printLine

  Description:
   Prints an incoming string to
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.  

   row                  - A reference to a constant integer that holds
                          the Y-Position to print the string to.

   attr                 - A reference to a constant integer that holds the
                          color combination that will be applied to the
			  output string.

   window               - A reference to a constant integer that holds the
                          index value of the CursesWindow object that will
			  be printed to.
			  

   outString            - A reference to a constant string object that holds
                          the string to print to on the given window.
			  
  Output:
   NONE
*/
void printLine(const std::unordered_map<int, CursesWindow*>& wins,
	       const int& row,
	       const int& col,
	       const int& attrs,
	       const int& window,
	       const std::string& outString)
{
  wattron(wins.at(window)->getWindow(), COLOR_PAIR(attrs));
  mvwaddstr(wins.at(window)->getWindow(),
	    row,
	    col,
	    outString.c_str());
  wattroff(wins.at(window)->getWindow(), COLOR_PAIR(attrs));
} // end of "printLine"



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
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.
			  
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

      // update the numlines of the window
      wins.at(currWin)->setNumLines(wins.at(_MAINWIN)->getNumLines() - _YOFFSET);
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
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.
			  
   shiftX               - The current shift state of the bottom windows.
			  
  Output:
   NONE
*/
void shiftBottomWinsRight(std::unordered_map<int, CursesWindow*>& wins,
			  const int& shiftX)
{
  int currWin = shiftX;
  int totalShifts = 0;

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

  // create the starting window now that the windows have been shifted and
  // update the numlines of the window
  wins.at(shiftX - 1)->createWindow(wins.at(_MAINWIN)->getNumLines() - _YOFFSET,
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
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.       
  Output:
   NONE
*/
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins)
{
  char val = 'a';

  std::unordered_map<int, CursesWindow*>::const_iterator it;
  for(it = wins.begin(); it != wins.end(); it++)
    {
      val++;
      if(it->second->getWindow() != nullptr)
	{
	  box(it->second->getWindow(), val, val);
	}
    }
} // end of "drawBoxes"



/*
  Function:
   printUserInput

  Description
   Prints user input to the incomining window.  Printing is restricted
   by conditional statements that ensure no printing can happen outside
   the bounds of the current window, as well as stdscr(main window).
   Based on those conditions, input is stored in the std::string object
   type reference parameter.
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.
			  
   winIndex             - A const int type containing the key for the window
                          we wish to print user input to.

   input                - A reference to a constant integer that contains
                          the last value extracted by getch().  If it meets
			  necessary conditions, it will be printed to the
			  screen and appended to the inputString.
			  
   inputString          - A refrence to a string object type that contains
                          input getch() has extracted based upon necessary
			  conditions.
			  
   yOffset              - A reference to an integer that contains the current
                          Y position in the window to print to.

			  
   xOffset              - A reference to an integer that contains the current
                          X position in the window to print to.  It is also
			  used as a controlling expression in the if else
			  structures.
  Output:
   NONE
*/
void printUserInput(const std::unordered_map<int, CursesWindow*>& wins,
		    const int winIndex,
		    const int& input,
		    std::string& inputString,		    
		    int& yOffset,
		    int& xOffset)
{
  if((input >= 32) &&
     (input <= 126) &&
     (input != KEY_ENTER) &&
     (xOffset < wins.at(winIndex)->getNumCols() - 2))
    {
      inputString.push_back(input);
      mvwaddch(wins.at(winIndex)->getWindow(),
	       yOffset,
	       xOffset,
	       input);
      xOffset++;
    }
  else if(input == KEY_BACKSPACE && xOffset > 0)
    {
      inputString.pop_back();      
      xOffset--;
      mvwaddch(wins.at(winIndex)->getWindow(),
	       yOffset,
	       xOffset,
	       ' ');
      wmove(wins.at(winIndex)->getWindow(),
	    yOffset,
	    xOffset);
    }
  else if(input == 10 || input == KEY_ENTER)
    {
      inputString.push_back(10);
    }
} // end of "printUserInput"



/*
  Function:
   printBadInputString
 
  Description:
   Prints the incoming string as black text on a white background
   to the incoming window.  The window is first cleared completely
   of the any preivous outputby printing a color line at the location
   first before printing the bad input string.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type. wins contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.

   window               - A reference to a constant integer that holds the
                          index value of the CursesWindow object that will
			  be printed to.			  


   yOffset              - A reference to an integer that contains the current
                          Y position in the window to print to.

			  
   xOffset              - A reference to an integer that contains the current
                          X position in the window to print to.

   outString            - A reference to a constant string object that holds
                          the string to print to on the given window.

  Output:
   NONE
*/
void printBadInputString(const std::unordered_map<int, CursesWindow*>& wins,
			 const int& window,
			 const int& yOffset,
			 const int& xOffset,
			 const std::string& outString)
{
  std::string colorLine;
  curs_set(0);
  wattroff(wins.at(window)->getWindow(),
	   A_BOLD);
		      
  // clear the line where the prompt will be printed
  colorLine = createColorLine(wins.at(window)->getNumCols());
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    window,
	    colorLine);
				     
  // define and print the prompt
  printLine(wins,
	    yOffset,
	    xOffset,
	    _BLACK_TEXT,
	    window,
	    outString);
  
  wrefresh(wins.at(window)->getWindow());
  doupdate();  
} // end of "printBadInputString"



/*
  Function:
  
  Description:

  Input:

  Output:
  
*/
void drawGraph(const std::unordered_map<int, CursesWindow*>& wins,
		  const int& winName,
		  std::queue<double> vals,
		  std::string graphName)
{
  std::vector<double> valsCopy;  
  int numLines = wins.at(winName)->getNumLines();
  int numCols = wins.at(winName)->getNumCols();
  std::string outString = graphName;

  while(!vals.empty())
    {
      valsCopy.push_back(vals.front());
      vals.pop();
    }

  // print window border
  for(int i = 0, j = 0; i < numLines, j < numCols; i++, j++)
    {
      mvwaddch(wins.at(winName)->getWindow(),
	       i,
	       0,
	       '*');
      mvwaddch(wins.at(winName)->getWindow(),
	       i,
	       numCols - 1,
	       '*');
      mvwaddch(wins.at(winName)->getWindow(),
	       0,
	       i,
	       '*');
      mvwaddch(wins.at(winName)->getWindow(),
	       2,
	       i,
	       '*');            
      mvwaddch(wins.at(winName)->getWindow(),
	       numLines - 1,
	       j,
	       '*');
    }

  wattron(wins.at(winName)->getWindow(), A_BOLD);
  for(int i = outString.size(); i < numCols - 2; i++)
    {
      outString.append(" ");
    }

  mvwaddstr(wins.at(winName)->getWindow(),
	    1,
	    1,
	    outString.c_str());
  

  wattron(wins.at(winName)->getWindow(), COLOR_PAIR(_BLACK_TEXT));

  // print graph
  if(valsCopy.size() > 0)
    {
      for(int i = valsCopy.size() - 1, j = numCols + 1; i >= 0 && j > 3; i--)
	{
	  // calc bar height
	  double val = std::floor(valsCopy.at(i) / 10);
	  val = val/10;
	  int y = val * (numLines - 4);

	  // get current utilization
	  int currVal = valsCopy.back();
	  outString = std::to_string(currVal);

	  wattron(wins.at(winName)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
	  
	  // print current value
	  if(currVal < 10)
	    {
	      int outX = numCols - 2;
	      mvwaddstr(wins.at(winName)->getWindow(),
			1,
			outX,
			outString.c_str());
	    }
	  else if(currVal > 9 && currVal < 100)
	    {
	      int outX = numCols - 3;

	      mvwaddstr(wins.at(winName)->getWindow(),
			1,
			outX,
			outString.c_str());
	    }
	  else
	    {
	      int outX = numCols - 4;
	      mvwaddstr(wins.at(winName)->getWindow(),
			1,
			outX,
			outString.c_str());
	    }
	  
	  wattron(wins.at(winName)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
	  
	  // draw graph bars
	  for(int k = 1; k <= y; k++)
	    {
	      mvwaddch(wins.at(winName)->getWindow(),
		       numLines - k - 1,
		       j - 3,
		       ' ');
	      mvwaddch(wins.at(winName)->getWindow(),
		       numLines - k - 1,
		       j - 4,
		       ' ');
	    }
	  j -= 2;
	}
    }

  // reset ncurses attributes
  wattroff(wins.at(winName)->getWindow(), A_BOLD);  
  wattron(wins.at(winName)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
} // end of "drawGraph"
