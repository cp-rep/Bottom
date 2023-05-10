/*
  File:
  secondsToTime.cpp
 */
#include "secondsToTime.hpp"



/*
  Function:
  Default Constructor
*/
SecondsToTime::SecondsToTime(const float seconds)
{
  m_hours = convertToHours(seconds);
  m_minutes = convertToMinutes(seconds);
  m_seconds = findRemainingSeconds(seconds);
  m_totalSecs = seconds;
} // end of "Default Constructor"



/*
  Function:
  convertToHours
  
  Description:
  
  Input:
  
  Output:
  
 */
const int SecondsToTime::convertToHours(const int& secs) const
{
  return secs/(MINUTE * MINUTE);
} // end of "convertToHours"



/*
  Function:
  convertToMinutes
  
  Description:
  
  Input:
  
  Output:
  
 */
const int SecondsToTime::convertToMinutes(const int& secs) const
{
  return (secs/MINUTE) % MINUTE;
} // end of "convertToMinutes"



/*
  Function:
  findRemainingSeconds
  
  Description:
  
  Input:
  
  Output:
  
 */
const int SecondsToTime::findRemainingSeconds(const int& secs) const
{
  return secs % MINUTE;
} // end of "findRemainingSeconds"



/*
  Function:
  returnHHMMSS
  
  Description:
  
  Input:
  
  Output:
  
 */
std::string SecondsToTime::returnHHMMSS(const int& hours,
					const int& minutes,
					const int& seconds) const
{
  std::string hhmmss;

  if(hours < 10)
    {
      hhmmss.append("0");
    }
  hhmmss.append(std::to_string(hours));
  hhmmss.append(":");

  if(minutes < 10)
    {
      hhmmss.append("0");
    }

  hhmmss.append(std::to_string(minutes));
  hhmmss.append(":");

  if(seconds < 10)
    {
      hhmmss.append("0");
    }
  hhmmss.append(std::to_string(seconds));

  return hhmmss;
} // end of "returnHHMMSS"



/*
  Function:
  getHours
  
  Description:
  
  Input:
  
  Output:
  
 */
const unsigned int& SecondsToTime::getHours() const
{
  return m_hours;
} // end of "getHours"
 

/*
  Function:
  getMinutes
  
  Description:
  
  Input:
  
  Output:
  
 */
const unsigned int& SecondsToTime::getMinutes() const
{
  return m_minutes;
} // end of "getMinutes"


/*
  Function:
  getSeconds
  
  Description:
  
  Input:
  
  Output:
 */
const unsigned int& SecondsToTime::getSeconds() const
{
  return m_seconds;
} // en dof "getSeconds"
  

/*
  Function:
  setHours
  Description:
  
  Input:

  Output:
 */
void SecondsToTime::setHours(const unsigned int& hours)
{
  m_hours = hours;
} // end of "setHours"



/*
  Function:
  setMinutes
  
  Description:
  
  Input:
  
  Output:
 */
void SecondsToTime::setMinutes(const unsigned int& minutes)
{
  m_minutes = minutes;
} // end of "setMinutes"



/*
  Function:
  setSeconds
  
  Description:
  
  Input:
  Output
 */
void SecondsToTime::setSeconds(const unsigned int& seconds)
{
  m_seconds = seconds;
} // end of "setSeconds"
