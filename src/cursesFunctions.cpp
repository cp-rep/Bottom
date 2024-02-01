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

  Input/Output:
   NONE
   
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
   This function creates and initializes all the necessary startup windows
   for the Bottom program that are written to the screen on startup.  They
   are stored in an unordered map for later use.
   
  Input/Output:
   NONE

  Input:
   NONE
   
  Output:
   wins                 - A reference to an unordered map <int, CursesWindow*>
                          object type that will be used to store each
			  CursesWindow object initialized in this function.  The
                          keys are from _cursesWinConsts.hpp and match the 
                          corresponding CursesWindow objects they are pointing
			  to.
  Returns:
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
   refreshAllWins

  Description:
   Refreshes all CursesWindow objects member variables that point to a
   currently allocated WINDOW type (values that are not nullptr). They are
   sorted before refreshing to ensure the proper write order.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   NONE
   
  Output:
   NONE

  Returns:
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
   clearTopWins

  Description:
   Clears currently active and defined CursesWindow object windows for the top
   five lines of Bottom.  This is approximately 55 windows. All "erased" windows
   are stored in the screen buffers waiting for a call to refresh() to write the
   changes.

  Input/Output:
   NONE
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by values in the file
                          _cursesWinConsts.hpp.
  Output:
   NONE
   
  Returns:
   NONE
*/
void clearTopWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  for(int i = _TOPWIN; i <= _MEMAVAILDATAWIN; i++)
    {
      werase(wins.at(i)->getWindow());

    }
} // end of "clearTopWins"



/*
  Function:
   clearProcWins

  Description:
   Clears currently active and defined CursesWindow object windows for the bottom
   windows that containt process data "PID, USER, PR, NI.."  All "erased" windows
   are stored in the screen buffer waiting for a call to refresh() to write the
   change.

  Input/Output:
   NONE
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Output:
   NONE

  Returns:
   NONE
*/
void clearProcWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      werase(wins.at(i)->getWindow());
    }
} // end of "clearProcWins"



/*
  Function:
   clearAllWins

  Description:
   Clears all currently active and defined CursesWindow object screens. All
   "erased" screens are stored in the screen buffer waiting for a call to
   refresh() to write the changes.

  Input/Output:
   NONE
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Output:
   NONE

  Returns:
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
   defineProcWinsStartVals
   
  Description:
   Defines the allocated CursesWindows objects accessible with key/value pairs that
   contain WINDOW related variables for outputing read process data.
  
  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.  
  Input:
   NONE

  Output:
   NONE

  Returns:
   NONE
*/
void defineProcWinsStartVals(const std::unordered_map<int, CursesWindow*>& wins)
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
  // define PID window
  numCols = _PIDWINCOLS;
  numLines = numLines - _YOFFSET;
  startY = _YOFFSET;
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
  numCols = _USERWINCOLS;
  startY = _YOFFSET;
  startX += _PIDWINCOLS + 1;
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
  numCols = _PRWINCOLS;
  startY = _YOFFSET;
  startX += _USERWINCOLS + 1;
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
  numCols = _NIWINCOLS;
  startY = _YOFFSET;
  startX =_PIDWINCOLS + _USERWINCOLS + _PRWINCOLS + 3;
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
  numCols = _VIRTWINCOLS;
  startY = _YOFFSET;
  startX += _NIWINCOLS + 1;  
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
  numCols = _RESWINCOLS;
  startY = _YOFFSET;
  startX += _VIRTWINCOLS + 1;
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
  numCols = _SHRWINCOLS;
  startY = _YOFFSET;
  startX += _RESWINCOLS + 1;
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
  numCols = _SWINCOLS;
  startY = _YOFFSET;
  startX += _SHRWINCOLS + 1;
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
  numCols = _PROCCPUWINCOLS;
  startY = _YOFFSET;
  startX += _SWINCOLS + 1;
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
  numCols = _PROCMEMWINCOLS;
  startY = _YOFFSET;
  startX += _PROCCPUWINCOLS  + 1;
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
  numCols = _PROCTIMEWINCOLS;
  startY = _YOFFSET;
  startX += _PROCMEMWINCOLS  + 1;
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
  numCols = _COMMANDWINCOLS;
  startY = _YOFFSET;
  startX += _PROCTIMEWINCOLS  + 1;
  std::string commandLine = "COMMAND";
  
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
} // end of "defineProcWinsStartVals"



/*
  Function:
   defineTopWinsDataStartVals

  Description:
   Defines the allocated CursesWindows objects accessible with key/value pairs that
   contain WINDOW related variables for outputing dynamically read OS data.

  Input:
   NONE

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Output:
   NONE

  Returns:
   NONE
*/
void defineTopWinsDataStartVals(const std::unordered_map<int, CursesWindow*>& wins)
{
  wins.at(_TASKSTOTALDATAWIN)->defineWindow(newwin(1,
						   _TASKSDATAWINCOLS,
						   _TASKSDATAWINSTARTY,
						   _TASKSTOTALDATAWINSTARTX),
					    "total,",
					    1,
					    _TASKSDATAWINCOLS,
					    _TASKSDATAWINSTARTY,
					    _TASKSTOTALDATAWINSTARTX);
  wins.at(_TASKSRUNDATAWIN)->defineWindow(newwin(1,
						 _TASKSDATAWINCOLS,
						 _TASKSDATAWINSTARTY,
						 _TASKSRUNDATAWINSTARTX),
					  "running,",
					  1,
					  _TASKSDATAWINCOLS,
					  _TASKSDATAWINSTARTY,
					  _TASKSRUNDATAWINSTARTX);
  wins.at(_TASKSSLEEPDATAWIN)->defineWindow(newwin(1,
						   _TASKSDATAWINCOLS,
						   _TASKSDATAWINSTARTY,
						   _TASKSSLEEPDATAWINSTARTX),
					    "sleeping,",
					    1,
					    _TASKSDATAWINCOLS,
					    _TASKSDATAWINSTARTY,
					    _TASKSSLEEPDATAWINSTARTX);
  wins.at(_TASKSSTOPDATAWIN)->defineWindow(newwin(1,
						  _TASKSDATAWINCOLS,
						  _TASKSDATAWINSTARTY,
						  _TASKSSTOPDATAWINSTARTX),
					   "stopped,",
					   1,
					   _TASKSDATAWINCOLS,
					   _TASKSDATAWINSTARTY,
					   _TASKSSTOPDATAWINSTARTX);
  wins.at(_TASKSZOMBDATAWIN)->defineWindow(newwin(1,
						  _TASKSDATAWINCOLS,
						  _TASKSDATAWINSTARTY,
						  _TASKSZOMBDATAWINSTARTX),
					   "zombie",
					   1,
					   _TASKSDATAWINCOLS,
					   _TASKSDATAWINSTARTY,
					   _TASKSZOMBDATAWINSTARTX);
  wins.at(_CPUUSDATAWIN)->defineWindow(newwin(1,
					      _CPUDATAWINCOLS,
					      _CPUDATAWINSTARTY,
					      _CPUUSDATAWINSTARTX),
				       "us,",
				       1,
				       _CPUDATAWINCOLS,
				       _CPUDATAWINSTARTY,
				       _CPUUSDATAWINSTARTX);
  wins.at(_CPUSYDATAWIN)->defineWindow(newwin(1,
					      _CPUDATAWINCOLS,
					      _CPUDATAWINSTARTY,
					      _CPUSYDATAWINSTARTX),
				       "sy,",
				       1,
				       _CPUDATAWINCOLS,
				       _CPUDATAWINSTARTY,
				       _CPUSYDATAWINSTARTX); 
  wins.at(_CPUNIDATAWIN)->defineWindow(newwin(1,
					      _CPUDATAWINCOLS,
					      _CPUDATAWINSTARTY,
					      _CPUNIDATAWINSTARTX),
				       "ni,",
				       1,
				       _CPUDATAWINCOLS,
				       _CPUDATAWINSTARTY,
				       _CPUNIDATAWINSTARTX);
  wins.at(_CPUIDDATAWIN)->defineWindow(newwin(1,
					      _CPUDATAWINCOLS,
					      _CPUDATAWINSTARTY,
					      _CPUIDDATAWINSTARTX),	      
				       "id,",
				       1,
				       _CPUDATAWINCOLS,
				       _CPUDATAWINSTARTY,
				       _CPUIDDATAWINSTARTX);
  wins.at(_CPUWADATAWIN)->defineWindow(newwin(1,
					      _CPUDATAWINCOLS,
					      _CPUDATAWINSTARTY,
					      _CPUWADATAWINSTARTX),	      
				       "wa,",
				       1,
				       _CPUDATAWINCOLS,
				       _CPUDATAWINSTARTY,
				       _CPUWADATAWINSTARTX);
  wins.at(_CPUHIDATAWIN)->defineWindow(newwin(1,
					      _CPUDATAWINCOLS,
					      _CPUDATAWINSTARTY,
					      _CPUHIDATAWINSTARTX),
				       "hi,",
				       1,
				       _CPUDATAWINCOLS,
				       _CPUDATAWINSTARTY,
				       _CPUHIDATAWINSTARTX);
  wins.at(_CPUSIDATAWIN)->defineWindow(newwin(1,
					      _CPUDATAWINCOLS,
					      _CPUDATAWINSTARTY,
					      _CPUSIDATAWINSTARTX),	      
				       "si,",
				       1,
				       _CPUDATAWINCOLS,
				       _CPUDATAWINSTARTY,
				       _CPUSIDATAWINSTARTX);
  wins.at(_CPUSTDATAWIN)->defineWindow(newwin(1,
					      _CPUDATAWINCOLS,
					      _CPUDATAWINSTARTY,
					      _CPUSTDATAWINSTARTX),
				       "st",
				       1,
				       _CPUDATAWINCOLS,
				       _CPUDATAWINSTARTY,
				       _CPUSTDATAWINSTARTX);
  wins.at(_MEMTOTALDATAWIN)->defineWindow(newwin(1,
						 _MEMDATAWINCOLS,
						 _MEMWINSTARTY,
						 _MEMTOTALDATAWINSTARTX),  
					  "total,",
					  1,
					  _MEMDATAWINCOLS,
					  _MEMWINSTARTY,
					  _MEMTOTALDATAWINSTARTX);
  wins.at(_MEMFREEDATAWIN)->defineWindow(newwin(1,
						_MEMDATAWINCOLS,
						_MEMWINSTARTY,
						_MEMFREEDATAWINSTARTX),
					 "free,",
					 1,
					 _MEMDATAWINCOLS,
					 _MEMWINSTARTY,
					 _MEMFREEDATAWINSTARTX);
  wins.at(_MEMUSEDDATAWIN)->defineWindow(newwin(1,
						_MEMDATAWINCOLS,
						_MEMWINSTARTY,
						_MEMUSEDDATAWINSTARTX),
					 "used,",
					 1,
					 _MEMDATAWINCOLS,
					 _MEMWINSTARTY,
					 _MEMUSEDDATAWINSTARTX);
  wins.at(_MEMBUFFCACHEDATAWIN)->defineWindow(newwin(1,
						     _MEMDATAWINCOLS,
						     _MEMWINSTARTY,
						     _MEMBUFFCACHEDATAWINSTARTX),
					      "buff/cache",
					      1,
					      _MEMDATAWINCOLS,
					      _MEMWINSTARTY,
					      _MEMBUFFCACHEDATAWINSTARTX);
  wins.at(_SWAPTOTALDATAWIN)->defineWindow(newwin(1,
						     _MEMDATAWINCOLS,
						     _SWAPWINSTARTY,
						     _SWAPTOTALDATAWINSTARTX),  
					      "total,",
					      1,
					      _MEMDATAWINCOLS,
					      _SWAPWINSTARTY,
					      _SWAPTOTALDATAWINSTARTX);
  wins.at(_SWAPFREEDATAWIN)->defineWindow(newwin(1,
						    _MEMDATAWINCOLS,
						    _SWAPWINSTARTY,
						    _SWAPFREEDATAWINSTARTX),
					     "free,",
					     1,
					     _MEMDATAWINCOLS,
					     _SWAPWINSTARTY,
					     _SWAPFREEDATAWINSTARTX);
  wins.at(_SWAPUSEDDATAWIN)->defineWindow(newwin(1,
						    _MEMDATAWINCOLS,
						    _SWAPWINSTARTY,
						    _SWAPUSEDDATAWINSTARTX),
					     "used,",
					     1,
					     _MEMDATAWINCOLS,
					     _SWAPWINSTARTY,
					     _SWAPUSEDDATAWINSTARTX);
  wins.at(_MEMAVAILDATAWIN)->defineWindow(newwin(1,
						 _MEMDATAWINCOLS,
						 _SWAPWINSTARTY,
						 _MEMAVAILDATAWINSTARTX),
					  "avail Mem",
					  1,
					  _MEMDATAWINCOLS,
					  _SWAPWINSTARTY,
					  _MEMAVAILDATAWINSTARTX);
} // end of "defineTopWinsDataStartVals"



/*
  Function:
   defineTopWinsStartVals

  Description:
   Defines the allocated CursesWindows objects accessible with key/value pairs that
   contain WINDOW related variables for outputing dynamically read OS data.  

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   NONE
   
  Output:
   NONE
   
  Returns:
   NONE
*/
void defineTopWinsStartVals(const std::unordered_map<int, CursesWindow*>& wins)
{
  wins.at(_TASKSWIN)->defineWindow(newwin(1,
					  _TASKSWINCOLS,
					  _TASKSWINSTARTY,
					  _TASKSWINSTARTX),
				   "Tasks:",
				   1,
				   _TASKSWINCOLS,
				   _TASKSWINSTARTY,
				   _TASKSWINSTARTX);
  wins.at(_TASKSTOTALWIN)->defineWindow(newwin(1,
					       _TASKSTOTALWINCOLS,
					       _TASKSWINSTARTY,
					       _TASKSTOTALWINSTARTX),
					"total,",
					1,
					_TASKSTOTALWINCOLS,
					_TASKSWINSTARTY,
					_TASKSTOTALWINSTARTX);
  wins.at(_TASKSRUNWIN)->defineWindow(newwin(1,
					     _TASKSRUNWINCOLS,
					     _TASKSWINSTARTY,
					     _TASKSRUNWINSTARTX),
				      "running,",
				      1,
				      _TASKSRUNWINCOLS,
				      _TASKSWINSTARTY,
				      _TASKSRUNWINSTARTX);
  wins.at(_TASKSSLEEPWIN)->defineWindow(newwin(1,
					       _TASKSSLEEPWINCOLS,
					       _TASKSWINSTARTY,
					       _TASKSSLEEPWINSTARTX),
					"sleeping,",
					1,
					_TASKSSLEEPWINCOLS,
					_TASKSWINSTARTY,
					_TASKSSLEEPWINSTARTX);
  wins.at(_TASKSSTOPWIN)->defineWindow(newwin(1,
					      _TASKSSTOPWINCOLS,
					      _TASKSWINSTARTY,
					      _TASKSSTOPWINSTARTX),
				       "stopped,",
				       1,
				       _TASKSSTOPWINCOLS,
				       _TASKSWINSTARTY,
				       _TASKSSTOPWINSTARTX);
  wins.at(_TASKSZOMBWIN)->defineWindow(newwin(1,
					      _TASKSZOMBWINCOLS,
					      _TASKSWINSTARTY,
					      _TASKSZOMBWINSTARTX),
				       "zombie",
				       1,
				       _TASKSZOMBWINCOLS,
				       _TASKSWINSTARTY,
				       _TASKSZOMBWINSTARTX);
  wins.at(_CPUWIN)->defineWindow(newwin(1,
					_CPUWINCOLS,
					_CPUWINSTARTY,
					_CPUWINSTARTX),
				 "%CPU(s):",
				 1,
				 _CPUWINCOLS,
				 _CPUWINSTARTY,
				 _CPUWINSTARTX);
  wins.at(_CPUUSWIN)->defineWindow(newwin(1,
					  _CPUUSWINCOLS,
					  _CPUWINSTARTY,
					  _CPUUSWINSTARTX),
				   "us,",
				   1,
				   _CPUUSWINCOLS,
				   _CPUWINSTARTY,
				   _CPUUSWINSTARTX);
  wins.at(_CPUSYWIN)->defineWindow(newwin(1,
					  _CPUSYWINCOLS,
					  _CPUWINSTARTY,
					  _CPUSYWINSTARTX),
				   "sy,",
				   1,
				   _CPUSYWINCOLS,
				   _CPUWINSTARTY,
				   _CPUSYWINSTARTX); 
  wins.at(_CPUNIWIN)->defineWindow(newwin(1,
					  _CPUNIWINCOLS,
					  _CPUWINSTARTY,
					  _CPUNIWINSTARTX),
				   "ni,",
				   1,
				   _CPUNIWINCOLS,
				   _CPUWINSTARTY,
				   _CPUNIWINSTARTX);
  wins.at(_CPUIDWIN)->defineWindow(newwin(1,
					  _CPUIDWINCOLS,
					  _CPUWINSTARTY,
					  _CPUIDWINSTARTX),	      
				   "id,",
				   1,
				   _CPUIDWINCOLS,
				   _CPUWINSTARTY,
				   _CPUIDWINSTARTX);
  wins.at(_CPUWAWIN)->defineWindow(newwin(1,
					  _CPUWAWINCOLS,
					  _CPUWINSTARTY,
					  _CPUWAWINSTARTX),	      
				   "wa,",
				   1,
				   _CPUWAWINCOLS,
				   _CPUWINSTARTY,
				   _CPUWAWINSTARTX);
  wins.at(_CPUHIWIN)->defineWindow(newwin(1,
					  _CPUHIWINCOLS,
					  _CPUWINSTARTY,
					  _CPUHIWINSTARTX),
				   "hi,",
				   1,
				   _CPUHIWINCOLS,
				   _CPUWINSTARTY,
				   _CPUHIWINSTARTX);
  wins.at(_CPUSIWIN)->defineWindow(newwin(1,
					  _CPUSIWINCOLS,
					  _CPUWINSTARTY,
					  _CPUSIWINSTARTX),	      
				   "si,",
				   1,
				   _CPUSIWINCOLS,
				   _CPUWINSTARTY,
				   _CPUSIWINSTARTX);
  wins.at(_CPUSTWIN)->defineWindow(newwin(1,
					  _CPUSTWINCOLS,
					  _CPUWINSTARTY,
					  _CPUSTWINSTARTX),
				   "st",
				   1,
				   _CPUSTWINCOLS,
				   _CPUWINSTARTY,
				   _CPUSTWINSTARTX);
  wins.at(_MEMWIN)->defineWindow(newwin(1,
					_MEMWINCOLS,
					_MEMWINSTARTY,
					_MEMWINSTARTX),  
				 "MiB Mem :",
				 1,
				 _MEMWINCOLS,
				 _MEMWINSTARTY,
				 _MEMWINSTARTX);
  wins.at(_MEMTOTALWIN)->defineWindow(newwin(1,
					     _MEMTOTALWINCOLS,
					     _MEMWINSTARTY,
					     _MEMTOTALWINSTARTX),  
				      "total,",
				      1,
				      _MEMTOTALWINCOLS,
				      _MEMWINSTARTY,
				      _MEMTOTALWINSTARTX);
  wins.at(_MEMFREEWIN)->defineWindow(newwin(1,
					    _MEMFREEWINCOLS,
					    _MEMWINSTARTY,
					    _MEMFREEWINSTARTX),
					 "free,",
				     1,
				     _MEMFREEWINCOLS,
				     _MEMWINSTARTY,
				     _MEMFREEWINSTARTX);
  wins.at(_MEMUSEDWIN)->defineWindow(newwin(1,
					    _MEMUSEDWINCOLS,
					    _MEMWINSTARTY,
					    _MEMUSEDWINSTARTX),
				     "used,",
				     1,
				     _MEMUSEDWINCOLS,
				     _MEMWINSTARTY,
				     _MEMUSEDWINSTARTX);
  wins.at(_MEMBUFFCACHEWIN)->defineWindow(newwin(1,
						 _MEMBUFFCACHEWINCOLS,
						 _MEMWINSTARTY,
						 _MEMBUFFCACHEWINSTARTX),
					  "buff/cache",
					  1,
					  _MEMBUFFCACHEWINCOLS,
					  _MEMWINSTARTY,
					  _MEMBUFFCACHEWINSTARTX);


  wins.at(_SWAPWIN)->defineWindow(newwin(1,
					 _SWAPWINCOLS,
					 _SWAPWINSTARTY,
					 _SWAPWINSTARTX),  
				  "total,",
				  1,
				  _SWAPWINCOLS,
				  _SWAPWINSTARTY,
				  _SWAPWINSTARTX);
  wins.at(_SWAPTOTALWIN)->defineWindow(newwin(1,
						 _SWAPTOTALWINCOLS,
						 _SWAPWINSTARTY,
						 _SWAPTOTALWINSTARTX),  
					  "total,",
					  1,
					  _SWAPTOTALWINCOLS,
					  _SWAPWINSTARTY,
					  _SWAPTOTALWINSTARTX);
  wins.at(_SWAPFREEWIN)->defineWindow(newwin(1,
					     _SWAPFREEWINCOLS,
					     _SWAPWINSTARTY,
					     _SWAPFREEWINSTARTX),
				      "free,",
				      1,
				      _SWAPFREEWINCOLS,
				      _SWAPWINSTARTY,
				      _SWAPFREEWINSTARTX);
  wins.at(_SWAPUSEDWIN)->defineWindow(newwin(1,
						_SWAPUSEDWINCOLS,
						_SWAPWINSTARTY,
						_SWAPUSEDWINSTARTX),
					 "used,",
					 1,
					 _SWAPUSEDWINCOLS,
					 _SWAPWINSTARTY,
					 _SWAPUSEDWINSTARTX);
  wins.at(_MEMAVAILWIN)->defineWindow(newwin(1,
					     _MEMAVAILWINCOLS,
					     _SWAPWINSTARTY,
					     _MEMAVAILWINSTARTX),
				      "avail Mem",
				      1,
				      _MEMAVAILWINCOLS,
				      _SWAPWINSTARTY,
				      _MEMAVAILWINSTARTX);
} // end of "defineTopWinsStartVals"



/*
  Function:
   defineGraphWinStartVals

  Description:
   Defines the starting window values for the for the CPU Utilization and Main Memory
   Usage windows that the incoming wins parameter points to with Key/Value pairs.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   NONE
   
  Output:
   NONE
   
  Returns:
   NONE
*/
void defineGraphWinStartVals(const std::unordered_map<int, CursesWindow*>& wins)
{
  int numLines;
  int numCols;
  int startY;
  int startX;
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
} // end of "defineGraphWinsStartVals"


// THIS FUNCTION  will have to be changed for multithreaded approach
/*
  Function:
   defineTopWins

  Description:
   Uses incoming parameters to intialize and define window objects for
   data output to the very top line windows of the Bottom program.

  Input/Ouput:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
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
   NONE
   
  Returns:
   NONE
*/
void defineTopWins(const std::unordered_map<int, CursesWindow*>& wins,
		   const std::string HHMMSS,
		   const int numDays,
		   const int numHours,
		   const int numMinutes,
		   const std::vector<std::string> parsedLoadAvg,
		   const int& numUsers)
{
  std::string days = intToStr(numDays);
  std::string hours = intToStr(numHours);
  std::string minutes = intToStr(numMinutes);
  std::string users = intToStr(numUsers);  
  std::string outString;
  std::string timeType;
  std::string userString;
  std::string uptime;
  int uptimeDataCols = 0;
  int loadAvgWinCols = 0;
  int userCols = 0;
  int userDataCols = users.length();
  int uptimePostCols = 0;
  bool postWin = false;
  int nextWinStartX = 0;

  if(numDays < 1)
    {
      if(numHours < 1)
	{
	  uptime.append(minutes);
	  uptimeDataCols = minutes.length();
	  uptimePostCols = 4;  // 'min,'
	  timeType = "min,";
	  postWin = true;
	}
      else
	{
	  if(numHours < 10)
	    {
	      uptime.append(" ");
	      uptimeDataCols += 1;
	    }
	  uptime.append(hours);
	  uptime.append(":");
	  if(numMinutes < 10)
	    {
	      uptime.append("0");
	    }

	  uptime.append(minutes);
	  uptime.append(",");
	  uptimeDataCols += hours.length();
	  uptimeDataCols += 4;
	}
    }
  else if(numDays == 1)
    {
      uptime.append(days);
      uptimeDataCols = days.length();
      uptimePostCols = 4; // 'day,'
      timeType = "day,";
      postWin = true;
    }
  else
    {
      uptime.append(days);
      uptimeDataCols = days.length();
      uptimePostCols = 5; // 'days,'
      timeType = "days,";
      postWin = true;
    }

  if(numUsers == 1)
    {
      userCols = 5;
      userString = "user,";
    }
  else
    {
      userCols = 6;
      userString = "users,";
    }
  
  for(int i = 0; i < 3; i++)
    {
      loadAvgWinCols += parsedLoadAvg.at(i).length();
    }
  
  loadAvgWinCols += 4;
  wins.at(_TOPWIN)->defineWindow(newwin(1,
					_TOPWINCOLS,
					_TOPWINSTARTY,
					nextWinStartX),
				 "bottom",
				 1,
				 _TOPWINCOLS,
				 _TOPWINSTARTY,
				 nextWinStartX);
  outString = "bottom -";
  mvwaddstr(wins.at(_TOPWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
  nextWinStartX = wins.at(_TOPWIN)->getNumCols() +
    wins.at(_TOPWIN)->getStartX() + 1;
  wins.at(_TOPCURRTIMEWIN)->defineWindow(newwin(1,
						_TOPCURRTIMEWINCOLS,
						_TOPWINSTARTY,
						nextWinStartX),
					 "XX:XX:XX",
					 1,
					 _TOPCURRTIMEWINCOLS,
					 _TOPWINSTARTY,
					 nextWinStartX);
  outString = HHMMSS;
  mvwaddstr(wins.at(_TOPCURRTIMEWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());  

  nextWinStartX = wins.at(_TOPCURRTIMEWIN)->getNumCols() +
    wins.at(_TOPCURRTIMEWIN)->getStartX() + 1;
  wins.at(_TOPUPWIN)->defineWindow(newwin(1,
					  _TOPUPWINCOLS,
					  _TOPWINSTARTY,
					  nextWinStartX),
				   "up",
				   1,
				   _TOPUPWINCOLS,
				   _TOPWINSTARTY,
				   nextWinStartX);
  outString = "up";
  mvwaddstr(wins.at(_TOPUPWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());  
  nextWinStartX = wins.at(_TOPUPWIN)->getNumCols() +
    wins.at(_TOPUPWIN)->getStartX() + 1;  
  wins.at(_TOPUPDATAWIN)->defineWindow(newwin(1,
					      uptime.length(),
					      _TOPWINSTARTY,
					      nextWinStartX),
				       "",
				       1,
				       uptime.length(),
				       _TOPWINSTARTY,
				       nextWinStartX);
  outString = uptime;
  mvwaddstr(wins.at(_TOPUPDATAWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  if(postWin == true)
    {
      nextWinStartX = wins.at(_TOPUPDATAWIN)->getNumCols() +
	wins.at(_TOPUPDATAWIN)->getStartX() + 1;        
      wins.at(_TOPUPPOSTWIN)->defineWindow(newwin(1,
						  uptimePostCols,
						  _TOPWINSTARTY,
						  nextWinStartX),
					   "",
					   1,
					   uptimePostCols,
					   _TOPWINSTARTY,
					   nextWinStartX);
      outString = timeType;
      mvwaddstr(wins.at(_TOPUPPOSTWIN)->getWindow(),
		0,
		0,
		outString.c_str());  
      nextWinStartX = wins.at(_TOPUPPOSTWIN)->getNumCols() +
	wins.at(_TOPUPPOSTWIN)->getStartX() + 1;
    }
  else
    {
      nextWinStartX = wins.at(_TOPUPDATAWIN)->getNumCols() +
	wins.at(_TOPUPDATAWIN)->getStartX() + 1;
    }

  if(userDataCols < 10)
    {
      userDataCols = 2;
    }
  
  wins.at(_TOPUSERDATAWIN)->defineWindow(newwin(1,
						userDataCols,
						_TOPWINSTARTY,
						nextWinStartX),
					 "",
					 1,
					 userDataCols,
					 _TOPWINSTARTY,
					 nextWinStartX);
  outString = users;
  mvwaddstr(wins.at(_TOPUSERDATAWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());  
  nextWinStartX = wins.at(_TOPUSERDATAWIN)->getNumCols() +
    wins.at(_TOPUSERDATAWIN)->getStartX() + 1;        
  wins.at(_TOPUSERWIN)->defineWindow(newwin(1,
					    userCols,
					    _TOPWINSTARTY,
					    nextWinStartX),
				     "",
				     1,
				     userCols,
				     _TOPWINSTARTY,
				     nextWinStartX);

  outString = userString;
  mvwaddstr(wins.at(_TOPUSERWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());  
  nextWinStartX = wins.at(_TOPUSERWIN)->getNumCols() +
    wins.at(_TOPUSERWIN)->getStartX() + 2;
  wins.at(_TOPLOADAVGWIN)->defineWindow(newwin(1,
					       _TOPLOADAVGWINCOLS,
					       _TOPWINSTARTY,
					       nextWinStartX),
					"",
					1,
					_TOPLOADAVGWINCOLS,
					_TOPWINSTARTY,
					nextWinStartX);
  outString = "load average:";
  mvwaddstr(wins.at(_TOPLOADAVGWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());  

  nextWinStartX = wins.at(_TOPLOADAVGWIN)->getNumCols() +
    wins.at(_TOPLOADAVGWIN)->getStartX() + 1;
  wins.at(_TOPLOADAVGDATAWIN)->defineWindow(newwin(1,
						   loadAvgWinCols,
						   _TOPWINSTARTY,
						   nextWinStartX),
					    "",
					    1,
					    loadAvgWinCols,
					    _TOPWINSTARTY,
					    nextWinStartX);
  outString = parsedLoadAvg.at(0);
  outString.append(", ");
  outString.append(parsedLoadAvg.at(1));
  outString.append(", ");
  outString.append(parsedLoadAvg.at(2));  
  mvwaddstr(wins.at(_TOPLOADAVGDATAWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());  
} // end of "defineTopWins"



/*
  Function:
   updateHelpWindowDimensions

  Description:
   Determines the current screen size of the standard screen and deletes or
   creates the hel pwindow dependent on those values.  For example, if the
   current screen size is too small to fit the contents of the help window,
   the help window will delete until otherwise.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   NONE

  Output:
   NONE

  Returns:
   NONE
*/
void updateHelpWindowDimensions(const std::unordered_map<int, CursesWindow*>& wins)
{
  int numLines;
  int numCols;
  int startY;
  int startX;
  
  getmaxyx(stdscr, numLines, numCols);
  wins.at(_MAINWIN)->setNumLines(numLines);
  wins.at(_MAINWIN)->setNumCols(numCols);

  // handle help window check for terminal resizing
  if( ((_HELPWINMAXCOLS > numCols) ||
       (_HELPWINMAXLINES > numLines)) &&
      (wins.at(_HELPWIN)->getWindow() != nullptr) )
    {
      wins.at(_HELPWIN)->deleteWindow();
      wins.at(_HELPWIN)->setWindow(nullptr);
    }
  else if(wins.at(_HELPWIN)->getWindow() == nullptr)
    {
      wins.at(_HELPWIN)->defineWindow(newwin(wins.at(_HELPWIN)->getNumLines(),
					     wins.at(_HELPWIN)->getNumCols(),
					     0,
					     0),
				      "help",
				      wins.at(_HELPWIN)->getNumLines(),
				      wins.at(_HELPWIN)->getNumCols(),
				      0,
				      0);
    }

  wnoutrefresh(wins.at(_MAINWIN)->getWindow());
  wnoutrefresh(wins.at(_HELPWIN)->getWindow());    
  doupdate();
} // end of "updateHelpWindowDimensions"



/*
  Function:
   updateTopWinDimensions

  Description:
   Determines the current screen size of the standard screen and deletes or
   creates top windows dependent on those values.  For example, if the
   current screen size is too small to fit the contents any window being
   checked, that specific window will delete itself until otherwise.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   NONE

  Output:
   NONE

  Returns:
   NONE
*/
void updateTopWinDimensions(const std::unordered_map<int, CursesWindow*>& wins)
{
  int numLines;
  int numCols;
  int startY;
  int startX;
  
  getmaxyx(stdscr, numLines, numCols);
  wins.at(_MAINWIN)->setNumLines(numLines);
  wins.at(_MAINWIN)->setNumCols(numCols);

  // handle top windows terminal resizing
  for(int i = _TASKSWIN; i <= _MEMAVAILDATAWIN; i++)
    {
      if(wins.at(i)->getNumCols() + wins.at(i)->getStartX() > numCols ||
	 wins.at(i)->getStartY() >= numLines)
	{
	  wins.at(i)->deleteWindow();
	  wins.at(i)->setWindow(nullptr);
	}
      else if(wins.at(i)->getWindow() == nullptr)
	{
	  wins.at(i)->defineWindow(newwin(wins.at(i)->getNumLines(),
					  wins.at(i)->getNumCols(),
					  wins.at(i)->getStartY(),
					  wins.at(i)->getStartX()),
				   wins.at(i)->getWindowName(),
				   wins.at(i)->getNumLines(),
				   wins.at(i)->getNumCols(),
				   wins.at(i)->getStartY(),
				   wins.at(i)->getStartX());
	}
    }  
} // end of "updateTopWinDimensions"



/*
  Function:
   updateProcWinDimensions

  Description:
   Determines the current screen size of the standard screen and deletes or
   creates process windows dependent on those values.  For example, if the
   current screen size is too small to fit the contents any window being
   checked, that specific window will delete itself until otherwise.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   shiftY               - The current "vertical" shift state of the process
                          windows.			  

   shiftX               - The current "horizontal" shift state of the process
                          windows.
  Output:
   NONE

  Returns:
   NONE
*/
void updateProcWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
			     const int& shiftY,
			     const int& shiftX)
{
  int numLines;
  int numCols;
  
  getmaxyx(stdscr, numLines, numCols);
  wins.at(_MAINWIN)->setNumLines(numLines);
  wins.at(_MAINWIN)->setNumCols(numCols);  
  // handle process windows terminal resizing
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      // if window resize is too few columns or lines for the current windows
      if( (wins.at(i)->getNumCols() + wins.at(i)->getStartX() > numCols) ||
	  (numLines != wins.at(i)->getNumLines() + _YOFFSET) )
	{
	  // delete them
	  wins.at(i)->deleteWindow();
	  wins.at(i)->setWindow(nullptr);
	}
    }
  
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
} // end of "updateProcWinDimensions"



/*
  Function:
   updateGraphWinDimensions

  Description:
   Determines the current screen size of the standard screen and deletes or
   creates graph windows dependent on those values.  For example, if the
   current screen size is too small to fit the contents any window being
   checked, that specific window will delete itself until otherwise.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.  
  Input:
   cpuGraphCount        - A reference to a const integer type that represents
                          the current state of the cpu graph.

   memGraphCount        - A reference to a const integer type that represents
                          the current state of the mem graph.
  Output:
   NONE

  Returns:
   NONE
*/
void updateGraphWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
			      const int& cpuGraphCount,
			      const int& memGraphCount)
{
  int numLines;
  int numCols;
  int startY;
  int startX;
  getmaxyx(stdscr, numLines, numCols);
  wins.at(_MAINWIN)->setNumLines(numLines);
  wins.at(_MAINWIN)->setNumCols(numCols);
  
  // cpu utilization graph resize logic
  if((cpuGraphCount == 1) || (cpuGraphCount == 2))
    {
      if(cpuGraphCount == 1)
	{
	  // mode one
	  numLines = _GRAPHWINLINES;
	  numCols = 32;
	  startY = _YOFFSET + 1;
	  startX = wins.at(_MAINWIN)->getNumCols() - numCols;
	}
      else
	{
	  // mode two
	  numLines = _GRAPHWINLINES;
	  numCols = (wins.at(_MAINWIN)->getNumCols() -
		     wins.at(_COMMANDWIN)->getNumCols() -
		     wins.at(_COMMANDWIN)->getStartX() - 1);
	  startY = _YOFFSET + 1;
	  startX = wins.at(_MAINWIN)->getNumCols() - numCols; 
	}
      
      if( (wins.at(_COMMANDWIN)->getWindow() != nullptr) &&
	  (startX > wins.at(_COMMANDWIN)->getStartX() +
	   wins.at(_COMMANDWIN)->getNumCols()) &&
	  (startX + numCols  <= wins.at(_MAINWIN)->getNumCols()) &&
	  (startY + numLines < wins.at(_MAINWIN)->getNumLines()) &&
	  (wins.at(_CPUGRAPHWIN)->getWindow() == nullptr) &&
	  (numCols > 31) )
	{
	  wins.at(_CPUGRAPHWIN)->defineWindow(newwin(numLines,
						     numCols,
						     startY,
						     startX),
					      "_CPUGRAPHWIN",
					      numLines,
					      numCols,
					      startY,
					      startX);
	}
      else if( (wins.at(_COMMANDWIN)->getWindow() != nullptr) &&
	       (startX > wins.at(_COMMANDWIN)->getStartX() +
		wins.at(_COMMANDWIN)->getNumCols()) &&
	       (startX + numCols  <= wins.at(_MAINWIN)->getNumCols()) &&
	       (startY + numLines < wins.at(_MAINWIN)->getNumLines()) &&
	       (wins.at(_CPUGRAPHWIN)->getWindow() != nullptr) &&
	       (numCols > 31) )
	{
	  wins.at(_CPUGRAPHWIN)->deleteWindow();
	  wins.at(_CPUGRAPHWIN)->defineWindow(newwin(numLines,
						     numCols,
						     startY,
						     startX),
					      "_CPUGRAPHWIN",
					      numLines,
					      numCols,
					      startY,
					      startX);
	}
      else
	{
	  wins.at(_CPUGRAPHWIN)->deleteWindow();
	  wins.at(_CPUGRAPHWIN)->setWindow(nullptr);
	}
    }
  else if(cpuGraphCount == 3)
    {
      numLines = _GRAPHWINLINES + 10;
      if(numLines < 14)
	{
	  numLines = 14;
	}
      numCols = (wins.at(_MAINWIN)->getNumCols() -
		 wins.at(_COMMANDWIN)->getNumCols() -
		 wins.at(_COMMANDWIN)->getStartX() - 1);
      startY = _YOFFSET + 1;
      startX = wins.at(_MAINWIN)->getNumCols() - numCols;

      if( (wins.at(_COMMANDWIN)->getWindow() != nullptr) &&
	  (startX > wins.at(_COMMANDWIN)->getStartX() +
	   wins.at(_COMMANDWIN)->getNumCols()) &&
	  (startX + numCols  <= wins.at(_MAINWIN)->getNumCols()) &&
	  (startY + numLines < wins.at(_MAINWIN)->getNumLines()) &&
	  (wins.at(_CPUGRAPHWIN)->getWindow() == nullptr) &&
	  (numCols > 31) )
	{
	  wins.at(_CPUGRAPHWIN)->defineWindow(newwin(numLines,
						     numCols,
						     startY,
						     startX),
					      "_CPUGRAPHWIN",
					      numLines,
					      numCols,
					      startY,
					      startX);
	}
      else if( (wins.at(_COMMANDWIN)->getWindow() != nullptr) &&
	       (startX > wins.at(_COMMANDWIN)->getStartX() +
		wins.at(_COMMANDWIN)->getNumCols()) &&
	       (startX + numCols  <= wins.at(_MAINWIN)->getNumCols()) &&
	       (startY + numLines < wins.at(_MAINWIN)->getNumLines()) &&
	       (wins.at(_CPUGRAPHWIN)->getWindow() != nullptr) &&
	       (numCols > 31) )

	{
	  wins.at(_CPUGRAPHWIN)->deleteWindow();
	  wins.at(_CPUGRAPHWIN)->defineWindow(newwin(numLines,
						     numCols,
						     startY,
						     startX),
					      "_CPUGRAPHWIN",
					      numLines,
					      numCols,
					      startY,
					      startX);
	}
      else
	{
	  wins.at(_CPUGRAPHWIN)->deleteWindow();
	  wins.at(_CPUGRAPHWIN)->setWindow(nullptr);
	}
    }
  else
    {
      if(wins.at(_CPUGRAPHWIN)->getWindow() != nullptr)
	{
	  wins.at(_CPUGRAPHWIN)->deleteWindow();
	  wins.at(_CPUGRAPHWIN)->setWindow(nullptr);
	}
    }

  // main memory usage graph resize logic
  if((memGraphCount == 1) || (memGraphCount == 2))
    {
      if(memGraphCount == 1)
	{
	  // mode one
	  numLines = _GRAPHWINLINES;
	  numCols = 32;
	  startX = wins.at(_MAINWIN)->getNumCols() - numCols;
	  if(wins.at(_CPUGRAPHWIN)->getWindow() != nullptr)
	    {
	      startY = wins.at(_CPUGRAPHWIN)->getNumLines() +
		wins.at(_CPUGRAPHWIN)->getStartY();
	    }
	  else
	    {
	      startY = _YOFFSET + 1;
	    }
	}
      else
	{
	  // mode two
	  numLines = _GRAPHWINLINES;
	  numCols = (wins.at(_MAINWIN)->getNumCols() -
		     wins.at(_COMMANDWIN)->getNumCols() -
		     wins.at(_COMMANDWIN)->getStartX() - 1);
	  if(wins.at(_CPUGRAPHWIN)->getWindow() != nullptr)
	    {
	      startY = wins.at(_CPUGRAPHWIN)->getNumLines() +
		wins.at(_CPUGRAPHWIN)->getStartY();
	    }
	  else
	    {
	      startY = _YOFFSET + 1;
	    }

	  startX = wins.at(_MAINWIN)->getNumCols() - numCols; 
	}
      
      if( (wins.at(_COMMANDWIN)->getWindow() != nullptr) &&
	  (startX > wins.at(_COMMANDWIN)->getStartX() +
	   wins.at(_COMMANDWIN)->getNumCols()) &&
	  (startX + numCols  <= wins.at(_MAINWIN)->getNumCols()) &&
	  (startY + numLines < wins.at(_MAINWIN)->getNumLines()) &&
	  (wins.at(_MEMGRAPHWIN)->getWindow() == nullptr) &&
	  (numCols > 31) )
	{
	  wins.at(_MEMGRAPHWIN)->defineWindow(newwin(numLines,
						     numCols,
						     startY,
						     startX),
					      "_MEMGRAPHWIN",
					      numLines,
					      numCols,
					      startY,
					      startX);
	}
      else if( (wins.at(_COMMANDWIN)->getWindow() != nullptr) &&
	       (startX > wins.at(_COMMANDWIN)->getStartX() +
		wins.at(_COMMANDWIN)->getNumCols()) &&
	       (startX + numCols  <= wins.at(_MAINWIN)->getNumCols()) &&
	       (startY + numLines < wins.at(_MAINWIN)->getNumLines()) &&
	       (wins.at(_MEMGRAPHWIN)->getWindow() != nullptr) &&
	       (numCols > 31) )
	{
	  wins.at(_MEMGRAPHWIN)->deleteWindow();
	  wins.at(_MEMGRAPHWIN)->defineWindow(newwin(numLines,
						     numCols,
						     startY,
						     startX),
					      "_MEMGRAPHWIN",
					      numLines,
					      numCols,
					      startY,
					      startX);
	}
      else
	{
	  wins.at(_MEMGRAPHWIN)->deleteWindow();
	  wins.at(_MEMGRAPHWIN)->setWindow(nullptr);
	}
    }
  else if(memGraphCount == 3)
    {
      numLines = _GRAPHWINLINES + 10;      
      if(numLines < 14)
	{
	  numLines = 14;
	}
      
      numCols = (wins.at(_MAINWIN)->getNumCols() -
		 wins.at(_COMMANDWIN)->getNumCols() -
		 wins.at(_COMMANDWIN)->getStartX() - 1);
      if(wins.at(_CPUGRAPHWIN)->getWindow() != nullptr)
	{
	  startY = wins.at(_CPUGRAPHWIN)->getNumLines() +
	    wins.at(_CPUGRAPHWIN)->getStartY();
	}
      else
	{
	  startY = _YOFFSET + 1;
	}      
      startX = wins.at(_MAINWIN)->getNumCols() - numCols;

      if( (wins.at(_COMMANDWIN)->getWindow() != nullptr) &&
	  (startX > wins.at(_COMMANDWIN)->getStartX() +
	   wins.at(_COMMANDWIN)->getNumCols()) &&
	  (startX + numCols  <= wins.at(_MAINWIN)->getNumCols()) &&
	  (startY + numLines < wins.at(_MAINWIN)->getNumLines()) &&
	  (wins.at(_MEMGRAPHWIN)->getWindow() == nullptr) &&
	  (numCols > 31) )
	{
	  wins.at(_MEMGRAPHWIN)->defineWindow(newwin(numLines,
						     numCols,
						     startY,
						     startX),
					      "_MEMGRAPHWIN",
					      numLines,
					      numCols,
					      startY,
					      startX);
	}
      else if( (wins.at(_COMMANDWIN)->getWindow() != nullptr) &&
	       (startX > wins.at(_COMMANDWIN)->getStartX() +
		wins.at(_COMMANDWIN)->getNumCols()) &&
	       (startX + numCols  <= wins.at(_MAINWIN)->getNumCols()) &&
	       (startY + numLines < wins.at(_MAINWIN)->getNumLines()) &&
	       (wins.at(_MEMGRAPHWIN)->getWindow() != nullptr) &&
	       (numCols > 31) )
	{
	  wins.at(_MEMGRAPHWIN)->deleteWindow();
	  wins.at(_MEMGRAPHWIN)->defineWindow(newwin(numLines,
						     numCols,
						     startY,
						     startX),
					      "_MEMGRAPHWIN",
					      numLines,
					      numCols,
					      startY,
					      startX);
	}
      else
	{
	  wins.at(_MEMGRAPHWIN)->deleteWindow();
	  wins.at(_MEMGRAPHWIN)->setWindow(nullptr);
	}
    }
  else
    {
      if(wins.at(_MEMGRAPHWIN)->getWindow() != nullptr)
	{
	  wins.at(_MEMGRAPHWIN)->deleteWindow();
	  wins.at(_MEMGRAPHWIN)->setWindow(nullptr);
	}
    }
} // end of "updateGraphWinDimensions"



/*
  Function:
   createColorLine

  Description:
   Creates a string of white space chacaters with length of the incoming
   parameter and returns it to the caller.

  Input/Output:
   NONE
   
  Input:
   len                  - A reference to a constant integer type which holds
                          the total length of whitespace characters to
			  define in the string.
  Output:
   NONE

  Returns:
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
   updateWinDimensions

  Description:
   A major function that gets the current dimensions of the standard screen
   and determines if any allocated window fits within those dimensions. Minor
   functions are called to assist with this determination.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   shiftY               - The current "vertical" shift state of the process
                          windows. 			  

   shiftX               - The current "horizontal" shift state of the process
                          windows.

   cpuGraphCount        - A reference to a const integer type that represents
                          the current state of the cpu graph.

   memGraphCount        - A reference to a const integer type that represents
                          the current state of the mem graph.			  
  Output:
   NONE

  Returns:
   NONE
*/
void updateWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
			 const int& shiftY,
			 const int& shiftX,
			 const int& cpuGraphCount,
			 const int& memGraphCount)
{
  int numLines;
  int numCols;
  int startY;
  int startX;
  
  getmaxyx(stdscr, numLines, numCols);
  wins.at(_MAINWIN)->setNumLines(numLines);
  wins.at(_MAINWIN)->setNumCols(numCols);
  updateTopWinDimensions(wins);
  updateProcWinDimensions(wins,
			  shiftY,
			  shiftX);
  updateGraphWinDimensions(wins,
			   cpuGraphCount,
			   memGraphCount);

  // print the color line to the main win
  std::string colorLine = createColorLine(wins.at(_MAINWIN)->getNumCols());
  printLine(wins,
	    _YOFFSET,
	    0,
	    _BLACK_TEXT,
	    _MAINWIN,
	    colorLine);
  refreshAllWins(wins);
} // end of "updateWinDimensions"



/*
  Function:
   attronProcWins

  Description:
   This function iterates through the list of process windows enabling the
   attribute parameter for each currently allocated window in the loop range.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.

   attr 	        - A const integer type that should contain the
                          desired attribute to "turn on" for the process
			  windows.
  Output:
   NONE

  Returns:
   NONE
*/
void attronProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		    const int attr)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), attr);
    }  
} // end of "attronProcWins"



/*
  Function:
   attroffProcWins

  Description:
   This function iterates through the list of process windows disabling the
   attribute parameter for each currently allocated window in the loop range.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.

   attr 	        - A const integer type that should contain the
                          desired attribute to "turn on" for the process
			  windows.
  Output:
   NONE

  Returns:
   NONE
*/
void attroffProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		     const int attr)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      wattroff(wins.at(i)->getWindow(), attr);
    }  
} // end of "attroffProcWins"



/*
  Function:
   attronTopDataWins

  Description:
   This function iterates through the list of top data windows enabling the
   attribute parameter for each currently allocated window in the loop range.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.

   attr 	        - A const integer type that should contain the
                          desired attribute to "turn on" for the process
			  windows.
  Output:
   NONE

  Output:
   NONE
*/
void attronTopDataWins(std::unordered_map<int, CursesWindow*>& wins,
		       const int attrs)
{
  for(int i = _TASKSTOTALDATAWIN; i <= _MEMAVAILDATAWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), attrs);
    }
} // end of "attronTopDataWins"



/*
  Function:
   attroffTopDataWins

  Description:
   This function iterates through the list of top data windows enabling the
   attribute parameter for each currently allocated window in the loop range.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.

   attr 	        - A const integer type that should contain the
                          desired attribute to "turn on" for the process
			  windows.
  Output:
   NONE

  Returns:
   NONE
*/
void attroffTopDataWins(std::unordered_map<int, CursesWindow*>& wins,
			const int attrs)
{
  for(int i = _TASKSTOTALDATAWIN; i <= _MEMAVAILDATAWIN; i++)
    {
      wattroff(wins.at(i)->getWindow(), attrs);
    }
} // end of "attroffTopDataWins"



/*
  Function:
   attronTasksDataWins

  Description:
   This function iterates through the list of tasks data windows enabling the
   attribute parameter for each currently allocated window in the loop range.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.

   attr 	        - A const integer type that should contain the
                          desired attribute to "turn on" for the process
			  windows.  
  Output:
   NONE

  Returns:
   NONE
*/
void attronTasksDataWins(std::unordered_map<int, CursesWindow*>& wins,
			 const int attrs)
{
  for(int i = _TASKSTOTALDATAWIN; i <= _TASKSZOMBDATAWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "attronTasksDataWins"



/*
  Function:
   attroffTasksDataWins
  
  Description:
   This function iterates through the list of tasks data windows disabling the
   attribute parameter for each currently allocated window in the loop range.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.

   attr 	        - A const integer type that should contain the
                          desired attribute to "turn on" for the process
			  windows.  
  Output:
   NONE

  Returns
   NONE
*/
void attroffTasksDataWins(const std::unordered_map<int, CursesWindow*>& wins,
			  const int attrs)
{
  for(int i = _TASKSTOTALDATAWIN; i <= _TASKSZOMBDATAWIN; i++)
    {
      wattroff(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "attroffTasksDataWins"



/*
  Function:
   attronCpusDataWins

  Description:
   This function iterates through the list of CPU(s) data windows enabling the
   attribute parameter for each currently allocated window in the loop range.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.

   attr 	        - A const integer type that should contain the
                          desired attribute to "turn on" for the process
			  windows.
  Output:
   NONE

  Returns:
   NONE
*/
void attronCpusDataWins(std::unordered_map<int, CursesWindow*>& wins,
			const int attrs)
{
  for(int i = _CPUUSDATAWIN; i <= _CPUSTDATAWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "attronCpusDataWins"



/*

  Function:
   attroffCpusDataWins
   
  Description:
   This function iterates through the list of CPU(s) data windows disabling the
   attribute parameter for each currently allocated window in the loop range.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.

   attr 	        - A const integer type that should contain the
                          desired attribute to "turn on" for the process
			  windows.
  Output:
   NONE

  Returns:
   NONE
*/
void attroffCpusDataWins(std::unordered_map<int, CursesWindow*>& wins,
			 const int attrs)
{
  for(int i = _CPUUSDATAWIN; i <= _CPUSTDATAWIN; i++)
    {
      wattroff(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "boldOffCpusDataWins



/*
  Function:
   attronMemDataWins
   
  Description:
   This function iterates through the list of MiB Mem: data windows enabling the
   attribute parameter for each currently allocated window in the loop range.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.

   attr 	        - A const integer type that should contain the
                          desired attribute to "turn on" for the process
			  windows.
  Output:
   NONE

  Returns:
   NONE
*/
void attronMemDataWins(std::unordered_map<int, CursesWindow*>& wins,
		     int attrs)
{
  for(int i = _MEMTOTALDATAWIN; i <= _MEMAVAILDATAWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "attronMemDataWins"




/*
  Function:
   attroffMemDataWins

  Description:
   This function iterates through the list of MiB Mem: data windows disabling the
   attribute parameter for each currently allocated window in the loop range.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.

   attr 	        - A const integer type that should contain the
                          desired attribute to "turn on" for the process
			  windows.
  Output:
   NONE

  Returns:
   NONE      
*/
void attroffMemDataWins(std::unordered_map<int, CursesWindow*>& wins,
			const int attrs)
{
  for(int i = _MEMTOTALDATAWIN; i <= _MEMAVAILDATAWIN; i++)
    {
      wattroff(wins.at(i)->getWindow(), A_BOLD);
    }
} // end of "attroffMemDataWins"



/*
  Function:
   colorOnProcWins

  Description:
   Sets the a color pair attribute ON for the process windows.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.                  

  colorPair             - An integer that represents a color pair initialized in
                          the initializeCurses() function in this file.  The
			  pre-defined parameter value is defined in
			  _cursesWinConsts.hpp.
  Output:
   NONE

  Returns:
   NONE
*/
void colorOnProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		       int colorPair)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      wattron(wins.at(i)->getWindow(), COLOR_PAIR(colorPair));
    }
} // end of "colorOnProcWins"



/*
  Function:
   colorOffProcWins

  Description:
   Sets the a color pair attribute OFF for the process windows.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.                

  colorPair             - An integer that represents a color pair initialized in
                          the initializeCurses() function in this file.  The
			  pre-defined parameter value is defined in
			  _cursesWinConsts.hpp.
  Output:
   NONE

  Returns:
   NONE
*/
void colorOffProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		      const int colorPair)
{
  for(int i = _PIDWIN; i <= _COMMANDWIN; i++)
    {
      wattroff(wins.at(i)->getWindow(), COLOR_PAIR(colorPair));
    }  
} // end of "colorOffProcWins"



/*
  Function:
   printTasksWins

  Description:
   Prints the non-data windows for the "Tasks:" line.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.                  
  Output:
   NONE

  Returns:
   NONE
*/
void printTasksWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  std::string outString;

  outString = "Tasks:";
  mvwaddstr(wins.at(_TASKSWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "total,";
  mvwaddstr(wins.at(_TASKSTOTALWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "running,";
  mvwaddstr(wins.at(_TASKSRUNWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "sleeping,";
  mvwaddstr(wins.at(_TASKSSLEEPWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "stopped,";
  mvwaddstr(wins.at(_TASKSSTOPWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "zombie";
  mvwaddstr(wins.at(_TASKSZOMBWIN)->getWindow(),
	    0,
	    wins.at(_TASKSZOMBWIN)->getNumCols() - outString.length(),
	    outString.c_str());
} // end of "printTasksWins"



/*
  Function:
   printTasksDataWins

  Description:
   Prints the data values stored in the taskInfo parameter to the corresponding
   tasks data windows (_TASKSTOTAL/RUNNING/SLEEPING/STOPPED) from the
   _cursesWinConsts.hpp header file.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.              
			  
  taskInfo              - A constant reference to a TaskInfo object that contains
                          data to be printed to the tasks windows.
  Output:
   NONE

  Returns:
   NONE
*/
void printTasksDataWins(const std::unordered_map<int, CursesWindow*>& wins,
			const TaskInfo& taskInfo)
{
  std::string outString;

  outString = uIntToStr(taskInfo.getTotal());  
  mvwaddstr(wins.at(_TASKSTOTALDATAWIN)->getWindow(),
	    0,
	    wins.at(_TASKSTOTALDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = uIntToStr(taskInfo.getRunning());  
  mvwaddstr(wins.at(_TASKSRUNDATAWIN)->getWindow(),
	    0,
	    wins.at(_TASKSRUNDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = uIntToStr(taskInfo.getSleeping());  
  mvwaddstr(wins.at(_TASKSSLEEPDATAWIN)->getWindow(),
	    0,
	    wins.at(_TASKSSLEEPDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = uIntToStr(taskInfo.getStopped());  
  mvwaddstr(wins.at(_TASKSSTOPDATAWIN)->getWindow(),
	    0,
	    wins.at(_TASKSSTOPDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = uIntToStr(taskInfo.getZombie());  
  mvwaddstr(wins.at(_TASKSZOMBDATAWIN)->getWindow(),
	    0,
	    wins.at(_TASKSZOMBDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
} // end of "printTasksDataWins"



/*
  Function:
   printCpuWins

  Description
   Prints the non-data windows for the "CPU(s):" line.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.                
  Output:
   NONE

  Returns:
   NONE
*/
void printCpuWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  std::string outString;

  
  outString = "%Cpu(s):";
  mvwaddstr(wins.at(_CPUWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
  
  outString = "us,";
  mvwaddstr(wins.at(_CPUUSWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "sy,";
  mvwaddstr(wins.at(_CPUSYWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());  

  outString = "ni,";
  mvwaddstr(wins.at(_CPUNIWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "id,";
  mvwaddstr(wins.at(_CPUIDWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "wa,";
  mvwaddstr(wins.at(_CPUWAWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "hi,";
  mvwaddstr(wins.at(_CPUHIWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "si,";
  mvwaddstr(wins.at(_CPUSIWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "st";
  mvwaddstr(wins.at(_CPUSTWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
} // end of "printCpuWins"



/*
  Function:
   printCpuDataWins

  Description:
   Prints the data values stored in the cpuInfo parameter to the corresponding
   cpu data windows (_CPUUSWIN,SYWIN,NIWIN...) from the _cursesWinConsts.hpp header 
   file. 

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.            
			  
  cpuUsage               - A constant reference to a CPUUsage object that
                           should be defined with read CPU values.

  Output:
   NONE

  Returns:
   NONE
*/
void printCpuDataWins(const std::unordered_map<int, CursesWindow*>& wins,
		      const CPUUsage& cpuUsage)
{
  std::string outString;

  outString = doubleToStr(cpuUsage.us, 1);  
  mvwaddstr(wins.at(_CPUUSDATAWIN)->getWindow(),
	    0,
	    wins.at(_CPUUSDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(cpuUsage.sy, 1);  
  mvwaddstr(wins.at(_CPUSYDATAWIN)->getWindow(),
	    0,
	    wins.at(_CPUSYDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(cpuUsage.ni, 1);
  mvwaddstr(wins.at(_CPUNIDATAWIN)->getWindow(),
	    0,
	    wins.at(_CPUNIDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(cpuUsage.id, 1);
  mvwaddstr(wins.at(_CPUIDDATAWIN)->getWindow(),
	    0,
	    wins.at(_CPUIDDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(cpuUsage.wa, 1);
  mvwaddstr(wins.at(_CPUWADATAWIN)->getWindow(),
	    0,
	    wins.at(_CPUWADATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(cpuUsage.irq, 1);
  mvwaddstr(wins.at(_CPUHIDATAWIN)->getWindow(),
	    0,
	    wins.at(_CPUHIDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(cpuUsage.sirq, 1);
  mvwaddstr(wins.at(_CPUSIDATAWIN)->getWindow(),
	    0,
	    wins.at(_CPUSIDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(cpuUsage.st, 1);
  mvwaddstr(wins.at(_CPUSTDATAWIN)->getWindow(),
	    0,
	    wins.at(_CPUSTDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
} // end of "printCpuDataWins'



/*
  Function:
   printMemDataWins

  Description:
   Prints the data values stored in the memInfo parameter to the corresponding
   memMiB data windows (_MIBTOTALWIN,FREEWIN,USEDWIN...) from the _cursesWinConsts.hpp 
   header file.

  Input/Ouput:
   NONE
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.          

  cpuUsage               - A constant reference to a CPUUsage object that
                           should be defined with read CPU values.			  
  Output:
   NONE

  Returns:
   NONE
*/
void printMemDataWins(const std::unordered_map<int, CursesWindow*>& wins,
		      const MemInfo& memInfo)
{
  std::string outString;
  outString = doubleToStr(KiBToMiB(memInfo.getMemTotal()), 1);
  mvwaddstr(wins.at(_MEMTOTALDATAWIN)->getWindow(),
	    0,
	    wins.at(_MEMTOTALDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(KiBToMiB(memInfo.getMemFree()), 1);
  mvwaddstr(wins.at(_MEMFREEDATAWIN)->getWindow(),
	    0,
	    wins.at(_MEMFREEDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(KiBToMiB(memInfo.getMemUsed()), 1);
  mvwaddstr(wins.at(_MEMUSEDDATAWIN)->getWindow(),
	    0,
	    wins.at(_MEMUSEDDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(KiBToMiB(memInfo.getBuffCache()), 1);
  mvwaddstr(wins.at(_MEMBUFFCACHEDATAWIN)->getWindow(),
	    0,
	    wins.at(_MEMBUFFCACHEDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(KiBToMiB(memInfo.getSwapTotal()), 1);
  mvwaddstr(wins.at(_SWAPTOTALDATAWIN)->getWindow(),
	    0,
	    wins.at(_SWAPTOTALDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(KiBToMiB(memInfo.getSwapFree()), 1);
  mvwaddstr(wins.at(_SWAPFREEDATAWIN)->getWindow(),
	    0,
	    wins.at(_SWAPFREEDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(KiBToMiB(memInfo.getSwapUsed()), 1);
  mvwaddstr(wins.at(_SWAPUSEDDATAWIN)->getWindow(),
	    0,
	    wins.at(_SWAPUSEDDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
  outString = doubleToStr(KiBToMiB(memInfo.getMemAvailable()), 1);
  mvwaddstr(wins.at(_MEMAVAILDATAWIN)->getWindow(),
	    0,
	    wins.at(_MEMAVAILDATAWIN)->getNumCols() - outString.length(),
	    outString.c_str());
} // end of "printMemDataWins"



/*
  Function:
   printMemWins

  Description:
   Prints the non-data windows for the "MiB Mem:" line.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.                
  Output:
   NONE

  Returns:
   NONE   
*/
void printMemWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  std::string outString;
  
  outString = "MiB Mem :";
  mvwaddstr(wins.at(_MEMWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "total,";
  mvwaddstr(wins.at(_MEMTOTALWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
  
  outString = "free,";
  mvwaddstr(wins.at(_MEMFREEWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
  
  outString = "used,";
  mvwaddstr(wins.at(_MEMUSEDWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
  
  outString = "buff/cache";
  mvwaddstr(wins.at(_MEMBUFFCACHEWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
} // end of "printMemWins"



/*
  Function:
   printSwapWins

  Description:
   Prints the non-data windows for the "MiB Swap:" line.
  
  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.                
  Output:
   NONE

  Returns:
   NONE   
*/
void printSwapWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  std::string outString;
  
  outString = "MiB Swap:";
  mvwaddstr(wins.at(_SWAPWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  
  outString = "total,";
  mvwaddstr(wins.at(_SWAPTOTALWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
  
  outString = "free,";
  mvwaddstr(wins.at(_SWAPFREEWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());

  outString = "used,";
  mvwaddstr(wins.at(_SWAPUSEDWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
  
  outString = "avail Mem";
  mvwaddstr(wins.at(_MEMAVAILWIN)->getWindow(),
	    0,
	    0,
	    outString.c_str());
} // end of "printSwapWins"



/*
  Function:
   printWindowNames

  Description:
   Prints the window names for the columns "PID, USER, PR, NI...". All "printed" data 
   is stored in the screen buffer waiting for a call to refresh() to print it.

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.

   shiftY               - The current "vertical" shift state of the process
                          windows. 			  

   shiftX               - The current "horizontal" shift state of the process
                          windows.
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
   "row/column" screen position as well as memory.

   A simple loop is used to iterate over all the current process list objects
   to print those processes data.
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
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

   sortState            - A reference to a constant integer that should contain
                          the current sort state of the process lists.

   highlight            - A reference to a const bool object that should contain
                          the current highlight state for the process lists.
   
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
	      attronProcWins(wins, A_BOLD);
	    }
	  
	  // PID
	  if(highlight == true && sortState == _PIDWIN)
	    {
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD); 
	    }
	      
	  outString = intToStr(procData.at(pidList.at(i))->getPID());
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
	      outString = intToStr(tempPRVal);
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
	      
	  outString = intToStr(procData.at(pidList.at(i))->getNI());
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
	      
	  outString = uIntToStr(procData.at(pidList.at(i))->getVIRT());
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
	  outString = uIntToStr(procData.at(pidList.at(i))->getRES());
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
	      
	  outString = uIntToStr(procData.at(pidList.at(i))->getSHR());
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
	  int maxLen = wins.at(_COMMANDWIN)->getNumCols();
	  
	  if(maxLen > outString.length())
	    {
	      outString = outString.substr(0, maxLen);
	    }
	  
	  mvwaddstr(wins.at(_COMMANDWIN)->getWindow(),
		    posY,
		    0,
		    outString.c_str());

	  attroffProcWins(wins, A_BOLD);

	}
    }
} // end of "printProcs"



/*
  Function:
   printLine

  Description:
   Prints the outString parameter to the window parameter based upon the
   values contained in the row, col, and attr parameters.

  Input/Output:
   NONE
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.  

   row                  - A reference to a constant integer that holds
                          the Y-Position to print the string to.

   col                  - A reference to a constant integer that should
                          contain the column number for the desired window
			  to which the line shal be printed.

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

  Returns:
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
   printUserInput

  Description
   Prints user input to the incomining window.  Printing is restricted
   by conditional statements that ensure no printing can happen outside
   the bounds of the current window, as well as stdscr(main window).
   Based on those conditions, input is stored in the std::string object
   type reference parameter.

  Input/Output:
   inputString          - A refrence to a string object type that contains
                          input getch() has extracted based upon necessary
			  conditions. 
  
   yOffset              - A reference to an integer that contains the current
                          Y position in the window to print to.

			  
   xOffset              - A reference to an integer that contains the current
                          X position in the window to print to.  It is also
			  used as a controlling expression in the if else
			  structures.
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.
			  
   winIndex             - A const int type containing the key for the window
                          we wish to print user input to.

   input                - A reference to a constant integer that contains
                          the last value extracted by getch().  If it meets
			  necessary conditions, it will be printed to the
			  screen and appended to the inputString.
  Output:
   NONE

  Returns:
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
                          <int, CursesWindow*> type that contains pointers
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

  Returns:
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
   shiftProcWinsLeft

  Description:
   Shifts all the bottom windows left one shift aligning the new first
   window at the leftmost column of the MainWindow screen.

  Input/Ouput:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.
  Input:			  
   shiftX               - A constant integer type containing the current shift
                          state of the bottom windows.
			  
  Output:
   NONE

  Returns:
   NONE
*/
void shiftProcWinsLeft(const std::unordered_map<int, CursesWindow*>& wins,
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
} // end of "shiftProcWinsLeft"



/*
  Function:
   shiftProcWinsRight

  Description:
   Shifts all the bottom windows right one shift aligning the new first
   window at the leftmost column of the MainWindow screen.

  Input/Ouput:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.
  Input:			  
   shiftX               - A constant integer type containing the current shift
                          state of the bottom windows.
  Output:
   NONE

  Returns:
   NONE
*/
void shiftProcWinsRight(const std::unordered_map<int, CursesWindow*>& wins,
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

} // end of "shiftProcWinsRight"



/*
  Function:
   drawGraph
  
  Description:
   Draws a graph based on the incoming parameters to the desired parameter
   window.

  Input:

   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.

   winName              - A reference to a constant integer type that should
                          contain the name of the window in which to build
			  the graph in.

   vals                 - A reference to a constant integer type that should
                          contain the values in which to populate the graph
			  with.

   graphName            - A reference to a constant string object that should
                          contain the name that will be displayed at the top
			  of the graph window.

   graphScale           - A reference to a constant integer type that should
                          contain a value of 1 or 2 that represent the scale
			  in which the Y-axis of the graph will be defined
			  by.

  Output:
   NONE

  Returns:
   NONE
*/
void drawGraph(const std::unordered_map<int, CursesWindow*>& wins,
	       const int& winName,
	       std::queue<double> vals,
	       const std::string& graphName,
	       const int& graphScale)
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
	  int middleVal = valsCopy.at(i);
	  val = val/10;
	  int y = val * (numLines - 4);

	  if(graphScale == _GRAPHSCALETWO)
	    {
	      if((middleVal % 10) >= 5)
		{
		  y++;
		}
	    }

	  // get current utilization
	  int currVal = valsCopy.back();
	  outString = "%";
	  outString.append(intToStr(currVal));	  
	  wattron(wins.at(winName)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
	  
	  // print current value
	  if(currVal < 10)
	    {
	      int outX = numCols - 3;
	      mvwaddstr(wins.at(winName)->getWindow(),
			1,
			outX,
			outString.c_str());
	    }
	  else if(currVal > 9 && currVal < 100)
	    {
	      int outX = numCols - 4;

	      mvwaddstr(wins.at(winName)->getWindow(),
			1,
			outX,
			outString.c_str());
	    }
	  else
	    {
	      int outX = numCols - 5;
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

	      if((j-4) != 0)
		{
		  mvwaddch(wins.at(winName)->getWindow(),
			   numLines - k - 1,
			   j - 4,
			   ' ');
		}
	    }
	  j -= 2;
	}
    }

  // reset ncurses attributes
  wattroff(wins.at(winName)->getWindow(), A_BOLD);  
  wattron(wins.at(winName)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
} // end of "drawGraph"



/*
  Function:
   drawBoxes

  Description:
   Draws a box for every "WINDOW" that is currently initialized and stored
   in the "wins" object.

  Input/Output:
   NONE
   
  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
			  to all currently allocated CursesWindow objects
			  that can be indexed by values in the file
			  _cursesWinConsts.hpp.
  Output:
   NONE

  Returns:
   NONE
*/
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins)
{
  char val = 'A';
  std::unordered_map<int, CursesWindow*>::const_iterator it;
  
  for(it = wins.begin(); it != wins.end(); it++)
    {
      if(val == '[')
	{
	  val = 'A';
	}
      
      val++;
      
      if(it->second->getWindow() != nullptr)
	{
	  box(it->second->getWindow(), val, val);
	}
    }
} // end of "drawBoxes"
