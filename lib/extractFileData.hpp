/*
  File: extractFileData.hpp
  Description:
 */
#ifndef EXTRACTFILEDATA_HPP
#define EXTRACTFILEDATA_HPP
#include <string>
#include <vector>
#include <sys/stat.h>

const std::string returnPhraseLine(const std::string& fileName,
				   const std::string& phrase);
const int returnFirstIntFromLine(const std::string& line);
const std::vector<std::string> getFilePaths(const std::string& dirPath);
const std::vector<std::string> getFileNames(const std::string& dirPath);
const std::vector<std::string> getFolderPaths(const std::string& dirPath);
bool testNumericDir(const std::string& dirPath);

// string parser
std::vector<std::string> parseNewLineStrings(const std::string str);

// pipe command reader
const std::string getUptimeFromPipe();
const std::string listDirContents();
const std::vector<int> findNumericDirs(const std::string& dirPath);

#endif
