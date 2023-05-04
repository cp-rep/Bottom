/*
  File: byteConverter.cpp
  Description:
 */
#include "byteConverter.hpp"

#define TO_MIB 0.9765625



/*
  Function:
  KiBToMiB

  Description:
  Converts incoming parameter KiB units to MiB units and returns the result.

  
 */
const int KiBToMiB(const float& val)
{
  float temp = val;
  temp = temp * TO_MIB;
  temp = temp/1000;
    
  return (int)temp;
} // end of "kBToKiB"
