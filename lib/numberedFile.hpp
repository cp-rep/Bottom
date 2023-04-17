// ============================================================================
// File: numberedFile.hpp
//
// Description:
//   A simple class that constructs an object with the goal of creating a file
//   name. The file name is constructed with a number appended to it. The class
//   provides a member function that can increment that file number.
//
//   This class is good to use for creating a numbered file system such as a
//   simple logging system.
//
// Notes:
//   - May be worth turning this into an extensible class that uses a
//     std::vector<std::string> structure to store all file name components
//     in the future.  It's use cases could expand.
// ============================================================================
#ifndef NUMBEREDFILE_HPP
#define NUMBEREDFILE_HPP
#include <string>



class NumberedFile{
public:
  // constructors 
  explicit NumberedFile(const std::string& pName = "",
			const std::string& fName = "",
			const unsigned int fNum = 0,
			const std::string& fType = "");

  // destructor
  ~NumberedFile(){};
  
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
  std::string m_fileType; // ile extension to be appended to file name
  std::string m_fullPath; // full path including file name, number, and exension
};

#endif
