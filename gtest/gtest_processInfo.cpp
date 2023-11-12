/*
  File:
   processInfo.hpp
  
  Description:
   Google Unit Tests for the function implementations of the extractFileData.hpp class.
*/
#include <gtest/gtest.h>
#include "processInfo.hpp"



TEST(CopyConstructor_FUNCTION, CopyConstructor_TEST)
{
  ProcessInfo p1(1,
		 "USER",
		 2,
		 3,
		 4,
		 5,
		 6,
		 7.7,
		 8.8,
		 "comm",
		 "54321",
		 'A',
		 true,
		 9,
		 8,
		 7,
		 6,
		 5);

  ProcessInfo p2(p1);

  EXPECT_EQ(p1, p2);

}

