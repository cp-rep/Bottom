/*
  File: cursesFunctions.cpp
 */
#include "cursesFunctions.hpp"
#include <algorithm>



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

  for(int i = 0; i < wins.size(); i++)
    {
      if(wins.at(i)->getWindow() != nullptr)
	{
	  werase(wins.at(i)->getWindow());
	}
    }
}



/*
  Function:
  clearTopWins

  Description:
 */
void clearTopWins(const std::unordered_map<int, CursesWindow*>& wins)
{
    werase(wins.at(_TOPWIN)->getWindow());
    werase(wins.at(_TASKSWIN)->getWindow());
    werase(wins.at(_CPUWIN)->getWindow());
    werase(wins.at(_MEMWIN)->getWindow());
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
    werase(wins.at(_COMMANDWIN)->getWindow());
    werase(wins.at(_PROCTIMEWIN)->getWindow());
    werase(wins.at(_PROCMEMWIN)->getWindow());
    werase(wins.at(_PROCCPUWIN)->getWindow());
    werase(wins.at(_SWIN)->getWindow());
    werase(wins.at(_SHRWIN)->getWindow());    
    werase(wins.at(_RESWIN)->getWindow());
    werase(wins.at(_VIRTWIN)->getWindow());
    werase(wins.at(_NIWIN)->getWindow());
    werase(wins.at(_PRWIN)->getWindow());
    werase(wins.at(_USERWIN)->getWindow());
    werase(wins.at(_PIDWIN)->getWindow());
} // end of "clearBottomWins"







/*
  Function:
  attronBottomWins

  Description:

  Input:

  Output:
 */
void attronBottomWins(const std::unordered_map<int, CursesWindow*>& wins, int attrs)
{  
  wattron(wins.at(_COMMANDWIN)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_PROCTIMEWIN)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_PROCMEMWIN)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_PROCCPUWIN)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_SWIN)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_SHRWIN)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_RESWIN)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_VIRTWIN)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_NIWIN)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_PRWIN)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_USERWIN)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_PIDWIN)->getWindow(), COLOR_PAIR(attrs));
}



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
  wattroff(wins.at(_COMMANDWIN)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_PROCTIMEWIN)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_PROCMEMWIN)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_PROCCPUWIN)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_SWIN)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_SHRWIN)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_RESWIN)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_VIRTWIN)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_NIWIN)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_PRWIN)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_USERWIN)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_PIDWIN)->getWindow(), COLOR_PAIR(attrs));
}



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
  printSortedProcsReverse

  Description:

  Input:

  Output:
 */
void printSortedProcsReverse(const int& startLine,
			     const std::vector<std::pair<double, int>>& sortedOut,
			     const std::unordered_map<int, ProcessInfo*>& pUmap,
			     const std::unordered_map<int, CursesWindow*>& wins)
{
  for(int k = sortedOut.size() - 1, g = startLine; k >= 0; k--, g++)
    {
      // PID
      mvwaddstr(wins.at(_PIDWIN)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getPID()).c_str());
      // USER
      mvwaddstr(wins.at(_USERWIN)->getWindow(),
		g,
		0,
		pUmap.at(sortedOut.at(k).second)->getUSER().c_str());
      // PR
      mvwaddstr(wins.at(_PRWIN)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getPR()).c_str());
      // NI
      mvwaddstr(wins.at(_NIWIN)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getNI()).c_str());
      // VIRT
      mvwaddstr(wins.at(_VIRTWIN)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getVIRT()).c_str());
      // RES
      mvwaddstr(wins.at(_RESWIN)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getRES()).c_str());
      // SHR
      mvwaddstr(wins.at(_SHRWIN)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getSHR()).c_str());
      // S
      mvwaddch(wins.at(_SWIN)->getWindow(), 
	       g,
	       0,
	       pUmap.at(sortedOut.at(k).second)->getS());
      // %CPU
      mvwaddstr(wins.at(_PROCCPUWIN)->getWindow(),
		g,
		0,
		doubleToStr(pUmap.at(sortedOut.at(k).second)->getCPUUsage(), 1).c_str());
      // %MEM
      mvwaddstr(wins.at(_PROCMEMWIN)->getWindow(),
		g,
		0,
		"N/A");
      // TIME+
      mvwaddstr(wins.at(_PROCTIMEWIN)->getWindow(),
		g,
		0,
		"N/A");
      // COMMAND
      mvwaddstr(wins.at(_COMMANDWIN)->getWindow(),
		g,
		0,
		pUmap.at(sortedOut.at(k).second)->getCOMMAND().c_str());
    }
  
} // end of "printSortedProcsReverse"



/*
  Function:
  printProcs

  Description:

  Input:

  Output:
 */
void printProcs(const int& shiftY,
		const int& shiftX,
		const std::vector<int>& pidList,
		const std::unordered_map<int, ProcessInfo*>& pUmap,
		const std::unordered_map<int, CursesWindow*>& wins)
{
  std::string outString;

  for(int i = 0; i < pidList.size(); i++)
    {
      int posY = i + shiftY;
      if(posY != 0)
      	{
	  // PID
	  if(shiftX <= _PIDWIN && wins.at(_PIDWIN)->getWindow() != nullptr)
	    {
	      outString = std::to_string(pUmap.at(pidList.at(i))->getPID());
	      mvwaddstr(wins.at(_PIDWIN)->getWindow(),
			posY,
			wins.at(_PIDWIN)->getNumCols() - outString.length(),
			outString.c_str());
	    }
	  // USER      
	  if(shiftX <= _USERWIN && wins.at(_USERWIN)->getWindow() != nullptr)
	    {
	      outString = pUmap.at(pidList.at(i))->getUSER();
	      mvwaddstr(wins.at(_USERWIN)->getWindow(),
			posY,
			0,
			outString.c_str());
	    }
	  // PR
	  if(shiftX <= _PRWIN && wins.at(_PRWIN)->getWindow() != nullptr)
	    {
	      const int tempPRVal = pUmap.at(pidList.at(i))->getPR();
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
	      outString = std::to_string(pUmap.at(pidList.at(i))->getNI());
	      mvwaddstr(wins.at(_NIWIN)->getWindow(),
			posY,
			wins.at(_NIWIN)->getNumCols() - outString.length(),
			outString.c_str());
	    }
	  // VIRT
	  if(shiftX <= _VIRTWIN && wins.at(_VIRTWIN)->getWindow() != nullptr)
	    {
	      outString = std::to_string(pUmap.at(pidList.at(i))->getVIRT());
	      mvwaddstr(wins.at(_VIRTWIN)->getWindow(),
			posY,
			wins.at(_VIRTWIN)->getNumCols() - outString.length(),
			outString.c_str());
	    }
	  // RES
	  if(shiftX <= _RESWIN && wins.at(_RESWIN)->getWindow() != nullptr)
	    {
	      outString = std::to_string(pUmap.at(pidList.at(i))->getRES());
	      mvwaddstr(wins.at(_RESWIN)->getWindow(),
			posY,
			wins.at(_RESWIN)->getNumCols() - outString.length(),
			outString.c_str());
	    }
	  // SHR
	  if(shiftX <= _SHRWIN && wins.at(_SHRWIN)->getWindow() != nullptr)
	    {
	      outString = std::to_string(pUmap.at(pidList.at(i))->getSHR());
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
		       pUmap.at(pidList.at(i))->getS());
	    }

	  // %CPU
	  if(shiftX <= _PROCCPUWIN && wins.at(_PROCCPUWIN)->getWindow() != nullptr)
	    {
	      outString = doubleToStr(pUmap.at(pidList.at(i))->getCPUUsage(), 1);
	      mvwaddstr(wins.at(_PROCCPUWIN)->getWindow(),
			posY,
			wins.at(_PROCCPUWIN)->getNumCols() - outString.length(),
			outString.c_str());
	    }
	  // %MEM
	  if(shiftX <= _PROCMEMWIN && wins.at(_PROCMEMWIN)->getWindow() != nullptr)
	    {
	      outString = doubleToStr(pUmap.at(pidList.at(i))->getMEMUsage(), 1);
	      mvwaddstr(wins.at(_PROCMEMWIN)->getWindow(),
			posY,
			wins.at(_PROCMEMWIN)->getNumCols() - outString.length(),
			outString.c_str());
	    }
	  // TIME+
	  if(shiftX <= _PROCTIMEWIN && wins.at(_PROCTIMEWIN)->getWindow() != nullptr)
	    {
	      outString = pUmap.at(pidList.at(i))->getProcessCPUTime();
	      mvwaddstr(wins.at(_PROCTIMEWIN)->getWindow(),
			posY,
			wins.at(_PROCTIMEWIN)->getNumCols() - outString.length(),
			outString.c_str());
	    }
	  // COMMAND
	  if(shiftX <= _COMMANDWIN && wins.at(_COMMANDWIN)->getWindow() != nullptr)
	    {
	      outString = pUmap.at(pidList.at(i))->getCOMMAND();
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
  createLine

  Description:

  Input:

  Output:
 */
const std::string createColorLine(const int& len)
{
  std::string temp;
  for(int i = 0; i < len; i++)
    {
      temp.push_back(' ');
    }

  return temp;
} // end of "createLine"



/*
  Function:
  printColorLine

  Description:

  Input:

  Output:
 */
void printColorLine(const std::unordered_map<int, CursesWindow*>& wins,
		    const std::string& colorLine,
		    const int& row,
		    const int& attrs)
{
  /*
  for(int i = 0; i < winNums.size(); i++)
    {
      wattron(wins.at(winNums.at(i))->getWindow(), COLOR_PAIR(attrs));
      mvwaddstr(wins.at(winNums.at(i))->getWindow(),
		row,
		0,
		colorLine.c_str());
      wattroff(wins.at(winNums.at(i))->getWindow(), COLOR_PAIR(attrs));    
    }
 */
  wattron(wins.at(_MAINWIN)->getWindow(), COLOR_PAIR(attrs));
  mvwaddstr(wins.at(_MAINWIN)->getWindow(),
	    row,
	    0,
	    colorLine.c_str());
  wattroff(wins.at(_MAINWIN)->getWindow(), COLOR_PAIR(attrs));
} // end of "printColorLine"



/*
  Function:
  shiftBottomWinsLeft

  Description:

  Input:

  Output:
*/
void shiftBottomWinsLeft(std::unordered_map<int, CursesWindow*>& wins,
			 const int& shiftX)
{
  int totalShifts = 0;
  int currWin = shiftX;
  int startX = 0;

  // delete the current window at x-position 0
  wins.at(currWin)->deleteWindow();

  // move the window index forward to the first window that needs moving
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

  Input:

  Output:
*/
void shiftBottomWinsRight(std::unordered_map<int, CursesWindow*>& wins,
			  const int& shiftX)
{
  int currWin = shiftX;
  int totalShifts = 0;
  
  // set the data for the new starting window at x-position 0
  wins.at(shiftX - 1)->setStartX(0);

  // get the total number of needed shifts
  totalShifts = _COMMANDWIN - shiftX + 1; // = getTotalShifts(wins, currWin);

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
  getTotalShifts

  Description:

  Input:

  Output:

*/
int getTotalShifts(const std::unordered_map<int, CursesWindow*>& wins,
		   const int& winStartPos)
{
  int totalShifts = 0;
  
  for(int i = winStartPos; i < wins.size(); i++)
    {
      totalShifts++;
    }

  return totalShifts;
} // end of "getTotalShifts"



/*
  Function:
  drawBoxes

  Description:
  Draws a box for every "WINDOW" that is currently initialized.

  Input:

  Output:

*/
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins,
	       const int& shiftX)
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
