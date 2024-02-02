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
#include "dynData.hpp"
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
void updateHelpWindowDimensions(const std::unordered_map<int, CursesWindow*>& wins);
void updateTopWinDimensions(const std::unordered_map<int, CursesWindow*>& wins);
void updateProcWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
			     const int& shiftY,
			     const int& shiftX);
void updateGraphWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
			      const int& cpuGraphCount,
			      const int& memGraphCount);
const std::string createColorLine(const int& len);
void updateWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
			 const int& shiftY,
			 const int& shiftX,
			 const int& cpuGraphCount,
			 const int& memGraphCount);
void attronProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		    const int attr);
void attroffProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		     const int attr);
void attronTopDataWins(std::unordered_map<int, CursesWindow*>& wins,
		       const int attrs);
void attroffTopDataWins(std::unordered_map<int, CursesWindow*>& wins,
			const int attrs);
void attronTasksDataWins(std::unordered_map<int, CursesWindow*>& wins,
			 const int attrs);
void attroffTasksDataWins(const std::unordered_map<int, CursesWindow*>& wins,
			  const int attrs);
void attronCpusDataWins(std::unordered_map<int, CursesWindow*>& wins,
			const int attrs);
void attroffCpusDataWins(std::unordered_map<int, CursesWindow*>& wins,
			 const int attrs);
void attronMemDataWins(std::unordered_map<int, CursesWindow*>& wins,
		       const int attrs);
void attroffMemDataWins(std::unordered_map<int, CursesWindow*>& wins,
			const int attrs);
void colorOnProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		     const int colorPair);
void colorOffProcWins(const std::unordered_map<int, CursesWindow*>& wins,
		      const int colorPair);
void printTopWins(const std::unordered_map<int, CursesWindow*>& wins,
		  const struct DynamicTopWinData& dynTWData,
		  std::vector<std::string> parsedLoadAvg,
		  std::string timeString);
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
void shiftProcWinsLeft(const std::unordered_map<int, CursesWindow*>& wins,
		       const int& shiftX);
void shiftProcWinsRight(const std::unordered_map<int, CursesWindow*>& wins,
			const int& shiftX);
void drawGraph(const std::unordered_map<int, CursesWindow*>& wins,
	       const int& winName,
	       std::queue<double> vals,
	       const std::string& graphName,
	       const int& graphScale);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins);
#endif
