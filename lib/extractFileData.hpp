/*
  File: extractFileData.hpp
  Description:
 */
#ifndef EXTRACTFILEDATA_HPP
#define EXTRACTFILEDATA_HPP
#include <string>

class ExtractFileData{
public:
  const std::string returnPhraseLine(const std::string& fileName,
				     const std::string& phrase);
  const int returnFirstIntFromLine(const std::string& line);
private:
};

#endif
