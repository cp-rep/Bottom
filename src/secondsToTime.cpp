/*
  File:
   secondsToTime.cpp

  Description:
   Class implementation for the SecondsToTime class.
      
   SecondsToTime creates objects with the ability to do conversions on time
   data such as converting hours to seconds, or minutes to seconds. It can
   also return formatted time data for output.
*/
#include "secondsToTime.hpp"



/*
  Function:
   SecondsToTime Constructor

  Description:
   Constructs SecondsToTime objects.

  Input:
   seconds              - A constant float value that should be the total
                          seconds the caller wants converted into other time
			  values.
  Output:
   NONE
*/
SecondsToTime::SecondsToTime(const float seconds)
{
  m_hours = convertToHours(seconds);
  m_minutes = convertToMinutes(seconds);
  m_seconds = findRemainingSeconds(seconds);
  m_totalSecs = seconds;
} // end of "SecondsToTime Constructor"



/*
  Function:
   convertToHours
   
  Description:
   Converts the incoming parameter of seconds to hours.
  
  Input:
   secs                - A reference to a constant integer that should be
                         the amount of seconds the caller wants converted
			 to hours.
  Output:
   const int           - The resulting calculation from seconds to
                         hours.
*/
const int SecondsToTime::convertToHours(const int& secs) const
{
  return secs/(MINUTE * MINUTE);
} // end of "convertToHours"



/*
  Function:
   convertToMinutes
  
  Description:
   Converts the incoming parameter of seconds to minutes.
  
  Input:
   secs                - A reference to a constant integer that should be
                         the amount of seconds the caller wants converted
			 to minutes.
  Output:
   const int           - The resulting calculation from seconds to
                         hours.
*/
const int SecondsToTime::convertToMinutes(const int& secs) const
{
  return (secs/MINUTE) % MINUTE;
} // end of "convertToMinutes"



/*
  Function:
   findRemainingSeconds
  
  Description:
   Calculates and returns a remainder of seconds from the total
   incoming seconds provided by the calling object.
  
  Input:
   secs                 - A reference to a constant integer that will
                          be calculated for a remainder of seconds if
			  divided by a minute.
  Output:
   const int            - The calculated remainder of seconds.
  
*/
const int SecondsToTime::findRemainingSeconds(const int& secs) const
{
  return secs % MINUTE;
} // end of "findRemainingSeconds"



/*
  Function:
   returnHHMMSS
  
  Description:
   Prepares incoming time valus for output by converting them to
   string type in HH:MM:SS formatted pattern.
  
  Input:
   hours                - A reference to a constant integer that represents
                          the total hours to be converted and formatted.

   minutes              - A reference to a constant integer that represents
                          the total minutes to be converted and formatted.

   seconds              - A reference to a constant integer that represents
                          the total seconds to be converted and formatted.
  
  Output:
   string               - A formatted string in the pattern HH:MM:SS.
  
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
   Returns the calling objects m_hours private data member.
  
  Input:
   NONE
  
  Output:
   const unsigned int&  - The calling objects m_hours private data member.
*/
const unsigned int& SecondsToTime::getHours() const
{
  return m_hours;
} // end of "getHours"



/*
  Function:
   getMinutes
  
  Description:
   Returns the calling objects m_minutes private data member.
  
  Input:
   NONE
  
  Output:
   const unsigned int&  - The calling objects m_minutes private data member.  
*/
const unsigned int& SecondsToTime::getMinutes() const
{
  return m_minutes;
} // end of "getMinutes"



/*
  Function:
   getSeconds
  
  Description:
   Returns the calling objects m_seconds private data member.
  
  Input:
   NONE
  
  Output:
   const unsigned int&  - The calling objects m_seconds private data member.    

*/
const unsigned int& SecondsToTime::getSeconds() const
{
  return m_seconds;
} // end of "getSeconds"



/*
  Function:
   setHours
  
  Description:
   Defines the calling objects m_hours private data member with the incoming
   parameter.
  
  Input:
   hours                - A reference to a constant unsigned integer that is
                          the value that will be set to the m_hours private
			  data member.
  Output:
   NONE
*/
void SecondsToTime::setHours(const unsigned int& hours)
{
  m_hours = hours;
} // end of "setHours"



/*
  Function:
   setMinutes
  
  Description:
   Defines the calling objects m_minutes private data member with the incoming
   parameter.
  
  Input:
   minutes              - A reference to a constant unsigned integer that is
                          the value that will be set to the m_minutes private
			  data member.
  Output:
   NONE
*/
void SecondsToTime::setMinutes(const unsigned int& minutes)
{
  m_minutes = minutes;
} // end of "setMinutes"



/*
  Function:
   setSeconds
  
  Description:
   Defines the calling objects m_seconds private data member with the incoming
   parameter.
  
  Input:
   seconds              - A reference to a constant unsigned integer that is
                          the value that will be set to the m_seconds private
			  data member.
  Output:
   NONE
*/
void SecondsToTime::setSeconds(const unsigned int& seconds)
{
  m_seconds = seconds;
} // end of "setSeconds"
