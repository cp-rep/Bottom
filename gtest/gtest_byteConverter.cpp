/*
  File:
   gtest_byteConverter.cpp
  
  Description:
   Google Unit Tests for the function implementations of the byteConverter.hpp class.
*/
#include <gtest/gtest.h>
#include "byteConverter.hpp"

TEST(KiBToMiBFunction, ConverstionCorrect)
{
  EXPECT_EQ(KiBToMiB(8388608), 8192);
}


TEST(KiBToMiBFunction, ConverstionIncorrect)
{
  EXPECT_NE(KiBToMiB(8388608), 8193);
}


