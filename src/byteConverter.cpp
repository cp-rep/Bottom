/*
  File: byteConverter.cpp
  Description:
 */
#include "byteConverter.hpp"

#define TO_KIBIBYTE 0.9765625



/*
  Function:

  Description:
 */
const float ByteConverter::kBToKiB(const float& val)
{
  return val * TO_KIBIBYTE;
} // end of "kBToKiB"



/*
  Function:

  Description:
 */
const float ByteConverter::_KiBToMiB(const float& val)
{
  return 0;
} // end of "_KiBToMiB"
