// ============================================================================
// File: gtestCurseWindow.cpp
// Description:
//  Tests functionality of the CurseWindow class from the head and source file
//  curseWindow.hpp and curseWindow.cpp
// ============================================================================
#include <gtest/gtest.h>
#include "curseWindow.hpp"



/*
  Test the default constructor initializes correctly
 */
TEST(ClassTest, DefaultConstructor)
{
  CurseWindow win;
  EXPECT_EQ(nullptr, win.getWindow());
  EXPECT_EQ(0, win.getNumLines());
  EXPECT_EQ(0, win.getNumCols());
  EXPECT_EQ(0, win.getMaxWindowY());
  EXPECT_EQ(0, win.getMaxWindowX());
  EXPECT_EQ(0, win.getMinWindowY());    
  EXPECT_EQ(0, win.getMinWindowX());
  EXPECT_EQ(0, win.getCenterY());
  EXPECT_EQ(0, win.getCenterX());
  EXPECT_EQ(0, win.getStartY());
  EXPECT_EQ(0, win.getStartX());
  EXPECT_EQ(0, win.getCurrentY());
  EXPECT_EQ(0, win.getCurrentX());
  EXPECT_EQ(0, win.getPreviousY());
  EXPECT_EQ(0, win.getPreviousX());    
}



TEST(ClassTest, Constructor)
{
  CurseWindow win(nullptr,
		  1,
		  2,
		  3,
		  4,
		  5,
		  6,
		  7,
		  8,
		  9,
		  10,
		  11,
		  12,
		  13,
		  14);

  EXPECT_EQ(nullptr, win.getWindow());
  EXPECT_EQ(1, win.getNumLines());
  EXPECT_EQ(2, win.getNumCols());
  EXPECT_EQ(3, win.getMaxWindowY());
  EXPECT_EQ(4, win.getMaxWindowX());
  EXPECT_EQ(5, win.getMinWindowY());    
  EXPECT_EQ(6, win.getMinWindowX());
  EXPECT_EQ(7, win.getCenterY());
  EXPECT_EQ(8, win.getCenterX());
  EXPECT_EQ(9, win.getStartY());
  EXPECT_EQ(10, win.getStartX());
  EXPECT_EQ(11, win.getCurrentY());
  EXPECT_EQ(12, win.getCurrentX());
  EXPECT_EQ(13, win.getPreviousY());
  EXPECT_EQ(14, win.getPreviousX());      
}
