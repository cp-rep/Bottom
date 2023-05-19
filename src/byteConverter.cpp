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
const double KiBToMiB(const double& val)
{
  double temp = val;
  temp = temp * TO_MIB;
  temp = temp/1000;
    
  return temp;
} // end of "kBToKiB"
