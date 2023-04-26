/*
  File: uptimeReader.hpp
  Description:
 */
#include "uptimeReader.hpp"
#include <fstream>



/*
  Function:
  getUptimeFromPipe

  Description:

  Input:
  NONE
  Output:
  NONE
 */
const std::string getUptimeFromPipe()
{
  FILE* usersFile;
  std::string uptime;
  char c = 0;

  usersFile = popen("uptime", "r");

  if(usersFile == nullptr)
    {
      perror("popen() failed to open users program.");
      exit(EXIT_FAILURE);
    }

  while(fread(&c, sizeof c, 1, usersFile))
    {
      uptime.push_back(c);
    }

  pclose(usersFile);

  return uptime;

} // end of "getUptime"
