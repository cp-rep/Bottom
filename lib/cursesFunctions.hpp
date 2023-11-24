/*
  File:
   cursesFunctions.hpp

  Description:
   Function declarations for manipulating CursesWindow objects. This includes printing,
   turning on/off curses attributes, initializing, and refreshing curses windows.
*/
#ifndef CURSESFUNCTIONS_HPP
#define CURSESFUNCTIONS_HPP
#include <curses.h>
#include <queue>
#include <vector>
#include <unordered_map>
#include "byteConverter.hpp"
#include "cursesWindow.hpp"
#include "processInfo.hpp"
#include "extractFileData.hpp"
#include "_progStateConsts.hpp"
#include "_cursesWinConsts.hpp"

void initializeCurses();
void initializeStartingWindows(std::unordered_map<int, CursesWindow*>& wins);
void refreshAllWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearTopWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearProcWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearAllWins(const std::unordered_map<int, CursesWindow*>& wins);
void defineProcWinsStartVals(const std::unordered_map<int, CursesWindow*>& wins);
void defineTopWinsDataStartVals(const std::unordered_map<int, CursesWindow*>& wins);
void defineTopWinsStartVals(const std::unordered_map<int, CursesWindow*>& wins);
void defineGraphWinStartVals(const std::unordered_map<int, CursesWindow*>& wins);
void defineTopWins(const std::unordered_map<int, CursesWindow*>& wins,
		   const std::string HHMMSS,
		   const int numDays,
		   const int numHours,
		   const int numMinutes,
		   const std::vector<std::string> parsedLoadAvg,
		   const int& numUsers);
void updateHelpWindowDimensions(const std::unordered_map<int, CursesWindow*>& wins);
void updateTopWinDimensions(const std::unordered_map<int, CursesWindow*>& wins);
void updateProcWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
			     const int& shiftX,
			     const int& shiftY);
void updateGraphWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
			      const int& cpuGraphCount,
			      const int& memGraphCount);
const std::string createColorLine(const int& len);
void updateWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
			 const int& shiftX,
			 const int& shiftY,
			 const int& cpuGraphCount,
			 const int& memGraphCount);
void attrOnProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		    int attr);
void attrOffProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		     int attr);
void boldOnAllTopDataWins(std::unordered_map<int, CursesWindow*>& wins,
			  int attrs);
void boldOffAllTopDataWins(std::unordered_map<int, CursesWindow*>& wins,
			   int attrs);
void boldOnTasksDataWins(std::unordered_map<int, CursesWindow*>& wins,
			 int attrs);
void boldOffTasksDataWins(const std::unordered_map<int, CursesWindow*>& wins,
			  int attrs);
void boldOnCpusDataWins(std::unordered_map<int, CursesWindow*>& wins,
			int attrs);
void boldOffCpusDataWins(std::unordered_map<int, CursesWindow*>& wins,
			 int attrs);
void boldOnMemDataWins(std::unordered_map<int, CursesWindow*>& wins,
		       int attrs);
void boldOffMemDataWins(std::unordered_map<int, CursesWindow*>& wins,
			int attrs);
void colorOnProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		     int colorPair);
void colorOffProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		      int colorPair);
void printTasksWins(const std::unordered_map<int, CursesWindow*>& wins);
void printTasksDataWins(const std::unordered_map<int, CursesWindow*>& wins,
			const TaskInfo& taskInfo);
void printCpuWins(const std::unordered_map<int, CursesWindow*>& wins);
void printCpuDataWins(const std::unordered_map<int, CursesWindow*>& wins,
		      const CPUUsage& cpuUsage);
void printMemDataWins(const std::unordered_map<int, CursesWindow*>& wins,
		      const MemInfo& memInfo);
void printMemWins(const std::unordered_map<int, CursesWindow*>& wins);
void printSwapWins(const std::unordered_map<int, CursesWindow*>& wins);
void printTopWins(const std::unordered_map<int, CursesWindow*>& wins,
		  const std::vector<std::string>& allTopLines);
void printWindowNames(const std::unordered_map<int, CursesWindow*>& wins,
		      const int& shiftY,
		      const int& shiftX);
void printProcs(const std::unordered_map<int, CursesWindow*>& wins,
		const std::unordered_map<int, ProcessInfo*>& pUmap,
		const std::vector<int>& pidList,
		const int shiftY,
		const int shiftX,
		const int& sortState,
		const bool& highlight);
void printLine(const std::unordered_map<int, CursesWindow*>& wins,
	       const int& row,
	       const int& col,
	       const int& attrs,
	       const int& window,
	       const std::string& colorLine);
void printUserInput(const std::unordered_map<int, CursesWindow*>& wins,
		    const int winIndex,		    
		    const int& input,
		    std::string& inputString,		    
		    int& yOffset,
		    int& xOffset);
void printInputPrompt(std::unordered_map<int, CursesWindow*>& wins);
void printBadInputString(const std::unordered_map<int, CursesWindow*>& wins,
			 const int& window,
			 const int& yOffset,
			 const int& xOffset,
			 const std::string& outString);
void shiftProcWinsLeft(std::unordered_map<int, CursesWindow*>& wins,
		       const int& shiftX);
void shiftProcWinsRight(std::unordered_map<int, CursesWindow*>& wins,
			const int& shiftX);
void drawGraph(const std::unordered_map<int, CursesWindow*>& wins,
	       const int& winName,
	       std::queue<double> vals,
	       std::string graphName,
	       const int& graphScale);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins);
#endif
