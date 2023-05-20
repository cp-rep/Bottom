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
    werase(wins.at(11)->getWindow());
    werase(wins.at(10)->getWindow());
    werase(wins.at(9)->getWindow());
    werase(wins.at(8)->getWindow());
    werase(wins.at(7)->getWindow());
    werase(wins.at(6)->getWindow());    
    werase(wins.at(5)->getWindow());
    werase(wins.at(4)->getWindow());
    werase(wins.at(3)->getWindow());
    werase(wins.at(2)->getWindow());
    werase(wins.at(1)->getWindow());
    werase(wins.at(0)->getWindow());
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
  wattron(wins.at(11)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(10)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(9)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(8)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(7)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(6)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(5)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(4)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(3)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(2)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(1)->getWindow(), COLOR_PAIR(attrs));
  wattron(wins.at(0)->getWindow(), COLOR_PAIR(attrs));
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
  wattroff(wins.at(11)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(10)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(9)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(8)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(7)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(6)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(5)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(4)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(3)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(2)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(1)->getWindow(), COLOR_PAIR(attrs));
  wattroff(wins.at(0)->getWindow(), COLOR_PAIR(attrs));
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
  outString = wins.at(11)->getWindowName();
  mvwaddstr(wins.at(11)->getWindow(),
	    0,
	    wins.at(11)->getNumCols() - outString.length(),
	    outString.c_str());
  // USER
  outString = wins.at(10)->getWindowName();
  mvwaddstr(wins.at(10)->getWindow(),
	    0,
	    0,
	    outString.c_str());
  // PR
  outString = wins.at(9)->getWindowName();
  mvwaddstr(wins.at(9)->getWindow(),
	    0,
	    wins.at(9)->getNumCols() - outString.length(),
	    outString.c_str());
  // NI
  outString = wins.at(8)->getWindowName();
  mvwaddstr(wins.at(8)->getWindow(),
	    0,
	    wins.at(8)->getNumCols() - outString.length(),
	    outString.c_str());
  // VIRT
  outString = wins.at(7)->getWindowName();
  mvwaddstr(wins.at(7)->getWindow(),
	    0,
	    wins.at(7)->getNumCols() - outString.length(),
	    outString.c_str());
  // RES
  outString = wins.at(6)->getWindowName();
  mvwaddstr(wins.at(6)->getWindow(),
	    0,
	    wins.at(6)->getNumCols() - outString.length(),
	    outString.c_str());
  // SHR
  outString = wins.at(5)->getWindowName();
  mvwaddstr(wins.at(5)->getWindow(),
	    0,
	    wins.at(5)->getNumCols() - outString.length(),
	    outString.c_str());
  // S
  outString = wins.at(4)->getWindowName();
  mvwaddstr(wins.at(4)->getWindow(),
	    0,
	    wins.at(4)->getNumCols() - outString.length(),
	    outString.c_str());
  // %CPU
  outString = wins.at(3)->getWindowName();
  mvwaddstr(wins.at(3)->getWindow(),
	    0,
	    wins.at(3)->getNumCols() - outString.length(),
	    outString.c_str());
  // %MEM
  outString = wins.at(2)->getWindowName();
  mvwaddstr(wins.at(2)->getWindow(),
	    0,
	    wins.at(2)->getNumCols() - outString.length(),
	    outString.c_str());
  // TIME+
  outString = wins.at(1)->getWindowName();
  mvwaddstr(wins.at(1)->getWindow(),
	    0,
	    wins.at(1)->getNumCols() - outString.length(),
	    outString.c_str());
  // COMMAND
  outString = wins.at(0)->getWindowName();
  mvwaddstr(wins.at(0)->getWindow(),
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
      mvwaddstr(wins.at(11)->getWindow(),  // PIDWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getPID()).c_str());
      mvwaddstr(wins.at(10)->getWindow(), // USERWin
		g,
		0,
		pUmap.at(sortedOut.at(k).second)->getUser().c_str());
      mvwaddstr(wins.at(9)->getWindow(), // PRWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getPR()).c_str());
      mvwaddstr(wins.at(8)->getWindow(), // NIWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getNI()).c_str());
      mvwaddstr(wins.at(7)->getWindow(), // VIRTWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getVirt()).c_str());
      mvwaddstr(wins.at(6)->getWindow(), // RESWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getRes()).c_str());
      mvwaddstr(wins.at(5)->getWindow(), // SHRWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getSHR()).c_str());
      mvwaddch(wins.at(4)->getWindow(), // SWin
	       g,
	       0,
	       pUmap.at(sortedOut.at(k).second)->getS());
      mvwaddstr(wins.at(3)->getWindow(), // PercentCPUWin
		g,
		0,
		doubleToStr(pUmap.at(sortedOut.at(k).second)->getCPUUsage(), 1).c_str());
      mvwaddstr(wins.at(2)->getWindow(), // PercentMEMWin
		g,
		0,
		"N/A");
      mvwaddstr(wins.at(1)->getWindow(), // TIMEWin
		g,
		0,
		"N/A");
      mvwaddstr(wins.at(0)->getWindow(), // COMMANDWin
		g,
		0,
		pUmap.at(sortedOut.at(k).second)->getCommand().c_str());
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
		const std::vector<CursesWindow*>& wins)
{
  std::string outString;
  
  for(int i = 0; i < pUmap.size(); i++)
    {
      int posY = i + 1 + shiftY;
      if(posY == 0)
	{
	  posY =  1;
	}

      if(pUmap.at(pidList.at(i))->getUser() == "-1")
	continue;

      // PID
      outString = std::to_string(pUmap.at(pidList.at(i))->getPID());
      mvwaddstr(wins.at(11)->getWindow(),
		posY,
		wins.at(11)->getNumCols() - outString.length(),
		outString.c_str());
      // USER
      mvwaddstr(wins.at(10)->getWindow(),
		posY,
		0,
		pUmap.at(pidList.at(i))->getUser().c_str());
      // PR
      outString = std::to_string(pUmap.at(pidList.at(i))->getPR());
      mvwaddstr(wins.at(9)->getWindow(),
		posY,
		wins.at(9)->getNumCols() - outString.length(),
		outString.c_str());
      // NI
      outString = std::to_string(pUmap.at(pidList.at(i))->getNI());
      mvwaddstr(wins.at(8)->getWindow(),
		posY,
		wins.at(8)->getNumCols() - outString.length(),
		outString.c_str());
      // VIRT
      outString = std::to_string(pUmap.at(pidList.at(i))->getVirt());
      mvwaddstr(wins.at(7)->getWindow(),
		posY,
		wins.at(7)->getNumCols() - outString.length(),
		outString.c_str());
      // RES
      outString = std::to_string(pUmap.at(pidList.at(i))->getRes());
      mvwaddstr(wins.at(6)->getWindow(),
		posY,
		wins.at(6)->getNumCols() - outString.length(),
		outString.c_str());
      // SHR
      outString = std::to_string(pUmap.at(pidList.at(i))->getSHR());
      mvwaddstr(wins.at(5)->getWindow(),
		posY,
		wins.at(5)->getNumCols() - outString.length(),
		outString.c_str());
      // S
      mvwaddch(wins.at(4)->getWindow(),
	       posY,
	       0,
	       pUmap.at(pidList.at(i))->getS());
      // %CPU
      outString = doubleToStr(pUmap.at(pidList.at(i))->getCPUUsage(), 1);
      mvwaddstr(wins.at(3)->getWindow(),
		posY,
		wins.at(3)->getNumCols() - outString.length(),
		outString.c_str());
      // %MEM
      outString = doubleToStr(pUmap.at(pidList.at(i))->getMemUsage(), 1);
      mvwaddstr(wins.at(2)->getWindow(),
		posY,
		wins.at(2)->getNumCols() - outString.length(),
		outString.c_str());
      // TIME+
      outString = pUmap.at(pidList.at(i))->getProcessCPUTime();
      mvwaddstr(wins.at(1)->getWindow(),
		posY,
		wins.at(1)->getNumCols() - outString.length(),
		outString.c_str());
      // COMMAND
      mvwaddstr(wins.at(0)->getWindow(),
		posY,
		0,
		pUmap.at(pidList.at(i))->getCommand().c_str());
    }
} // end of "printProcs"
