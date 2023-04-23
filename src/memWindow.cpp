/*
  File: memWindow.cpp
  Description:
 */
#include "memWindow.hpp"
#include <fstream>
#include <cstdlib>


/*
  Function:
  MemWindow Default Constructor
   
  Description:

  Input:
  windowName      -
  numLines        -
  numCols         -
  maxWindowY      -
  maxWindowX      -
  minWindowY      -
  minWindowX      -
  centerY         -
  centerX         -
  startY          -
  startX          -
  currentY        -
  currentX        -
  previousY       -
  previousX       -

  Output:
  NONE
*/
MemWindow::MemWindow(std::string windowName,	      
		     const short& numLines,
		     const short& numCols,
		     const short& maxWindowY,
		     const short& maxWindowX,
		     const short& minWindowY,
		     const short& minWindowX,
		     const short& centerY,
		     const short& centerX,
		     const short& startY,
		     const short& startX,
		     const short& currentY,
		     const short& currentX,
		     const short& previousY,
		     const short& previousX,
		     const std::string& MiB,
		     const std::string& swap,
		     const float memTotal,
		     const float memFree,
		     const float memUsed,
		     const float buffCache,
		     const float swapTotal,
		     const float swapFree,
		     const float swapUsed,
		     const float swapAvailable) : CursesWindow(windowName,
							     numLines,
							     numCols,
							     maxWindowY,
							     maxWindowX,
							     minWindowY,
							     minWindowX,
							     centerY,
							     centerX,
							     startY,
							     startX,
							     currentY,
							     currentX,
							     previousY,
							     previousX)
{
  m_MiB = MiB;
  m_swap = swap;
  m_memTotal = memTotal;
  m_memFree = memFree;
  m_memUsed = memUsed;
  m_buffCache = buffCache;
  m_swapTotal = swapTotal;
  m_swapFree = swapFree;
  m_swapUsed = swapUsed;
  m_swapAvailable = swapAvailable;
} // end of "MemWindow Default Constructor"




/*
  Function:
  readMiBTotal
   
  Description:

  Input:
  NONE
  
  Output:
  NONE
*/
const std::string MemWindow::returnLineWithPhrase(const std::string& phrase)
{
  std::string tempLine;
  std::string tempPhrase;
  bool found = false; 
  std::ifstream inFile("/proc/meminfo", std::ifstream::in);
  
  for(int i = 0; ; i++)
    {
      std::getline(inFile, tempLine);
      for(int j = 0; tempLine.at(i) != ':'; j++)
	{
	  tempPhrase.push_back(tempLine.at(i));
	  
	  if(tempPhrase == phrase)
	    {
	      found = true;
	      break;
	    }
	}

      if(found == true)
	{
	  break;
	}
    }
  
  inFile.close();
  
  return tempLine;
} // end of "readMiBTotal"



/*
  Function:
  parseMemoryString
   
  Description:

  Input:
  NONE
  
  Output:
  NONE
*/
const int MemWindow::parseIntFromLine(const std::string& line)
{
  std::string temp;
  
  for(int i = 0; i < line.length(); i++)
    {
      if(line.at(i) >= '0' && line.at(i) <= '9')
	{
	  temp.push_back(line.at(i));
	}	
    }

  return stoi(temp);
}  // end of "parseMemoryLine"



/*
  Function:
  defineMemData
   
  Description:

  Input:
  NONE
  
  Output:
  NONE
*/
int MemWindow::defineMemData()
{
  std::string line = returnLineWithPhrase("MemTotal");
  m_memTotal = parseIntFromLine(line);

  return m_memTotal;
} // end of "defineMemData"
