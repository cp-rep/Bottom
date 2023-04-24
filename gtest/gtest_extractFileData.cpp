/*
  File: gtest_extractFileData.cpp
  
  Description:
  Tests functionality of the CursesWindow class from the head and source file
  cursesWindow.hpp and cursesWindow.cpp
*/
#include <gtest/gtest.h>
#include "extractFileData.hpp"



/*
 */
TEST(ExtractFileData, returnPhraseLine_fail_to_open)
{
  ExtractFileData data;
  
  // test for failure to open file
  ASSERT_EQ("N/A",
	    data.returnPhraseLine("noFile.txt", "MemTotal"));
}



/*
 */
TEST(ExtractFileData, returnPhraseLine_successful_open_and_read)
{
  ExtractFileData data;

  // test for successful open and phrase found
  //  ASSERT_EQ("MemTotal:        8124456 kB",
  ASSERT_EQ("N/A",
	    data.returnPhraseLine("~/Git/cp-rep/Bottom/Bottom/gtest/gtest_meminfo.txt", "MemTotal"));
}




/*
 */
TEST(ExtractFileData, returnPhraseLine_successful_open_phrase_not_found)
{
  ExtractFileData data;

  // test for successful open and phrase not found
  ASSERT_EQ("MemTotal:        8124456 kB",
	    data.returnPhraseLine("gtest_meminfo.txt", "NotFound"));  
}



