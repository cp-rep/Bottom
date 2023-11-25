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

  Input/Output:
   NONE
   
  Input:
   seconds              - A constant float value that should be the total
                          seconds the caller wants converted unsigned into other time
			  values.
  Output:
   NONE

  Returns:
   NONE
*/
SecondsToTime::SecondsToTime(const float& seconds)
{
  setHours(convertToHours(seconds));
  setMinutes(convertToMinutes(seconds));
  setSeconds(findRemainingSeconds(seconds));
  setTotalSeconds(seconds);
} // end of "SecondsToTime Constructor"



/*
  Function:
   convertToHours
   
  Description:
   Converts the incoming parameter of seconds to hours.

  Input/Output:
   NONE
   
  Input:
   seconds              - A reference to a constant unsigned integer that should be
                          the amount of seconds the caller wants converted
			  to hours.
  Output:
   NONE
   
  Returns:
   const unsigned int   - The resulting calculation from seconds to
                          hours.
*/
const unsigned int SecondsToTime::convertToHours(const unsigned int& seconds) const
{
  return seconds/(MINUTE * MINUTE);
} // end of "convertToHours"



/*
  Function:
   convertToMinutes
  
  Description:
   Converts the incoming parameter of seconds to minutes.

  Input/Output:
   NONE
   
  Input:
   seconds              - A reference to a constant unsigned integer that should be
                          the amount of seconds the caller wants converted
			  to minutes.
  Output:
   NONE
   
  Returns:
   const unsigned int   - The resulting calculation from seconds to
                          hours.
*/
const unsigned int SecondsToTime::convertToMinutes(const unsigned int& seconds) const
{
  return (seconds/MINUTE) % MINUTE;
} // end of "convertToMinutes"



/*
  Function:
   findRemainingSeconds
  
  Description:
   Calculates and returns a remainder of seconds from the total
   incoming seconds provided by the calling object.
  
  Input:
   seconds              - A reference to a constant unsigned integer that will
                          be calculated for a remainder of seconds if
			  divided by a minute.
  Output:
   NONE
   
  Returns:
   const unsigned int   - The calculated remainder of seconds.
*/
const unsigned int SecondsToTime::findRemainingSeconds
(const unsigned int& seconds) const
{
  return seconds % MINUTE;
} // end of "findRemainingSeconds"



/*
  Function:
   returnHHMMSS
  
  Description:
   Prepares incoming time valus for output by converting them to a 
   string type in HH:MM:SS format.

  Input/Output:
   NONE
   
  Input:
   hours                - A reference to a constant unsigned integer that represents
                          the total hours to be converted and formatted.

   minutes              - A reference to a constant unsigned integer that represents
                          the total minutes to be converted and formatted.

   seconds              - A reference to a constant unsigned integer that represents
                          the total seconds to be converted and formatted.
  Output:
   NONE
   
  Returns:
   string               - A formatted string in the pattern HH:MM:SS created by
                          using the incoming parameters.
*/
std::string SecondsToTime::returnHHMMSS(const unsigned int& hours,
					const unsigned int& minutes,
					const unsigned int& seconds) const
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
