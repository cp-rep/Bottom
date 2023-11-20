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
void resetToWinStartState(std::unordered_map<int, CursesWindow*>& wins);
void initializeStartingWindows(std::unordered_map<int, CursesWindow*>& wins);
void defineTopWins(std::unordered_map<int, CursesWindow*>& wins,
		   const std::string HHMMSS,
		   const int numDays,
		   const int numHours,
		   const int numMinutes,
		   const std::vector<std::string> parsedLoadAvg,
		   const int& numUsers);
void defineProcWinsStartVals(std::unordered_map<int, CursesWindow*>& wins);
void defineTopWinsStartVals(std::unordered_map<int, CursesWindow*>& wins);
void defineTopWinsDataStartVals(std::unordered_map<int, CursesWindow*>& wins);
void defineGraphWinStartVals(std::unordered_map<int, CursesWindow*>& wins);
void updateTopWinDimensions(std::unordered_map<int, CursesWindow*>& wins);
void updateProcWinDimensions(std::unordered_map<int, CursesWindow*>& wins,
			     const int& shiftX,
			     const int& shiftY);
void updateGraphWinDimensions(std::unordered_map<int, CursesWindow*>& wins,
			      const int& cpuGraphCount,
			      const int& memGraphCount);
void updateWinDimensions(std::unordered_map<int, CursesWindow*>& wins,
			 const int& shiftX,
			 const int& shiftY,
			 const int& cpuGraphCount,
			 const int& memGraphCount);
void updateHelpWindowDimensions(std::unordered_map<int, CursesWindow*>& wins);
void initializeProgramStates(std::unordered_map<char, int>& progStates);
void refreshAllWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearAllWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearTopWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearProcWins(const std::unordered_map<int, CursesWindow*>& wins);
void colorOnProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		     int colorPair);
void colorOffProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		      int colorPair);
void attrOnProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		    int attr);
void attrOffProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		     int attr);
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
void boldOnAllTopDataWins(std::unordered_map<int, CursesWindow*>& wins,
			  int attrs);
void boldOffAllTopDataWins(std::unordered_map<int, CursesWindow*>& wins,
			   int attrs);
void boldOnCpusDataWins(std::unordered_map<int, CursesWindow*>& wins,
			int attrs);
void boldOnTasksDataWins(std::unordered_map<int, CursesWindow*>& wins,
			 int attrs);
void boldOffTasksDataWins(const std::unordered_map<int, CursesWindow*>& wins,
			  int attrs);
void boldOffCpusDataWins(std::unordered_map<int, CursesWindow*>& wins,
			 int attrs);
void boldOnMemDataWins(std::unordered_map<int, CursesWindow*>& wins,
		       int attrs);
void boldOffMemDataWins(std::unordered_map<int, CursesWindow*>& wins,
			int attrs);
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
const std::string createColorLine(const int& len);
void printLine(const std::unordered_map<int, CursesWindow*>& wins,
	       const int& row,
	       const int& col,
	       const int& attrs,
	       const int& window,
	       const std::string& colorLine);
void shiftProcWinsLeft(std::unordered_map<int, CursesWindow*>& wins,
		       const int& shiftX);
void shiftProcWinsRight(std::unordered_map<int, CursesWindow*>& wins,
			const int& shiftX);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins);
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
void drawGraph(const std::unordered_map<int, CursesWindow*>& wins,
	       const int& winName,
	       std::queue<double> vals,
	       std::string graphName,
	       const int& graphScale);	       
#endif
