/*
  File: gtest_extractFileData.cpp
  
  Description:
  Tests the function implementations of the extractFileData.hpp header.
*/
#include <gtest/gtest.h>
#include "extractFileData.hpp"



/*
  Test:
  returnPhraseLine_fail_to_open

  Description:
  Attempts to open a filename that does not exist.  The assertion
  should return equal to the empty string if the filename
  successfully fails to open.
 */
TEST(ExtractFileData, returnPhraseLine_fail_to_open)
{
  
  ASSERT_EQ("N/A",
	    returnPhraseLine("noFile", "MemTotal"));
} // end of "returnPhraseLine_fail_to_open"



/*
  Test:
  returnPhraseLine_successful_open_and_read

  Description:
  Attempts to open a file, read it line by line looking for
  the provided phrase in the second argument.
  A successful assertion means the file was successfully opened
  and the search phrase was found, returning the provided
  assertion phrase.
 */
TEST(ExtractFileData, returnPhraseLine_successful_open_and_read)
{
    ASSERT_EQ("MemTotal:        8124456 kB",
	      returnPhraseLine("/proc/meminfo", "MemTotal"));
} // end of "returnPhraseLine_successful_open_and_read"



/*
  Test:
  returnPhraseLine_successful_open_phrase_not_found

  Description:
  Attempts to open a file, read it line by line looking for the
  provided phrase in the second argument.  The phrase it is looking
  for should not exist in the file, therefore a successful
  Assertion should return the empty string.
 */
TEST(ExtractFileData, returnPhraseLine_successful_open_phrase_not_found)
{
  ASSERT_EQ("",
	    returnPhraseLine("/proc/meminfo", "Phrase doesn't Exist."));
} // end of "returnPhraseLine_successful_open_phrase_not_found"



/*
  Test:
  returnFirstIntFromLine_int_exists

  Description:
  Calls the function returnFirstIntFromLine providing a string
  as an argument that contains a numeric characters.  The
  assertion succeeds if the returned int reprensenting those
  numeric characters match the int value assertion.
 */
TEST(ExtractFileData, returnFirstIntFromLine_int_exists)
{
  ASSERT_EQ(8124456,
	    returnFirstIntFromLine("MemTotal:        8124456 kB"));
} // end of "returnFirstIntFromLine_int_exists"



/*
  Test:
  returnFirstIntFromLine_int_doesnt_exist

  Description:
  Calls the function returnFirstIntFromLine providing a string
  as an argument that contains no numeric characters.  The
  assertion succeeds if the returned int is -1 matching the
  assertion value.
 */
TEST(ExtractFileData, returnFirstIntFromLine_int_doesnt_exist)
{
  ASSERT_EQ(-1,
	    returnFirstIntFromLine("MemTotal:        foo kB"));
} // end of "returnFirstIntFromLine_int_doesnt_exist"
