// ============================================================================
// File: numberedFile.cpp
//
// Description:
//   The numberedFile.hpp class implementation.
// ============================================================================
#include "numberedFile.hpp"
#include <iostream>



// ==== NumberedFile::Constructor =============================================
// Description:
//   Constructs the NumberedFile object.  The incoming parameters are
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
//   m_fullPath - A string containing the full path to the file to be creaated
//                including the file Name.
// ============================================================================
NumberedFile::NumberedFile(const std::string& pName,
			   const std::string& fName,				   
			   const unsigned int fNum,
			   const std::string& fType)
{
  // initialize member variables
  m_pathName = pName;
  m_fileName = fName;
  m_fileNum = fNum;
  m_fileType = fType;

  std::string tempNum(std::to_string(fNum));
  
  setFullPath(pName, fName, tempNum, fType);
} // end of "NumberedFile::Constructor"



// ==== NumberedFile::incrementFileName =======================================
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
void NumberedFile::incrementFileName()
{
  if(m_fileName == "" && m_fileNum == 0)
    {
      m_fileNum++;
    }
  else
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
    }
  
  setFullPath(m_pathName, m_fileName, std::to_string(m_fileNum), m_fileType);
} // end of "NumberedFile::incrementFileName"



// ==== NumberedFile::getPathName =============================================
//
// ============================================================================
const std::string& NumberedFile::getPathName() const noexcept
{
  return m_pathName;
} // end of "NumberedFile::getPathName"



// ==== NumberedFile::getFileName =============================================
//
// ============================================================================
const std::string& NumberedFile::getFileName() const noexcept
{
  return m_fileName;
} // end of "NumberedFile::getFileName"



// ==== NumberedFile::getFileNumber ===========================================
//
// ============================================================================
const unsigned int& NumberedFile::getFileNumber() const noexcept
{
  return m_fileNum;
} // end of "NumberedFile::getFileNumber"



// ==== NumberedFile::getFileType =============================================
//
// ============================================================================
const std::string& NumberedFile::getFileType() const noexcept
{
  return m_fileType;
} // end of "NumberedFile::getFileType"



// ==== NumberedFile::getFullPath =============================================
//
// ============================================================================
const std::string& NumberedFile::getFullPath() const noexcept
{
  return m_fullPath;
} // end of "NumberedFile::getFullPath"



// ==== NumberedFile::setPathName =============================================
//
// ============================================================================
void NumberedFile::setPathName(const std::string& pName) noexcept
{
  m_pathName = pName;
} // end of "NumberedFile::setPathName"



// ==== NumberedFile::setFileName =============================================
//
// ============================================================================
void NumberedFile::setFileName(const std::string& fName) noexcept
{
  m_fileName = fName;
} // end of "NumberedFile::setFileName"



// ==== NumberedFile::setFileNumber ===========================================
//
// ============================================================================
void NumberedFile::setFileNumber(const unsigned int& fNum) noexcept
{
  m_fileNum = fNum;
} // end of "NumberedFile::setFileNumber"



// ==== NumberedFile::setFileType =============================================
//
// ============================================================================
void NumberedFile::setFileType(const std::string& fType) noexcept
{
  m_fileType = fType;
} // end of "NumberedFile::setFileType"




// ==== NumberedFile::setFullPath =============================================
// Description:
//   Stores the full path to a file including the file name and extension to a
//   string to the m_fullPath member variable.
// ============================================================================
void NumberedFile::setFullPath(const std::string& pName,
			       const std::string& fName,
			       const std::string& fNum,
			       const std::string& fType)
{
  std::string tempName(pName);
  tempName += fName;
  tempName += fNum;
  tempName += fType;
  m_fullPath = tempName;  
} // end of "NumberedFile::setFullPath
