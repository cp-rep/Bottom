/*
  File: extractFileData.cpp
  Description:
 */
#include "extractFileData.hpp"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <unordered_map>

#define NEWLINE '\n'



/*
  Function:
  returnPhraseLine
   
  Description:
  Opens the file at the file path contained in the parameter fileName and
  proceeds to read the file line by line looking for a string containing
  the "phrase" from the parameter const std::string phrase.

  Input:
  fileName                    - a const std::string of the file path for the
                                file to open and read line by line.
  phrase		      - a const std::string for the phrase to search
                                for in each line read.
  
  Output:
  std::string                 - a const std::string containing the line which
                                the phrase was found.
*/
const std::string returnPhraseLine(const std::string& fileName,
				   const std::string& phrase)
{
  std::string tempLine;
  std::string tempPhrase;
  bool found = false; 
  std::ifstream inFile(fileName, std::ifstream::in);   

  // test if the file opened successfully
  if(!inFile.is_open())
    {
      return "-1";
    }

  // read the file line by line looking for the matching phrase
  for(int i = 0;; i++)
    {
      tempPhrase.clear();
      std::getline(inFile, tempLine);
      if(tempLine == "")
	break;
      
      for(int j = 0; tempLine.at(j) != ':'; j++)
	{
	  tempPhrase.push_back(tempLine.at(j));
	}

      if(tempPhrase == phrase)
	{
	  found = true;
	  break;
	}      	        
    }

  inFile.close();

  return tempLine;

} // end of "returnPhraseLine"



/*
  Function:
  returnFirstIntFromLine
   
  Description:
  Finds the first ASCII numeric character(s) from the line parameter,
  converts them to an int type, and then returns the value.

  Input:
  line                        - a const string that will be scanned
                                for numeric characters.
  
  Output:
  -1                          - a constant integer representing an error.

  stoi(temp)                  - a string of numeric characters converted
                                to a constant integer.
*/
const int returnFirstIntFromLine(const std::string& line)
{
  std::string temp;
  int i = 0;

  if(line.empty())
    {
      return 0;
    }
  
  // loop until we reach a numeric character
  do{
    i++;
  } while(line.at(i) < '0' || line.at(i) > '9');

  // push back until we reach a non numeric character
  while(line.at(i) >= '0' && line.at(i) <= '9')
    {
      temp.push_back(line.at(i));
      i++;
    }
    
  if(temp.empty())
    {
      return -1;
    }
  else
    {
      return stoi(temp);
    }
} // end of "returnFirstIntFromLine"



/*
  Function:
  getFileLineByNumber
   
  Description:
  Returns a specified line from a file.

  Input:
  filePath               - a const reference to a string for a full file path.

  lineNumber             - a zero based a const reference to an int for a
                           specificline number we want to return.
			   
  Output:
  const string           - a const string containing the desired line we are
                           returning based upon the incoming line number.
*/
const std::string getFileLineByNumber(const std::string& filePath,
				      const int& lineNumber)
{
  struct stat file;  
  std::string tempLine;
  std::ifstream inFile(filePath, std::ifstream::in);   
  
  if(stat(filePath.c_str(), &file) == 0 && S_ISREG(file.st_mode))
    {
      for(int i = 0; i <= lineNumber; i++)
	{
	  std::getline(inFile, tempLine, '\n');
	}

      return tempLine;
    }
  else
    {
      return "-1";
    }    
} // end of "getFileLineNumber"


/*
  Function:
  returnValByWhitespaceCount

  Description:
  Traverses a whitespace delimited string and retruns a preceding numeric
  value based upon how many whitespaces have been counted.

  Input:
  line                   - a const string reference containing a comma
                           delimited string.

  numWhiteSpaces         - a const int reference representing the number 
                           of whitespaces to skip before reading a value;

  Output:
  const int              - a const int containing a value read from the
                           parameter line.
 */
const int returnValByWhiteSpaceCount(const std::string& line,
				     const int& numWhiteSpaces)
{
  std::string valString;
  int i = 0;
  int spaceCount = 0;
  for(; i < line.length() && spaceCount != numWhiteSpaces; i++)
    {
      if(line.at(i) == ' ')
	{
	  spaceCount++;
	}
    }

  do{
      valString.push_back(line.at(i));
      i++;
    } while(line.at(i) != ' ');

  return stoi(valString);
} // end of "returnValByWhiteSpace"



/*
  Function:

  Description:

  Input:

  Output:

 */
const std::string returnStringByWhiteSpaceCount(const std::string& line,
						 const int& numWhiteSpaces)
{
  std::string valString;
  int i = 0;
  int spaceCount = 0;
  
  for(; i < line.length() && spaceCount != numWhiteSpaces; i++)
    {
      if(line.at(i) == ' ')
	{
	  spaceCount++;
	}
    }

  do{
      valString.push_back(line.at(i));
      i++;
    } while(line.at(i) != ' ');

  return valString;
} // end of "returnValByWhiteSpace"



/*
  Function:
  getFilesPaths

  Description:
  Returns a vector of found existing file paths based on the path given
  from the parameter dirPath.
 */
const std::vector<std::string> getFilePaths(const std::string& dirPath)
{
  std::vector<std::string> dirNames;
  return dirNames;
} // end of "getFileNames"



/*
  Function:
  getFileNames
   
  Description:
  Searches the file path given from the parameter dirPath for files.
  If the path exists and files are found, the file names are stored in
  vector<string> type and returned to the caller.
  
  Input:
  dirPath                - a const string reference representing a file
                           path to a directory.
  
  Output:
  NONE
*/
const std::vector<std::string> getFileNames(const std::string& dirPath)
{
  std::vector<std::string> dirNames;
  return dirNames;
} // end of "getFileNames"



/*
  Function:
  getFolderPaths
   
  Description:
  Searches the file path given from the parameter dirPath for files.
  If the path exists and directories represented by only numeric
  characters are found, their file names are converted to integers
  and returned as a vector<int> type to the caller.

  
  Input:
  dirPath                - a const string reference representing a file
                           path to a directory.  
  Output:
  NONE
*/
const std::string getFolderPaths(const std::string& dirPath)
{
  struct stat dir;

  if(stat(dirPath.c_str(), &dir) == 0 && S_ISDIR(dir.st_mode))
    {
      return "Yes";
    }
  else
    {
      return "No";
    }
} // end of "getNumberedFolders"



/*
  Function:
  testNumericDir

  Description:
 */
bool testNumericDir(const std::string& dirPath)
{
  struct stat dir;
  bool isNumericDir = false;
 
 if(stat(dirPath.c_str(), &dir) == 0 && S_ISDIR(dir.st_mode))
    {
      return true;
    }
  else
    {
      return false;
    }
} // end of "getNumberedFolders"



/*
  Function:
  parseNewLineStrings

  Description:
 */
std::vector<std::string> parseLine(const std::string str)
{
  std::vector<std::string> parsedString;
  std::string temp;
  bool whitespace = false;
  
  for(int i = 0; i < str.length(); i++)
    {
      while(str.at(i) == ' ' && i < str.length())
	{
	  if(!temp.empty())
	    {
	      parsedString.push_back(temp);
	      temp.clear();
	    }
	  i++;
	}
      temp.push_back(str.at(i));
    }

  if(!temp.empty())
    {
      parsedString.push_back(temp);
    }

  return parsedString;
} // end of "parseNewLineStrings"



/*
  Function:
  findMemInfoFromPipe
  
  Description:
  
  Input:
  
  Output:

 */
const std::string returnLineFromPipe(const std::string& comm,
				     const char* mode,
				     const int& lineNum)
{
  FILE* pipe;
  std::string line;;
  char c = 0;

  pipe = popen(comm.c_str(), mode);

  if(pipe == nullptr)
    {
      perror("popen() failed to open users program.");
      exit(EXIT_FAILURE);
    }

  for(int i = 0; i < lineNum - 1; i++)
    {
      while(fread(&c, sizeof c, 1, pipe))
	{
	  if(c == '\n')
	    break;
	}
    }

  while(fread(&c, sizeof c, 1, pipe))
    {
      if(c == '\n')
	{
	  break;
	}
      else
	{
	  line.push_back(c);
	}
    }

  pclose(pipe);

  return line;
} // end of "findMemInfoFromPipe"



/*
  Function:
  listDirContents

  Description:
 */
const std::string listDirContents()
{
  FILE* listFile;
  std::string dirContents;
  char c = 0;

  listFile = popen("ls", "r");

  if(listFile == nullptr)
    {
      perror("popen() failed to open ls program.");
      exit(EXIT_FAILURE);
    }

  while(fread(&c, sizeof c, 1, listFile))
    {
      dirContents.push_back(c);
    }

  pclose(listFile);

  return dirContents;
} // end of "listDirContents"



/*
  Function:
  findNumericDirs

  Description:
 */
const std::vector<int> findNumericDirs(const std::string& dirPath)
{
  FILE* pipe;
  std::string command = "ls ";
  std::vector<int> dirs;
  std::string fullPath;
  std::string numFolder;
  std::unordered_map<int, int> pids;
  char c = 0;

  command.append(dirPath);
  pipe = popen(command.c_str(), "r");

  if(pipe == nullptr)
    {
      perror("popen() failed to open ls program.");
      exit(EXIT_FAILURE);
    }

  while(fread(&c, sizeof c, 1, pipe))
    {
      if(c >= '0' && c <= '9')
	{
	  numFolder.push_back(c);
	}
      else if(c == '\n')
	{
	  fullPath.clear();
	  fullPath.append(dirPath);
	  fullPath.append(numFolder);

	  if(true == testNumericDir(fullPath))
	    {
	      int val;
	      std::stringstream container(numFolder);
	      container >> val;

	      if(pids[val] == 0)
		{
		  dirs.push_back(val);
		  pids[val]++;
		}
	    }
	  numFolder.clear();
	}
    }

  pclose(pipe);
  
  return dirs;
} // end of "findNumericDirs"



/*
  
 */
bool phraseExists(const std::string& line, const std::string& phrase)
{
  std::string temp;
  bool phraseExists = false;

  for(int i = 0; i < line.length(); i++)
    {
      if(line.at(i) == phrase.at(0))
	{
	  for(int j = 0; j < phrase.length() && i + j < line.length(); j++)
	    {
	      if(line.at(i + j) == phrase.at(j))
		{
		  temp.push_back(phrase.at(j));
		}
	    }
	}

      if(temp == phrase)
	{
	  phraseExists = true;
	  break;
	}
      else
	{
	  temp.clear();
	}
    }

  return phraseExists;
}
