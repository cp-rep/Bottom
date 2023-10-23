/*
  File:
   cursesFunctions.hpp

  Description:
   A collection of function declarations for manipulating CursesWindow objects.
   This includes creating, deleting, moving, and sorting the WINDOWs or their
   data.  Some functions for making necessary related calculations are
   also included.
*/
#ifndef CURSESFUNCTIONS_HPP
#define CURSESFUNCTIONS_HPP
#include <curses.h>
#include <vector>
#include <unordered_map>
#include "cursesColors.hpp"
#include "cursesWindow.hpp"
#include "mainWindow.hpp"
#include "topWindow.hpp"
#include "percentMEMWindow.hpp"
#include "COMMANDWindow.hpp"
#include "PIDWindow.hpp"
#include "SWindow.hpp"
#include "cpuWindow.hpp"
#include "tasksWindow.hpp"
#include "PRWindow.hpp"
#include "tasksRunningWindow.hpp"
#include "tasksSleepingWindow.hpp"
#include "tasksStoppedWindow.hpp"
#include "tasksTotalWindow.hpp"
#include "tasksZombieWindow.hpp"
#include "TIMEWindow.hpp"
#include "memWindow.hpp"
#include "RESWindow.hpp"
#include "NIWindow.hpp"
#include "USERWindow.hpp"
#include "cursesWindow.hpp"
#include "percentCPUWindow.hpp"
#include "SHRWindow.hpp"
#include "VIRTWindow.hpp"
#include "processInfo.hpp"
#include "extractFileData.hpp"
#include "_progStateConsts.hpp"
#include "_cursesWinConsts.hpp"
#include <mutex>

void initializeCurses();
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
		       TasksZombieWindow& tasksZombieWin);
void initializeProgramStates(std::unordered_map<char, int>& progStates);
void refreshAllWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearAllWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearTopWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearBottomWins(const std::unordered_map<int, CursesWindow*>& wins);
void boldOnTasksWins(std::unordered_map<int, CursesWindow*>& wins,
		     int attrs);
void boldOffTasksWins(const std::unordered_map<int, CursesWindow*>& wins,
		      int attrs);
void attronBottomWins(const std::unordered_map<int, CursesWindow*>& wins,
		      int attrs);
void attroffBottomWins(const std::unordered_map<int, CursesWindow*>& wins,
		       int attrs);
void printTasksData(const std::unordered_map<int, CursesWindow*>& wins,
		    const TaskInfo& taskInfo);
void printTopWins(const std::unordered_map<int, CursesWindow*>& wins,
		  const std::vector<std::string>& allTopLines);
void printWindowNames(const std::unordered_map<int, CursesWindow*>& wins);
void printSortedProcs(const std::vector<int>& pidList,
		      const std::vector<std::pair<double, int>>& sortedOut,
		      const std::unordered_map<int, ProcessInfo*>& pUmap,
		      const std::unordered_map<int, CursesWindow*>& wins);
void printSortedProcsReverse(const int& startLine,
			     const std::vector<std::pair<double, int>>& sortedOut,
			     const std::unordered_map<int, ProcessInfo*>& pUmap,
			     const std::unordered_map<int, CursesWindow*>& wins);
const std::string createColorLine(const int& len);
void printProcs(const std::unordered_map<int, CursesWindow*>& wins,
		const std::unordered_map<int, ProcessInfo*>& pUmap,
		const std::vector<int>& pidList,
		const int shiftY,
		const int shiftX);
void printColorLine(const std::unordered_map<int, CursesWindow*>& wins,
		    const int& row,
		    const int& attrs,
		    const int& window,
		    const std::string& colorLine);
void shiftBottomWinsLeft(std::unordered_map<int, CursesWindow*>& wins,
			 const int& shiftX);
void shiftBottomWinsRight(std::unordered_map<int, CursesWindow*>& wins,
			  const int& shiftX);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins);

#endif
