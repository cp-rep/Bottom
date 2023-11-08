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
  progStates.insert(std::make_pair(_PROGSTATEHELP, 1)); // open help menu
  progStates.insert(std::make_pair(_PROGSTATEQUIT, 1)); // quit
  progStates.insert(std::make_pair(_PROGSTATEHL, 1)); // highlight column
  progStates.insert(std::make_pair(_PROGSTATEKILL, 1)); // enter kill pid state
  progStates.insert(std::make_pair(_PROGSTATECSV, 1)); // make csv file
} // end of "initializeProgramStates"



/*
  Function:
   updateStateValues

  Description:
   Updates the values that will be used in further function calls
   to change the running program state.
  
  Input:
   wins              - A reference to a constant object that is an
                          un ordered map containing all the allocated
			  curses windows addressable by the hash key
			  PID number.
			  
   progStates           - A reference to a constant object that is
                          an unordered map containing the main program
			  states such as highlight, help, and quit. It
			  is addressable from the hash keys via
			  _progStateConsts.hpp.

   userInput            - A reference to a const int that contains the
                          inputed user value that is used as the
			  switch state control expression.

   sortState            - A reference to an int that contains the current
                          sort state value to be used in further state
			  related function calls.

   prevState            - A reference to an int that contains the
                          previous sortState from the last loop iteration.

   progState            - A reference to an int that is used to
                          update the program state in further function
			  calls.

   highlight            - A reference to a constant bool object that
                          is used in a control expression to determine
			  if the highlight state should be updated.

   highlightIndex       - A reference to an int that contains the index
                          determining which column to highlight.

  Output:
   NONE
*/
void updateStateValues(std::unordered_map<int, CursesWindow*>& wins,
		       std::unordered_map<char, int>& progStates,
		       const int& userInput,
		       int& sortState,
		       int& prevState,
		       int& progState,
		       const bool& highlight,
		       int& highlightIndex)
{
  if(userInput != -1)
    {
      if(progStates[userInput])
	{
	  prevState = progState;
	  progState = userInput;
	}
      else if(userInput == '<' && sortState > _PIDWIN)
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
      else if(userInput == '>' && sortState < _COMMANDWIN)
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
    }
  highlightIndex = sortState;
} // end of "updateStateValues"



/*
  Function:
   changeProgramState

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
void changeProgramState(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			std::unordered_map<int, CursesWindow*>& wins,
			int& progState,
			const int& prevState,
			const int& sortState,
			bool& quit,
			bool& highlight,
			const int& defaultKillPid)
{
  switch(progState)
    {
    case _PROGSTATEHELP: // help
      break;
    case _PROGSTATEQUIT: // quit
      quit = true;
      break;
    case _PROGSTATEHL: // highlight
      if(highlight == true)
	{
	  highlight = false;
	}
      else if(highlight == false)
	{
	  highlight = true;
	}
      progState = prevState;
      break;
    case _PROGSTATEKILL:
      killState(allProcessInfo,
		wins,
		defaultKillPid);
      progState = prevState;
      break;
    case _PROGSTATECSV:
      makeDirectory(_CSV);
      createFileCSV(allProcessInfo,
		    _CSV);
      progState = 0;
      break;
    default:
      break;
    }
} // end of "changeProgramState"



/*
  Function:
   bottomWinsProcSortState

  Description:
   Sorts a vector of integer objects containing PID numbers that will be sorted
   based upon the selected user input for outputing sorted process data.
  
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
void bottomWinsProcSortState(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			     std::vector<int>& pids,
			     std::vector<int>& outPids,
			     const int& userInput)
{
  switch(userInput)
    {
    case _PIDWIN:
      outPids = pids;
      std::sort(outPids.begin(),
		outPids.end());
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
				   &ProcessInfo::getCOMMAND);
      break;
    default:
      break;
    }
} // end of "bottomWinProcSortState"



/*
  Function:
   bottomWinsShiftState

  Description:
   Uses a switch control structure to determine the shift state of the
   windows and process data in the bottom windows.  Shifting left and right
   will allocate or deallocate the windows from memory.  Shifting up and down
   simply determine the starting and ending values of process datato be
   outputed.

  Input:
   wins                 - A reference to a constant object that is an
                          un ordered map containing all the allocated
			  curses windows addressable by the hash key
			  PID number.
			  
  shiftState            - A reference to a constant integer that contains
                          the current shift state used in a switch control
			  structure that can be updated vai the up, down, left,
			  and right arrow keys.

  shiftY                - A reference to an integer value that reprensents
                          the current amount to shift the process list data
			  vertically.

  shiftX		- A reference to an integer value that represents
                          the current amount of windows that are "shifted"
			  in or out of the bottom window list horizontally.

  shiftDownMax          - A constant integer that contains the max amount
                          the process data can be shifted down in the output
			  window.
  Output:
   NONE
*/
void bottomWinsShiftState(std::unordered_map<int, CursesWindow*>& wins,
			  const int& shiftState,
			  int& shiftY,
			  int& shiftX,
			  const int shiftDownMax)
{
  switch(shiftState)
    {
    case KEY_UP:
      if(shiftY < 1)
	{
	  shiftY++;
	}
      break;
    case KEY_DOWN:
      if(abs(shiftY) < shiftDownMax)
	{
	  shiftY--;
	}
      break;
    case KEY_LEFT:
      if(shiftX > _PIDWIN)
	{
	  shiftBottomWinsRight(wins,
			       shiftX);
	  shiftX--;
	}
      break;
    case KEY_RIGHT:
      if(shiftX < _COMMANDWIN)
	{
	  shiftBottomWinsLeft(wins,
			      shiftX);
	  shiftX++;
	}
      break;
    default:
      break;
    }
} // end of "bottomWinShiftState"



/*
  Function:
   killState

  Description:
  
  Input:
  
  Output:
  
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
  int numCols = wins.at(_MAINWIN)->getMaxX() - outString.length();
  unsigned int signal = 0;

  // create the user input window
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
      
      refreshAllWins(wins);
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
	      // test if input was only the new line key for default
	      if(inputString.size() == 1 && inputString.at(0) == 10)
		{
		  kill(killPid, SIGTERM);
		  break;
		}
	      // user entered characters plus the new line
	      else if(inputString.at(inputString.size() - 1) == 10)
		{
		  // pop the new line character
		  inputString.pop_back();

		  // check if remaining string is numeric input for kill signal
		  if(isNumericString(inputString))
		    {
		      unsigned int signal = stringToInt(inputString);
		      kill(killPid, signal);
		      break;
		    }
		  // invalid signal prompt
		  else
		    {
		      curs_set(0);
		      outString = createColorLine(wins.at(_MAINWIN)->getNumCols());
		      printColorLine(wins,
				     _YOFFSET - 1,
				     _WHITE_TEXT,
				     _MAINWIN,
				     outString);
				     
		      // update prompt string
		      outString = " Invalid Signal ";


		      // update window settings for prompt
		      wattroff(wins.at(_MAINWIN)->getWindow(),
			       A_BOLD);
		      wattron(wins.at(_MAINWIN)->getWindow(),
			      COLOR_PAIR(_BLACK_TEXT));

		      // primpt prompt
		      mvwaddstr(wins.at(_MAINWIN)->getWindow(),
				_YOFFSET - 1,
				0,
				outString.c_str());

		      // reset to default window settings
		      wrefresh(wins.at(_MAINWIN)->getWindow());

		      wattron(wins.at(_MAINWIN)->getWindow(),
			       COLOR_PAIR(_WHITE_TEXT));
		      
		      doupdate();
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
    }

  // delete user input window as no longer needed
  wins.at(_USERINPUTWIN)->deleteWindow();

  // restore settings
  wattroff(wins.at(_MAINWIN)->getWindow(),
	   A_BOLD);
  curs_set(0);
} // end of "killState"
