/*
  File: extractFileData.hpp
  Description:
 */
#ifndef EXTRACTFILEDATA_HPP
#define EXTRACTFILEDATA_HPP
#include <string>
#include <vector>
#include <sys/stat.h>

// read from files
const std::string returnPhraseLine(const std::string& fileName,
				   const std::string& phrase);
const int returnFirstIntFromLine(const std::string& line);
const std::string returnFileLineByNumber(const std::string& dirPath,
					 const int& lineNumber);

const std::vector<std::string> getFilePaths(const std::string& dirPath);
const std::vector<std::string> getFileNames(const std::string& dirPath);
const std::string getFolderPaths(const std::string& dirPath);
bool testNumericDir(const std::string& dirPath);
const std::string returnFileLineByPhrase(const std::string& filePath,
					 const std::string& phrase);


// parse from strings
std::vector<std::string> parseLine(const std::string& str);
const int returnValByWhiteSpaceCount(const std::string& line,
				     const int& numWhiteSpaces);
const std::string returnStringByWhiteSpaceCount(const std::string& line,
						 const int& numWhiteSpaces);
bool phraseExists(const std::string& line, const std::string& phrase);
const int convertToInt(const std::string& str);

// read from popen outputs
const std::string returnLineFromPipe(const std::string& comm,
				     const char* mode,
				     const int& lineNum);
const std::string listDirContents();
const std::vector<int> findNumericDirs(const std::string& dirPath);

// create strings
const std::string catParams();
const std::string fixStatLine(const std::string& line);

#endif
