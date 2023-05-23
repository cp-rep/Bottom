/*
  File: cursesWrappers.cpp
 */
#include "cursesWrappers.hpp"



/*
  Function:
  clearBottomWins

  Description:

  Input:

  Output:
 */
void clearBottomWins(const std::vector<CursesWindow*>& wins)
{
    werase(wins.at(_COMMAND)->getWindow());
    werase(wins.at(_PROCTIME)->getWindow());
    werase(wins.at(_PROCMEM)->getWindow());
    werase(wins.at(_PROCCPU)->getWindow());
    werase(wins.at(_S)->getWindow());
    werase(wins.at(_SHR)->getWindow());    
    werase(wins.at(_RES)->getWindow());
    werase(wins.at(_VIRT)->getWindow());
    werase(wins.at(_NI)->getWindow());
    werase(wins.at(_PR)->getWindow());
    werase(wins.at(_USER)->getWindow());
    werase(wins.at(_PID)->getWindow());
} // end of "clearBottomWins"



/*
  Function:
  attronBottomWins

  Description:

  Input:

  Output:
 */
void attronBottomWins(const std::vector<CursesWindow*>& wins, int attrs)
{  
  wattron(wins.at(_COMMAND)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_PROCTIME)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_PROCMEM)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_PROCCPU)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_S)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_SHR)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_RES)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_VIRT)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_NI)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_PR)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_USER)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(_PID)->getWindow(), COLOR_PAIR(attrs));
}



/*
  Function:
  attroffBottomWins

  Description:

  Input:

  Output:
 */
void attroffBottomWins(const std::vector<CursesWindow*>& wins, int attrs)
{
  wattroff(wins.at(_COMMAND)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_PROCTIME)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_PROCMEM)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_PROCCPU)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_S)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_SHR)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_RES)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_VIRT)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_NI)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_PR)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_USER)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(_PID)->getWindow(), COLOR_PAIR(attrs));
}



/*
  Function:
  printWindowNames

  Description:

  Input:

  Output:
 */
void printWindowNames(const std::vector<CursesWindow*>& wins)
{
  std::string outString;

  // PID
  outString = wins.at(_PID)->getWindowName();
  mvwaddstr(wins.at(_PID)->getWindow(),
	    0,
	    wins.at(_PID)->getNumCols() - outString.length(),
	    outString.c_str());
  // USER
  outString = wins.at(_USER)->getWindowName();
  mvwaddstr(wins.at(_USER)->getWindow(),
	    0,
	    0,
	    outString.c_str());
  // PR
  outString = wins.at(_PR)->getWindowName();
  mvwaddstr(wins.at(_PR)->getWindow(),
	    0,
	    wins.at(_PR)->getNumCols() - outString.length(),
	    outString.c_str());
  // NI
  outString = wins.at(_NI)->getWindowName();
  mvwaddstr(wins.at(_NI)->getWindow(),
	    0,
	    wins.at(_NI)->getNumCols() - outString.length(),
	    outString.c_str());
  // VIRT
  outString = wins.at(_VIRT)->getWindowName();
  mvwaddstr(wins.at(_VIRT)->getWindow(),
	    0,
	    wins.at(_VIRT)->getNumCols() - outString.length(),
	    outString.c_str());
  // RES
  outString = wins.at(_RES)->getWindowName();
  mvwaddstr(wins.at(_RES)->getWindow(),
	    0,
	    wins.at(_RES)->getNumCols() - outString.length(),
	    outString.c_str());
  // SHR
  outString = wins.at(_SHR)->getWindowName();
  mvwaddstr(wins.at(_SHR)->getWindow(),
	    0,
	    wins.at(_SHR)->getNumCols() - outString.length(),
	    outString.c_str());
  // S
  outString = wins.at(_S)->getWindowName();
  mvwaddstr(wins.at(_S)->getWindow(),
	    0,
	    wins.at(_S)->getNumCols() - outString.length(),
	    outString.c_str());
  // %CPU
  outString = wins.at(_PROCCPU)->getWindowName();
  mvwaddstr(wins.at(_PROCCPU)->getWindow(),
	    0,
	    wins.at(_PROCCPU)->getNumCols() - outString.length(),
	    outString.c_str());
  // %MEM
  outString = wins.at(_PROCMEM)->getWindowName();
  mvwaddstr(wins.at(_PROCMEM)->getWindow(),
	    0,
	    wins.at(_PROCMEM)->getNumCols() - outString.length(),
	    outString.c_str());
  // TIME+
  outString = wins.at(_PROCTIME)->getWindowName();
  mvwaddstr(wins.at(_PROCTIME)->getWindow(),
	    0,
	    wins.at(_PROCTIME)->getNumCols() - outString.length(),
	    outString.c_str());
  // COMMAND
  outString = wins.at(_COMMAND)->getWindowName();
  mvwaddstr(wins.at(_COMMAND)->getWindow(),
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
			     const std::vector<CursesWindow*>& wins)
{
  for(int k = sortedOut.size() - 1, g = startLine; k >= 0; k--, g++)
    {
      // PID
      mvwaddstr(wins.at(_PID)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getPID()).c_str());
      // USER
      mvwaddstr(wins.at(_USER)->getWindow(),
		g,
		0,
		pUmap.at(sortedOut.at(k).second)->getUSER().c_str());
      // PR
      mvwaddstr(wins.at(_PR)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getPR()).c_str());
      // NI
      mvwaddstr(wins.at(_NI)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getNI()).c_str());
      // VIRT
      mvwaddstr(wins.at(_VIRT)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getVIRT()).c_str());
      // RES
      mvwaddstr(wins.at(_RES)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getRES()).c_str());
      // SHR
      mvwaddstr(wins.at(_SHR)->getWindow(),
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getSHR()).c_str());
      // S
      mvwaddch(wins.at(_S)->getWindow(), 
	       g,
	       0,
	       pUmap.at(sortedOut.at(k).second)->getS());
      // %CPU
      mvwaddstr(wins.at(_PROCCPU)->getWindow(),
		g,
		0,
		doubleToStr(pUmap.at(sortedOut.at(k).second)->getCPUUsage(), 1).c_str());
      // %MEM
      mvwaddstr(wins.at(_PROCMEM)->getWindow(),
		g,
		0,
		"N/A");
      // TIME+
      mvwaddstr(wins.at(_PROCTIME)->getWindow(),
		g,
		0,
		"N/A");
      // COMMAND
      mvwaddstr(wins.at(_COMMAND)->getWindow(),
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
		const std::vector<int>& pidList,
		const std::unordered_map<int, ProcessInfo*>& pUmap,
		const std::vector<CursesWindow*>& wins,
		const bool& highlight)
{
  std::string outString;
  
  for(int i = 0; i < pUmap.size(); i++)
    {
      int posY = i + 1 + shiftY;
      if(posY == 0)
	{
	  posY =  1;
	}

      if(pUmap.at(pidList.at(i))->getUSER() == "-1")
	continue;

      // PID
      outString = std::to_string(pUmap.at(pidList.at(i))->getPID());
      mvwaddstr(wins.at(_PID)->getWindow(),
		posY,
		wins.at(_PID)->getNumCols() - outString.length(),
		outString.c_str());
      // USER
      mvwaddstr(wins.at(_USER)->getWindow(),
		posY,
		0,
		pUmap.at(pidList.at(i))->getUSER().c_str());
      // PR
      outString = std::to_string(pUmap.at(pidList.at(i))->getPR());
      mvwaddstr(wins.at(_PR)->getWindow(),
		posY,
		wins.at(_PR)->getNumCols() - outString.length(),
		outString.c_str());
      // NI
      outString = std::to_string(pUmap.at(pidList.at(i))->getNI());
      mvwaddstr(wins.at(_NI)->getWindow(),
		posY,
		wins.at(_NI)->getNumCols() - outString.length(),
		outString.c_str());
      // VIRT
      outString = std::to_string(pUmap.at(pidList.at(i))->getVIRT());
      mvwaddstr(wins.at(_VIRT)->getWindow(),
		posY,
		wins.at(_VIRT)->getNumCols() - outString.length(),
		outString.c_str());
      // RES
      outString = std::to_string(pUmap.at(pidList.at(i))->getRES());
      mvwaddstr(wins.at(_RES)->getWindow(),
		posY,
		wins.at(_RES)->getNumCols() - outString.length(),
		outString.c_str());
      // SHR
      outString = std::to_string(pUmap.at(pidList.at(i))->getSHR());
      mvwaddstr(wins.at(_SHR)->getWindow(),
		posY,
		wins.at(_SHR)->getNumCols() - outString.length(),
		outString.c_str());
      // S
      mvwaddch(wins.at(_S)->getWindow(),
	       posY,
	       0,
	       pUmap.at(pidList.at(i))->getS());
      // %CPU
      outString = doubleToStr(pUmap.at(pidList.at(i))->getCPUUsage(), 1);
      mvwaddstr(wins.at(_PROCCPU)->getWindow(),
		posY,
		wins.at(_PROCCPU)->getNumCols() - outString.length(),
		outString.c_str());
      // %MEM
      outString = doubleToStr(pUmap.at(pidList.at(i))->getMEMUsage(), 1);
      mvwaddstr(wins.at(_PROCMEM)->getWindow(),
		posY,
		wins.at(_PROCMEM)->getNumCols() - outString.length(),
		outString.c_str());
      // TIME+
      outString = pUmap.at(pidList.at(i))->getProcessCPUTime();
      mvwaddstr(wins.at(_PROCTIME)->getWindow(),
		posY,
		wins.at(_PROCTIME)->getNumCols() - outString.length(),
		outString.c_str());
      // COMMAND
      mvwaddstr(wins.at(_COMMAND)->getWindow(),
		posY,
		0,
		pUmap.at(pidList.at(i))->getCOMMAND().c_str());
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
void printColorLine(const std::vector<CursesWindow*>& wins,
		    const std::vector<int>& winNums,
		    const std::string& colorLine,
		    const int& row,
		    const int& attrs)
{
  for(int i = 0; i < winNums.size(); i++)
  {
    wattron(wins.at(winNums.at(i))->getWindow(), COLOR_PAIR(attrs));
    mvwaddstr(wins.at(winNums.at(i))->getWindow(),
	      row,
	      0,
	      colorLine.c_str());
    wattroff(wins.at(winNums.at(i))->getWindow(), COLOR_PAIR(attrs));    
  }
} // end of "printColorLine"

