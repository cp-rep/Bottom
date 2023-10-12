// ============================================================================
// File: log.cpp
//
// Description:
//   The log.hpp class implementation.
// ============================================================================
#include "log.hpp"
#include <iostream>



// ==== Log::Constructor ======================================================
// Description:
//   Constructs the Log object.  The incoming parameters are
//   concatenated into a string that can be used as a pathname to a file.
//
// Input:
//   pName - The path name to the directory a file is to be created in.
//   fName - The name of the file to create.
//   fNum  - The number of the file being created. (i.e. 0,..,N)
//   fType - The file extension. (e.g. ".txt")
//
// Output:
//   m_pName - The path name to the directory a file is to be created in.
//   m_fName - The name of the file to create.
//   m_fNum  - The number of the file being created. (i.e. 0,..,N)
//   m_fType - The file extension. (e.g. ".txt")
//   m_fullPath - A string containing the full path to the file to be created
//                including the file Name.
// ============================================================================
Log::Log(const std::string& pName,
	 const std::string& fName,
	 const unsigned int fNum,
	 const std::string& fType)
{
  std::string tempNum = "0";
  
  // initialize member variables
  m_pathName = pName;
  m_fileName = fName;
  m_fileNum = fNum;
  m_fileType = fType;
  tempNum += std::to_string(fNum);
  setFullPath(pName, fName, tempNum, fType);
} // end of "Log::Constructor"



// ==== Log::incrementFileName ================================================
// Description:
//   Takes the current file name and parses out the file number, converts it
//   to an int, and then increments it by 1. A new string is then created
//   with the desired file name prefix, then the incremented file number
//   appended to it.  The new file name is then appended to the full path
//   member variable.
//
// Input:
//   None
//
// Output:
//   m_fileNum - The file number incremented by 1.
//   m_fullPath - The full path with the new file name and new file number
//                appended.
// ============================================================================
void Log::incrementFileName()
{
  std::string tempNumeric = "";
  
  int i;
  // get the file number from the full path
  for(i = 0; i < m_fullPath.length(); i++)
    {
      if(m_fullPath.at(i) >= '0' && m_fullPath.at(i) <= '9')
	{
	  tempNumeric += m_fullPath.at(i);

	  // if there is a file type, this allows us to end the loop early
	  // instead of checking it for numeric characters
	  if(m_fileType != "")
	    {
	      if(m_fullPath.at(i + 1) == 0 ||
		 (m_fullPath.at(i) < '0' || m_fullPath.at(i) > '9'))
		{
		  break;
		}
	    }
	}
    }
      
  m_fileNum = stoi(tempNumeric);
  m_fileNum++;
  std::string tempStr;
  
  if(m_fileNum < 10)
    {
      tempStr.append("0");
    }

  tempStr.append(std::to_string(m_fileNum));
  
  setFullPath(m_pathName, m_fileName, tempStr, m_fileType);
  //  setFullPath(m_pathName, m_fileName, std::to_string(m_fileNum), m_fileType);  
} // end of "Log::incrementFileName"



// ==== Log::getPathName ======================================================
//
// ============================================================================
const std::string& Log::getPathName() const noexcept
{
  return m_pathName;
} // end of "Log::getPathName"



// ==== Log::getFileName ======================================================
//
// ============================================================================
const std::string& Log::getFileName() const noexcept
{
  return m_fileName;
} // end of "Log::getFileName"



// ==== Log::getFileNumber ====================================================
//
// ============================================================================
const unsigned int& Log::getFileNumber() const noexcept
{
  return m_fileNum;
} // end of "Log::getFileNumber"



// ==== Log::getFileType ======================================================
//
// ============================================================================
const std::string& Log::getFileType() const noexcept
{
  return m_fileType;
} // end of "Log::getFileType"



// ==== Log::getFullPath ======================================================
//
// ============================================================================
const std::string& Log::getFullPath() const noexcept
{
  return m_fullPath;
} // end of "Log::getFullPath"



// ==== Log::setPathName ======================================================
//
// ============================================================================
void Log::setPathName(const std::string& pName) noexcept
{
  m_pathName = pName;
} // end of "Log::setPathName"



// ==== Log::setFileName ======================================================
//
// ============================================================================
void Log::setFileName(const std::string& fName) noexcept
{
  m_fileName = fName;
} // end of "Log::setFileName"



// ==== Log::setFileNumber ====================================================
//
// ============================================================================
void Log::setFileNumber(const unsigned int& fNum) noexcept
{
  m_fileNum = fNum;
} // end of "Log::setFileNumber"



// ==== Log::setFileType ======================================================
//
// ============================================================================
void Log::setFileType(const std::string& fType) noexcept
{
  m_fileType = fType;
} // end of "Log::setFileType"




// ==== Log::setFullPath ======================================================
// Description:
//   Stores the full path to a file including the file name and extension to a
//   string to the m_fullPath member variable.
// ============================================================================
void Log::setFullPath(const std::string& pName,
		      const std::string& fName,
		      const std::string& fNum,
		      const std::string& fType)
{
  std::string tempName(pName);
  tempName += fName;
  tempName += fNum;
  tempName += fType;
  m_fullPath = tempName;  
} // end of "Log::setFullPath
