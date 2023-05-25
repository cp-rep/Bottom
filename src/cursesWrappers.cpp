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
void attronBottomWins(const std::vector<CursesWindow*>& wins, int attrs)
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
void attroffBottomWins(const std::vector<CursesWindow*>& wins, int attrs)
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
void printWindowNames(const std::vector<CursesWindow*>& wins)
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
			     const std::vector<CursesWindow*>& wins)
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
		const std::vector<CursesWindow*>& wins)
{
  std::string outString;
  
  for(int i = 0; i < pUmap.size(); i++)
    {
      int posY = i + shiftY;

      // PID
      if(shiftX <= _PIDWIN)
	{
	  outString = std::to_string(pUmap.at(pidList.at(i))->getPID());
	  mvwaddstr(wins.at(_PIDWIN)->getWindow(),
		    posY,
		    wins.at(_PIDWIN)->getNumCols() - outString.length(),
		    outString.c_str());
	}
      // USER      
      if(shiftX <= _USERWIN)
      	{

	  mvwaddstr(wins.at(_USERWIN)->getWindow(),
		    posY,
		    0,
		    pUmap.at(pidList.at(i))->getUSER().c_str());
	}
      
      // PR
      if(shiftX <= _PRWIN)
	{
	  outString = std::to_string(pUmap.at(pidList.at(i))->getPR());
	  mvwaddstr(wins.at(_PRWIN)->getWindow(),
		    posY,
		    wins.at(_PRWIN)->getNumCols() - outString.length(),
		    outString.c_str());
	}
      // NI
      if(shiftX <= _NIWIN)
	{
	  outString = std::to_string(pUmap.at(pidList.at(i))->getNI());
	  mvwaddstr(wins.at(_NIWIN)->getWindow(),
		    posY,
		    wins.at(_NIWIN)->getNumCols() - outString.length(),
		    outString.c_str());
	}
      // VIRT
      if(shiftX <= _VIRTWIN)
	{
      outString = std::to_string(pUmap.at(pidList.at(i))->getVIRT());
      mvwaddstr(wins.at(_VIRTWIN)->getWindow(),
		posY,
		wins.at(_VIRTWIN)->getNumCols() - outString.length(),
		outString.c_str());
	}
      // RES
      if(shiftX <= _RESWIN)
	{
      outString = std::to_string(pUmap.at(pidList.at(i))->getRES());
      mvwaddstr(wins.at(_RESWIN)->getWindow(),
		posY,
		wins.at(_RESWIN)->getNumCols() - outString.length(),
		outString.c_str());
	}
      // SHR
      if(shiftX <= _SHRWIN)
	{
      outString = std::to_string(pUmap.at(pidList.at(i))->getSHR());
      mvwaddstr(wins.at(_SHRWIN)->getWindow(),
		posY,
		wins.at(_SHRWIN)->getNumCols() - outString.length(),
		outString.c_str());
	}
      // S
      if(shiftX <= _SWIN){
      mvwaddch(wins.at(_SWIN)->getWindow(),
	       posY,
	       0,
	       pUmap.at(pidList.at(i))->getS());
      }
      // %CPU
      if(shiftX <= _PROCCPUWIN)
	{
      outString = doubleToStr(pUmap.at(pidList.at(i))->getCPUUsage(), 1);
      mvwaddstr(wins.at(_PROCCPUWIN)->getWindow(),
		posY,
		wins.at(_PROCCPUWIN)->getNumCols() - outString.length(),
		outString.c_str());
	}
      // %MEM
      if(shiftX <= _PROCMEMWIN)
	{
      outString = doubleToStr(pUmap.at(pidList.at(i))->getMEMUsage(), 1);
      mvwaddstr(wins.at(_PROCMEMWIN)->getWindow(),
		posY,
		wins.at(_PROCMEMWIN)->getNumCols() - outString.length(),
		outString.c_str());
	}
      // TIME+
      if(shiftX <= _PROCTIMEWIN)
	{
	  outString = pUmap.at(pidList.at(i))->getProcessCPUTime();
	  mvwaddstr(wins.at(_PROCTIMEWIN)->getWindow(),
		    posY,
		    wins.at(_PROCTIMEWIN)->getNumCols() - outString.length(),
		    outString.c_str());
	}
      // COMMAND
      if(shiftX <= _COMMANDWIN)
	{
	  outString = pUmap.at(pidList.at(i))->getCOMMAND();
	  mvwaddstr(wins.at(_COMMANDWIN)->getWindow(),
		    posY,
		    0,
		    outString.c_str());
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

