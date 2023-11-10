/*
 File:
  log.hpp

 Description:
  This class is good to use for creating a numbered file system such as a
  simple logging system.

*/
#ifndef LOG_HPP
#define LOG_HPP
#include <string>



class Log{
public:
  // constructors 
  explicit Log(const std::string& pName = "",
	       const std::string& fName = "",
	       const unsigned int fNum = 0,
	       const std::string& fType = "");
 
  // destructor
  ~Log(){};
  
  // member functions
  void incrementFileName();
    
  // getters and setters
  const std::string& getPathName() const noexcept;
  const std::string& getFileName() const noexcept;
  const unsigned int& getFileNumber() const noexcept;
  const std::string& getFileType() const noexcept;
  const std::string& getFullPath() const noexcept;
  void setPathName(const std::string& pName) noexcept;
  void setFileName(const std::string& fName) noexcept;
  void setFileNumber(const unsigned int& fNum) noexcept;
  void setFileType(const std::string& fType) noexcept;
  void setFullPath(const std::string& pName,
		   const std::string& fName,
		   const std::string& fNum,
		   const std::string& fType);
  
private:
  // member variables
  std::string m_pathName; // full path to a file
  std::string m_fileName; // desired filename
  unsigned int m_fileNum; // file number to be appended to filename
  std::string m_fileType; // file extension to be appended to file name
  std::string m_fullPath; // full path including file name, number, and exension
};

#endif
