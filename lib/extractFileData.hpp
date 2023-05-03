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
const std::string getFileLineByNumber(const std::string& dirPath,
				      const int& lineNumber);

const std::vector<std::string> getFilePaths(const std::string& dirPath);
const std::vector<std::string> getFileNames(const std::string& dirPath);
const std::string getFolderPaths(const std::string& dirPath);
bool testNumericDir(const std::string& dirPath);


// parse from strings
std::vector<std::string> parseNewLineStrings(const std::string str);
const int returnValByWhiteSpaceCount(const std::string& line,
				     const int& numWhiteSpaces);
const std::string returnStringByWhiteSpaceCount(const std::string& line,
						 const int& numWhiteSpaces);
bool phraseExists(const std::string& line, const std::string& phrase);

// read from popen outputs
const std::string findUptimeFromPipe();
const std::string findMemInfoFromPipe();
const std::string listDirContents();
const std::vector<int> findNumericDirs(const std::string& dirPath);



#endif
