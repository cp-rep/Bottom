/*
  File:
   changeProgramStates.hpp

   Description:
    Contains function definitions for functions in programStates.hpp that
    use user input to switch the current state of the Bottom program.
*/
#include "changeProgramStates.hpp"



/*
  Function:
   initializeProgramStates

  Description:
   Defines the program states that will operable via user input.
   
  Input:
   progStates           - A reference to an unordered_map<char, int> object
                          that is addressable via a character key from the
			  _progStateConsts.hpp file upon definition.
  Output:
   NONE
*/
void initializeProgramStates(std::unordered_map<char, int>& progStates)
{
  progStates.insert(std::make_pair(_STATEHELP, 1)); 
  progStates.insert(std::make_pair(_STATEQUIT, 1)); 
  progStates.insert(std::make_pair(_STATEHL, 1)); 
  progStates.insert(std::make_pair(_STATEKILL, 1));
  progStates.insert(std::make_pair(_STATECSV, 1)); 
  progStates.insert(std::make_pair(_STATESORTLEFT, 1));
  progStates.insert(std::make_pair(_STATESORTRIGHT, 1));
  progStates.insert(std::make_pair(_STATEKEYLEFT, 1));
  progStates.insert(std::make_pair(_STATEKEYRIGHT, 1));
  progStates.insert(std::make_pair(_STATEKEYUP, 1));
  progStates.insert(std::make_pair(_STATEKEYDOWN, 1));
  progStates.insert(std::make_pair(_ALLMOUSEEVENTS, 1));
  progStates.insert(std::make_pair(_MOUSEPOSITIONS, 1));
  progStates.insert(std::make_pair(_WINRESIZEEVENT, 1));
  progStates.insert(std::make_pair(_STATECPUGRAPH, 1));
  progStates.insert(std::make_pair(_STATEMEMGRAPH, 1));
} // end of "initializeProgramStates"



/*
  Function:
   updateProgramState

  Description:
   Updates the current main program state through a switch control
   structure dependent on previous state values and user input.

  Input:
   progState            - A reference to a int that is used to
                          update the program state.
			  
   prevState            - A reference to a constant int that contains the
                          previously update program state value.

   quit                 - A reference to a bool object that determines if
                          the program should end.

   highlight            - A reference to a bool object that
                          is used to update the current state value
			  for turning on or off highlighting of a
			  column.
  Output:
   NONE
*/
void updateProgramState(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			std::unordered_map<int, CursesWindow*>& wins,
			int& progState,
			const int& prevState,
			int& sortState,
			bool& quit,
			bool& highlight,
			const int& defaultKillPid,
			int& shiftY,
			int& shiftX,
			const int shiftDownMax,
			bool& cpuGraph,
			bool& memGraph,
			bool& stateChanged,
			int& cpuGraphCount,
			int& memGraphCount)
{
  int numLines;
  int numCols;
  int startY;
  int startX;
  
  switch(progState)
    {
    case _STATEHELP: // help
      helpState(wins);
      stateChanged = true;
      break;
    case _STATEQUIT: // quit
      quit = true;
      break;
    case _STATEHL: // highlight
      if(highlight == true)
	{
	  highlight = false;
	}
      else
	{
	  highlight = true;
	}
      break;
    case _STATEKILL: // kill state
      killState(allProcessInfo,
		wins,
		defaultKillPid);
      stateChanged = true;      
      break;
    case _STATECPUGRAPH: // cpu graph state
      numLines = 14;
      numCols = (((wins.at(_MAINWIN)->getNumCols() -
		   wins.at(_COMMANDWIN)->getNumCols() -
		   wins.at(_COMMANDWIN)->getStartX())/2) - 2);
      if(numCols %2 != 0)
	{
	  numCols--;
	}
      startY = _YOFFSET + 1;
      startX = wins.at(_MAINWIN)->getNumCols() - numCols;
      
      if(cpuGraph == false)
      	{
	  // create window
	  CursesWindow* graphWindow = new CursesWindow();
	  wins.insert(std::make_pair(_CPUGRAPHWIN, graphWindow));
	  wins.at(_CPUGRAPHWIN)->defineWindow(newwin(numLines,
						     numCols,
						     startY,
						     startX),
					      "_CPUGRAPHWIN",
					      numLines,
					      numCols,
					      startY,
					      startX);
	  // update mem graph
	  if(memGraph == true)
	    {
	      mvwin(wins.at(_MEMGRAPHWIN)->getWindow(),
			startY + numLines,
			wins.at(_MEMGRAPHWIN)->getStartX());		
		  
	    }
	  cpuGraph = true;
	  cpuGraphCount = 1;
	}
      else
	{
	  // resize logic
	  if(cpuGraphCount == 1)
	    {
	      numLines = ((numLines - 4) * 2) + 4;
	      numCols = ((numCols + 2) * 2) - 2;
	      startX = wins.at(_MAINWIN)->getNumCols() - numCols;
	      wins.at(_CPUGRAPHWIN)->setNumLines(numLines);
	      wins.at(_CPUGRAPHWIN)->setNumCols(numCols);
	      wins.at(_CPUGRAPHWIN)->setStartX(startX);
	      wins.at(_CPUGRAPHWIN)->setStartY(startY +
					       wins.at
					       (_CPUGRAPHWIN)->getNumLines());
	      // update mem graph
	      if(memGraph == true)
		{
		  mvwin(wins.at(_MEMGRAPHWIN)->getWindow(),
			wins.at(_CPUGRAPHWIN)->getNumLines() + _YOFFSET + 1,
			wins.at(_MEMGRAPHWIN)->getStartX());
		}

	      wresize(wins.at(_CPUGRAPHWIN)->getWindow(),
		      numLines,
		      numCols);
	      mvwin(wins.at(_CPUGRAPHWIN)->getWindow(),
		    startY,
		    startX);
	      cpuGraphCount = 2;
	    }
	  else if(cpuGraphCount == 2)
	    {
	      if(memGraph == true)
		{
		  mvwin(wins.at(_MEMGRAPHWIN)->getWindow(),
			_YOFFSET + 1,
			wins.at(_MEMGRAPHWIN)->getStartX());		
		  
		}
	      
	      // delete window
	      wins.at(_CPUGRAPHWIN)->deleteWindow();
	      delete(wins.at(_CPUGRAPHWIN));
	      wins.erase(_CPUGRAPHWIN);
	      cpuGraphCount = 0;
	      cpuGraph = false;
	    }
	}
      break;
    case _STATEMEMGRAPH:
      numLines = 14;
      numCols = (((wins.at(_MAINWIN)->getNumCols() -
		       wins.at(_COMMANDWIN)->getNumCols() -
		       wins.at(_COMMANDWIN)->getStartX())/2) - 2);
      if(numCols %2 != 0)
	{
	  numCols--;
	}      
      startY = _YOFFSET + 1;
      startX = wins.at(_MAINWIN)->getNumCols() - numCols;

      if(memGraph == false)
	{
	  if(cpuGraph == true)
	    {
	      startY = wins.at(_CPUGRAPHWIN)->getNumLines() + _YOFFSET + 1;
	    }
	  else
	    {
	      startY = _YOFFSET + 1;
	    }
	  
	  startX = wins.at(_MAINWIN)->getNumCols() - numCols;
	  
	  CursesWindow* graphWindow = new CursesWindow();
	  wins.insert(std::make_pair(_MEMGRAPHWIN, graphWindow));
	  wins.at(_MEMGRAPHWIN)->defineWindow(newwin(numLines,
						     numCols,
						     startY,
						     startX),
					      "_MEMGRAPHWIN",
					      numLines,
					      numCols,
					      startY,
					      startX);
	  memGraph = true;
	  memGraphCount = 1;
	}
      else
	{
	  if(memGraphCount == 1)
	    {
	      numLines = ((numLines - 4) * 2) + 4;
	      numCols = ((numCols + 2) * 2) - 2;
	      startX = wins.at(_MAINWIN)->getNumCols() - numCols;
	      if(cpuGraph == true)
		{
		  startY = wins.at(_CPUGRAPHWIN)->getNumLines() + _YOFFSET + 1;
		}
	      else
		{
		  startY = _YOFFSET + 1;
		}

	      wins.at(_MEMGRAPHWIN)->setNumLines(numLines);
	      wins.at(_MEMGRAPHWIN)->setNumCols(numCols);
	      wins.at(_MEMGRAPHWIN)->setStartY(startY);	      
	      wins.at(_MEMGRAPHWIN)->setStartX(startX);
	      
 	      wresize(wins.at(_MEMGRAPHWIN)->getWindow(),
		      numLines,
		      numCols);
	      mvwin(wins.at(_MEMGRAPHWIN)->getWindow(),
		    startY,
		    startX);	      

	      memGraphCount = 2;
	    }
	  else if (memGraphCount == 2)
	    {
	      wins.at(_MEMGRAPHWIN)->deleteWindow();
	      delete(wins.at(_MEMGRAPHWIN));
	      wins.erase(_MEMGRAPHWIN);
	      memGraphCount = 0;
	      memGraph = false;
	    }
	}
      break;
    case _STATECSV: // output csv file
      makeDirectory(_CSV);
      createFileCSV(allProcessInfo,
		    _CSV);
      break;
    case _STATESORTLEFT: // shift sort left
      if(sortState > _PIDWIN)
	{
	  if(highlight == true)
	    {
	      wattroff(wins.at(sortState)->getWindow(),
		       A_BOLD);
	      sortState--;
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD);
	    }
	  else
	    {
	      sortState--;
	    }
	}      
      break;      
    case _STATESORTRIGHT: // shift sort right 
      if(sortState < _COMMANDWIN)
	{
	  if(highlight == true)
	    {
	      wattroff(wins.at(sortState)->getWindow(),
		       A_BOLD);
	      sortState++;
	      wattron(wins.at(sortState)->getWindow(),
		      A_BOLD);
	    }
	  else
	    {
	      sortState++;
	    }
	}
      break;
    case _STATEKEYUP:
      if(shiftY < 1)
	{
	  shiftY++;
	}
      break;
    case _STATEKEYDOWN:
      if(abs(shiftY) < shiftDownMax)
	{
	  shiftY--;
	}
      break;
    case _STATEKEYLEFT:
      if(shiftX > _PIDWIN)
	{
	  // check room to shift
	  if(((wins.at(_COMMANDWIN)->getNumCols() + wins.at(_COMMANDWIN)->getStartX()) <=
	       wins.at(_MAINWIN)->getNumCols()) &&
	      ((wins.at(_COMMANDWIN)->getNumLines() + wins.at(_COMMANDWIN)->getStartY()) <=
		wins.at(_MAINWIN)->getNumLines()))
	    {
	
	      shiftBottomWinsRight(wins,
				   shiftX);
	      shiftX--;
	    }
	}
      break;
    case _STATEKEYRIGHT:
      if(shiftX < _COMMANDWIN)
	{

	  if(((wins.at(_COMMANDWIN)->getNumCols() + wins.at(_COMMANDWIN)->getStartX()) <
	       wins.at(_MAINWIN)->getNumCols() - 1) &&
	      ((wins.at(_COMMANDWIN)->getNumLines() + wins.at(_COMMANDWIN)->getStartY()) <=
	       wins.at(_MAINWIN)->getNumLines()))
	    {

	      shiftBottomWinsLeft(wins,
				  shiftX);
	      shiftX++;
	    }
	}
      break;      
    default:
      break;
    }

  progState = prevState;
} // end of "changeProgramState"



/*
  Function:
   updateSortState

  Description:
   Sorts a vector of integer objects containing PID numbers that will be sorted
   based upon the selected user input for outputing sorted process data.  This must
   be called before updateProgramState function.
  
  Input:
   allProcessInfo       - A reference to an unordered_map<int, ProcessInfo*> object
                          that contains all currently extracted process data from
			  the current PID list.

   pids                 - A reference to a vector<int> object containing the PID
                          numbers of the currently allocated processes.

   outPids              - A reference to a vector<int> object that will be used
                          as output list of sorted PID values.

   userInput            - A reference to a constant integer that holds the last
                          entered userInput value.
			  
  Output:
   NONE
 */
void updateSortState(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
		     std::vector<int>& pids,
		     std::vector<int>& outPids,
		     const int& sortState)
{
  switch(sortState)
    {
    case _PIDWIN:
      outPids = pids;
      std::sort(outPids.rbegin(),
		outPids.rend());
      break;
    case _USERWIN:
      outPids = sortValuesByPID(allProcessInfo,
				   pids,
				   &ProcessInfo::getUSER);
      break;
    case _PRWIN:
      outPids = sortValuesByPID(allProcessInfo,
				   pids,
				   &ProcessInfo::getPR);
      break;
    case _NIWIN:
      outPids = sortValuesByPID(allProcessInfo,
				   pids,
				   &ProcessInfo::getNI);
      break;
    case _VIRTWIN:
      outPids = sortValuesByPID(allProcessInfo,
				   pids,
				   &ProcessInfo::getVIRT);
      break;
    case _RESWIN:
      outPids = sortValuesByPID(allProcessInfo,
				   pids,
				   &ProcessInfo::getRES);
      break;
    case _SHRWIN:
      outPids = sortValuesByPID(allProcessInfo,
				   pids,
				   &ProcessInfo::getSHR);
      break;
    case _SWIN:
      outPids = sortValuesByPID(allProcessInfo,
				   pids,
				   &ProcessInfo::getS);
      break;
    case _PROCCPUWIN:
      outPids = sortValuesByPID(allProcessInfo,
				   pids,
				   &ProcessInfo::getCPUUsage);
      break;
    case _PROCMEMWIN:
      outPids = sortValuesByPID(allProcessInfo,
				   pids,
				   &ProcessInfo::getMEMUsage); 
      break;
    case _PROCTIMEWIN:
      outPids = sortValuesByPID(allProcessInfo,
				   pids,
				   &ProcessInfo::getProcessCPUTime);
      break;
    case _COMMANDWIN:
      outPids = sortValuesByPID(allProcessInfo,
				pids,
				&ProcessInfo::getCOMMANDUpper);
      break;
    default:
      break;
    }
} // end of "updateSortState"



/*
  Function:
   killState

  Description:
   Allows the user to send a signal to a process. If the signal is allowed by
   the kill() function, the signal will be successfully sent. Else, if any
   input does not meet the requirements of the kill() function, a logical
   reply will be output to the screen about the input error.
  
  Input:
   allProcessInfo       - A reference to an unordered_map<int, ProcessInfo*> object
                          that contains all currently extracted process data from
			  the current PID list.

   wins                 - A reference to a constant object that is an
                          un ordered map containing all the allocated
			  curses windows addressable by the hash key
			  PID number.
			  
   defaultKillPid       - A reference to a constant integer that holds the PID
                          for the first value of the current sorted list of
			  PIDs that represents the default PID to kill for
			  the current sort.
  Output:
   NONE

  Bad Cases Tested:
   Case 1: Blank Input + Invalid Signal
   Result: Invalid Signal

   Case 2: Blank Input + Characters
   Result: Invalid Signal

   Case 3: Characters
   Result: Unacceptable Integer

   Case 4: Invalid PID + Default Signal
   Result: Failed signal pid 'xxxx' with '15': No such process

   Case 5: Invalid PID + Valid User Input Signal
   Result: Failed signal pid 'xxxx' with 'x': No such process

   Case 6: Invalid PID + Invalid User Input Signal
   Result: Invalid Signal

   Case 7: Valid PID + Invalid Signal
   Result: Invalid Signal

   Case 8: Valid PID + Characters
   Result: Invalid Signal 
*/
void killState(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
	       std::unordered_map<int, CursesWindow*>& wins,
	       const int& defaultKillPid)
{
  std::string outString = "PID to signal/kill [default pid = ";
  outString.append(std::to_string(defaultKillPid));
  outString.append("] ");
		   
  std::string inputString;
  int input = 0;
  bool stopLoop = false;
  int xOffset = 0;
  int yOffset = 0;
  int numLines = 1;
  int numCols = wins.at(_MAINWIN)->getNumCols() - outString.length();
  unsigned int signal = 0;

  // create the user input window
  CursesWindow* userInputWindow = new CursesWindow();
  wins.insert(std::make_pair(_USERINPUTWIN, userInputWindow));  
  wins.at(_USERINPUTWIN)->defineWindow(newwin(numLines,
					      numCols,
					      _YOFFSET - 1,
					      outString.length()),
				       "UserInputWindow",
				       numLines,
				       numCols,
				       _YOFFSET - 1,
				       outString.length());
  
  // enable kill state curses settings
  curs_set(1);
  
  // output the kill prompt
  wattron(wins.at(_MAINWIN)->getWindow(),
	  A_BOLD);
  mvwaddstr(wins.at(_MAINWIN)->getWindow(),
	    _YOFFSET - 1,
	    0,
	    outString.c_str());
  wrefresh(wins.at(_MAINWIN)->getWindow());
  doupdate();  

  //  loop getting user input
  while(true)
    {
      input = getch();
      flushinp();
      printUserInput(wins,
		     _USERINPUTWIN,
		     input,
		     inputString,
		     yOffset,
		     xOffset);

      if(!inputString.empty())
	{
	  if(inputString.at(inputString.size() - 1) == 10)
	    {
	      inputString.pop_back();
	      break;
	    }
	}

      wrefresh(wins.at(_USERINPUTWIN)->getWindow());
      doupdate();
    }
  
  // we have received user input, enter if it meets criteria to kill a process
  if(isNumericString(inputString) || inputString.empty())
    { 
      int killPid;

      // set kill default
      if(inputString.empty())
	{
	  killPid = defaultKillPid;
	}
      // set kill entered PID      
      else
	{
	  killPid = stringToInt(inputString);

	}

      // create confirmation kill string
      inputString.clear();
      outString = "Send pid ";
      outString.append(std::to_string(killPid));
      outString.append(" signal [15/sigterm] ");

      // output string and update windows 11
      mvwaddstr(wins.at(_MAINWIN)->getWindow(),
		_YOFFSET - 1,
		0,
		outString.c_str());
      werase(wins.at(_USERINPUTWIN)->getWindow());

      // move user input window to new output location
      mvwin(wins.at(_USERINPUTWIN)->getWindow(),
	    _YOFFSET - 1,
	    outString.length());
      
      // reset input column offset since were getting a new input
      xOffset = 0;

      // loop for confirmation input
      while(true)
	{
	  input = getch();
	  flushinp();
	  printUserInput(wins,
			 _USERINPUTWIN,
			 input,
			 inputString,
			 yOffset,
			 xOffset);

	  // check if user entered input for type of kill signal
	  if(!inputString.empty())
	    {
	      // test if input was newline key for default kill signal
	      if(inputString.size() == 1 && inputString.at(0) == 10)
		{
		  if(kill(killPid, SIGTERM) != 0)
		    {
		      outString = " Failed signal pid '";
		      outString.append(std::to_string(killPid));
		      outString.append("' with '");
		      outString.append(std::to_string(SIGTERM));
		      outString.append(": No such process");
		      printBadInputString(wins,
					  _MAINWIN,
					  _YOFFSET -1,
					  0,
					  outString);
		      inputString.clear();
		      sleep(1.75);
		    }
		  
		  break;
		}
	      
	      // user entered characters plus the new line for kill signal
	      else if(inputString.at(inputString.size() - 1) == 10)
		{
		  // pop the new line character
		  inputString.pop_back();

		  // check if remaining string is numeric input for kill signal
		  if(isNumericString(inputString))
		    {
		      unsigned int signal = stringToInt(inputString);

		      // valid signal
		      if(isValidKillSignal(signal) == true)
			{
			  int result = kill(killPid, signal);
			  
			  if(result != 0)
			    {
			      outString = " Failed signal pid '";
			      outString.append(std::to_string(killPid));
			      outString.append("' with '");
			      outString.append(std::to_string(signal));
			      outString.append(": No such process");
			      printBadInputString(wins,
						  _MAINWIN,
						  _YOFFSET -1,
						  0,
						  outString);
			      inputString.clear();
			      sleep(1.75);
			    }
			}
		      // invalid signal
		      else
			{
			  outString = " Invalid Signal ";
			  printBadInputString(wins,
					      _MAINWIN,
					      _YOFFSET -1,
					      0,
					      outString);
			  inputString.clear();
			  sleep(1.75);
			}
			  
		      break;
		    }
		  // invalid signal
		  else
		    {
		      outString = " Invalid Signal ";
		      printBadInputString(wins,
					  _MAINWIN,
					  _YOFFSET -1,
					  0,
					  outString);
		      inputString.clear();
		      sleep(1.75);
		      break;
		    }
		}
	    }

	  refreshAllWins(wins);
	  doupdate();
	}
    }
  // unnacceptable input prompt
  else
    {
      outString = " Unacceptable Integer ";
      printBadInputString(wins,
			  _MAINWIN,
			  _YOFFSET -1,
			  0,
			  outString);
      inputString.clear();
      sleep(1.75);
    }

  // delete user input window
  wins.at(_USERINPUTWIN)->deleteWindow();
  delete(wins.at(_USERINPUTWIN));
  wins.erase(_USERINPUTWIN);

  // restore window settings
  wattroff(wins.at(_MAINWIN)->getWindow(),
	   A_BOLD);
  curs_set(0);
} // end of "killState"



/*
  Function:
   helpState

  Description:
   Outputs the help screen.  'q' exits the help screen.

  Input:
   wins                 - A reference to a constant object that is an
                          un ordered map containing all the allocated
			  curses windows addressable by the hash key
			  PID number.

  Output:
   NONE
*/
void helpState(std::unordered_map<int, CursesWindow*>& wins)
{
  std::string outString;
  int xOffset;
  int yOffset;

  clearAllWins(wins);
  CursesWindow* helpWindow = new CursesWindow();
  wins.insert(std::make_pair(_HELPWIN, helpWindow));
  wins.at(_HELPWIN)->defineWindow(newwin(wins.at(_MAINWIN)->getNumLines(),
					 wins.at(_MAINWIN)->getNumCols(),
					 0,
					 0),
				  "Help Window",
				  wins.at(_MAINWIN)->getNumLines(),
				  wins.at(_MAINWIN)->getNumCols(),
				  0,
				  0);

  // help window line
  yOffset = 0;
  xOffset = 0;
  wattron(wins.at(_HELPWIN)->getWindow(),
	  A_BOLD);
  outString = "Help for Interactive Commands";
  printLine(wins,
	    yOffset,	    
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  wattroff(wins.at(_HELPWIN)->getWindow(),
	   A_BOLD);
  yOffset++;
  outString = "Press '";
  printLine(wins,
	    yOffset,	    
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  xOffset += outString.length();
  outString = "q";
  wattron(wins.at(_HELPWIN)->getWindow(),
	  A_BOLD);
  printLine(wins,
	    yOffset,	    
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  wattroff(wins.at(_HELPWIN)->getWindow(),
	  A_BOLD);  
  xOffset += outString.length();
  outString = "' to exit help screen.";
  printLine(wins,
	    yOffset,	    
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);  
  
  // arrow keys
  yOffset += 2;
  xOffset = 0;
  outString = " - The '";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  xOffset += outString.length();
  outString = "Arrow Keys";
  wattron(wins.at(_HELPWIN)->getWindow(),
	  A_BOLD);
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  wattroff(wins.at(_HELPWIN)->getWindow(),
	   A_BOLD);
  xOffset += outString.length();
  outString = "' allow shifting windows left and right as well as ";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  outString = "the verticle scrolling of process output.";
  yOffset++;
  xOffset = 3;
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);

  // 'x' highlight key
  yOffset += 2;
  xOffset = 0;
  outString = " - The '";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  xOffset += outString.length();
  outString = "x";
  wattron(wins.at(_HELPWIN)->getWindow(),
	  A_BOLD);
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  wattroff(wins.at(_HELPWIN)->getWindow(),
	   A_BOLD);
  xOffset += outString.length();
  outString = "' key allows highlighting a particular process output column.";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);

  // '<' '>' sort state keys
  yOffset += 2;
  xOffset = 0;
  outString = " - The '";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  xOffset += outString.length();
  outString = "<";
  wattron(wins.at(_HELPWIN)->getWindow(),
	  A_BOLD);
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  wattroff(wins.at(_HELPWIN)->getWindow(),
	   A_BOLD);
  xOffset += outString.length();
  outString = "' '";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  wattron(wins.at(_HELPWIN)->getWindow(),
	  A_BOLD);
  xOffset += outString.length();
  outString = ">";
  wattron(wins.at(_HELPWIN)->getWindow(),
	  A_BOLD);
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  wattroff(wins.at(_HELPWIN)->getWindow(),
	   A_BOLD);
  xOffset += outString.length();
  outString = "' keys chnage which process output column to sort by.";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);    

  // 'k' kill state
  yOffset += 2;
  xOffset = 0;
  outString = " - The '";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  xOffset += outString.length();
  outString = "k";
  wattron(wins.at(_HELPWIN)->getWindow(),
	  A_BOLD);
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  wattroff(wins.at(_HELPWIN)->getWindow(),
	   A_BOLD);
  xOffset += outString.length();
  outString = "' key enters the \"kill\" state allowing the user to \"kill\"";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  yOffset++;
  xOffset = 3;
  outString = "desired processes.";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);

  // 'c' cpu window
  yOffset += 2;
  xOffset = 0;
  outString = " - The '";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  xOffset += outString.length();
  outString = "c";
  wattron(wins.at(_HELPWIN)->getWindow(),
	  A_BOLD);
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  wattroff(wins.at(_HELPWIN)->getWindow(),
	   A_BOLD);
  xOffset += outString.length();
  outString = "' key resizes and/or removes the cpu utilization window.";
    printLine(wins,
	      yOffset,
	      xOffset,
	      _WHITE_TEXT,
	      _HELPWIN,
	      outString);

  // 'm' mem window
  yOffset += 2;
  xOffset = 0;
  outString = " - The '";
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  xOffset += outString.length();
  outString = "m";
  wattron(wins.at(_HELPWIN)->getWindow(),
	  A_BOLD);
  printLine(wins,
	    yOffset,
	    xOffset,
	    _WHITE_TEXT,
	    _HELPWIN,
	    outString);
  wattroff(wins.at(_HELPWIN)->getWindow(),
	   A_BOLD);
  xOffset += outString.length();
  outString = "' key resizes and/or removes the main memory usage window.";
    printLine(wins,
	      yOffset,
	      xOffset,
	      _WHITE_TEXT,
	      _HELPWIN,
	      outString);
    
  // refresh and update windows
  wrefresh(wins.at(_MAINWIN)->getWindow());
  wrefresh(wins.at(_HELPWIN)->getWindow());    
  doupdate();

  int input;
  while(true)
    {
      input = getch();

      if(input == 'q')
	{
	  break;
	}      
    }
  
  wins.at(_HELPWIN)->deleteWindow();
  delete(wins.at(_HELPWIN));
  wins.erase(_HELPWIN);
} // end of "helpState"



/*
  Function:
   isValidKillSignal

  Description:
   Checks if the incoming integer contains a valid signal value to which a
   process can be killed.
  
  Input:
   signal               - A reference to a constant integer that contains
                          a value that represents the signal number
			  to kill a process with.
  
  Output:
   bool                 - A boolean object that is true if the signal value
                          is a valid kill signal, false otherwise.
*/
bool isValidKillSignal(const int& signal)
{
  bool isValid = false;
  
  switch(signal)
    {
    case SIGTERM:
      isValid = true;
      break;
    case SIGKILL:
      isValid = true;      
      break;
    case SIGHUP:
      isValid = true;      
      break;
    case SIGINT:
      isValid = true;      
      break;
    case SIGALRM:
      isValid = true;
      break;
    case SIGCHLD:
      isValid = true;
      break;
    case SIGPIPE:
      isValid = true;
      break;
    default:
      isValid = false;      
	break;
    }

  return isValid;
} // end of "isValidKillSignal"
