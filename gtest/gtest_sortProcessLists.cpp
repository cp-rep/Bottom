/*
  File: gtest_sortProcessLists.cpp
  
  Description:
  Tests the function implementations of the sortProcessLists.hpp header.
*/
#include <gtest/gtest.h>
#include "sortProcessLists.hpp"
#include "extractFileData.hpp"




TEST(sortValuesByPID_FUNCTION, sortValuesByPID_TEST)
{
  std::unordered_map<int, ProcessInfo*> allProcessInfo;
  std::vector<int> pids;
  std::vector<int> sorted;
  std::vector<int> isEqual;

  // allocate processes
  ProcessInfo* process1 = new ProcessInfo();
  ProcessInfo* process2 = new ProcessInfo();
  ProcessInfo* process3 = new ProcessInfo();
  ProcessInfo* process4 = new ProcessInfo();
  ProcessInfo* process5 = new ProcessInfo();
  ProcessInfo* process6 = new ProcessInfo();
  ProcessInfo* process7 = new ProcessInfo();
  ProcessInfo* process8 = new ProcessInfo();
  ProcessInfo* process9 = new ProcessInfo();
  ProcessInfo* process10 = new ProcessInfo();
  ProcessInfo* process11 = new ProcessInfo();
  ProcessInfo* process12 = new ProcessInfo();
  ProcessInfo* process13 = new ProcessInfo();
  ProcessInfo* process14 = new ProcessInfo();
  ProcessInfo* process15 = new ProcessInfo();
  ProcessInfo* process16 = new ProcessInfo();
  ProcessInfo* process17 = new ProcessInfo();
  ProcessInfo* process18 = new ProcessInfo();
  ProcessInfo* process19 = new ProcessInfo();
  ProcessInfo* process20 = new ProcessInfo();

  // save pids to vector
  pids.push_back(1);
  pids.push_back(2);
  pids.push_back(3);
  pids.push_back(4);
  pids.push_back(5);
  pids.push_back(6);
  pids.push_back(7);
  pids.push_back(8);
  pids.push_back(9);
  pids.push_back(10);
  pids.push_back(11);
  pids.push_back(12);
  pids.push_back(13);
  pids.push_back(14);
  pids.push_back(15);
  pids.push_back(16);
  pids.push_back(17);
  pids.push_back(18);
  pids.push_back(19);
  pids.push_back(20);

  // allocate processes at corresponding pid indices
  allProcessInfo.insert(std::make_pair(pids.at(0), process1));
  allProcessInfo.insert(std::make_pair(pids.at(1), process2));
  allProcessInfo.insert(std::make_pair(pids.at(2), process3));
  allProcessInfo.insert(std::make_pair(pids.at(3), process4));
  allProcessInfo.insert(std::make_pair(pids.at(4), process5));
  allProcessInfo.insert(std::make_pair(pids.at(5), process6));
  allProcessInfo.insert(std::make_pair(pids.at(6), process7));
  allProcessInfo.insert(std::make_pair(pids.at(7), process8));
  allProcessInfo.insert(std::make_pair(pids.at(8), process9));
  allProcessInfo.insert(std::make_pair(pids.at(9), process10));
  allProcessInfo.insert(std::make_pair(pids.at(10), process11));
  allProcessInfo.insert(std::make_pair(pids.at(11), process12));
  allProcessInfo.insert(std::make_pair(pids.at(12), process13));
  allProcessInfo.insert(std::make_pair(pids.at(13), process14));
  allProcessInfo.insert(std::make_pair(pids.at(14), process15));
  allProcessInfo.insert(std::make_pair(pids.at(15), process16));
  allProcessInfo.insert(std::make_pair(pids.at(16), process17));
  allProcessInfo.insert(std::make_pair(pids.at(17), process18));
  allProcessInfo.insert(std::make_pair(pids.at(18), process19));
  allProcessInfo.insert(std::make_pair(pids.at(19), process20));

  // test processes allocated correctly
  EXPECT_EQ(allProcessInfo.size(), 20);

  // set process value data
  // characters
  allProcessInfo.at(pids.at(0))->setS('A');
  allProcessInfo.at(pids.at(1))->setS('B');
  allProcessInfo.at(pids.at(2))->setS('C');
  allProcessInfo.at(pids.at(3))->setS('D');
  allProcessInfo.at(pids.at(4))->setS('E');

  allProcessInfo.at(pids.at(5))->setS('A');
  allProcessInfo.at(pids.at(6))->setS('B');
  allProcessInfo.at(pids.at(7))->setS('C');
  allProcessInfo.at(pids.at(8))->setS('D');
  allProcessInfo.at(pids.at(9))->setS('E');
  
  allProcessInfo.at(pids.at(10))->setS('A');
  allProcessInfo.at(pids.at(11))->setS('B');
  allProcessInfo.at(pids.at(12))->setS('C');
  allProcessInfo.at(pids.at(13))->setS('D');
  allProcessInfo.at(pids.at(14))->setS('E');

  allProcessInfo.at(pids.at(15))->setS('A');
  allProcessInfo.at(pids.at(16))->setS('B');
  allProcessInfo.at(pids.at(17))->setS('C');
  allProcessInfo.at(pids.at(18))->setS('D');
  allProcessInfo.at(pids.at(19))->setS('E');

  // strings
  allProcessInfo.at(pids.at(0))->setUSER("ME");
  allProcessInfo.at(pids.at(1))->setUSER("MEE");
  allProcessInfo.at(pids.at(2))->setUSER("MEEE");
  allProcessInfo.at(pids.at(3))->setUSER("MEEEE");
  allProcessInfo.at(pids.at(4))->setUSER("MEEEEE");

  allProcessInfo.at(pids.at(5))->setUSER("ME");
  allProcessInfo.at(pids.at(6))->setUSER("MEE");
  allProcessInfo.at(pids.at(7))->setUSER("MEEE");
  allProcessInfo.at(pids.at(8))->setUSER("MEEEE");
  allProcessInfo.at(pids.at(9))->setUSER("MEEEEE");

  allProcessInfo.at(pids.at(10))->setUSER("ME");
  allProcessInfo.at(pids.at(11))->setUSER("MEE");
  allProcessInfo.at(pids.at(12))->setUSER("MEEE");
  allProcessInfo.at(pids.at(13))->setUSER("MEEEE");
  allProcessInfo.at(pids.at(14))->setUSER("MEEEEE");

  allProcessInfo.at(pids.at(15))->setUSER("ME");
  allProcessInfo.at(pids.at(16))->setUSER("MEE");
  allProcessInfo.at(pids.at(17))->setUSER("MEEE");
  allProcessInfo.at(pids.at(18))->setUSER("MEEEE");
  allProcessInfo.at(pids.at(19))->setUSER("MEEEEE");

  // doubles
  allProcessInfo.at(pids.at(0))->setCPUUsage(1.1);
  allProcessInfo.at(pids.at(1))->setCPUUsage(2.2);
  allProcessInfo.at(pids.at(2))->setCPUUsage(3.3);
  allProcessInfo.at(pids.at(3))->setCPUUsage(4.4);
  allProcessInfo.at(pids.at(4))->setCPUUsage(5.5);

  allProcessInfo.at(pids.at(5))->setCPUUsage(1.1);
  allProcessInfo.at(pids.at(6))->setCPUUsage(2.2);
  allProcessInfo.at(pids.at(7))->setCPUUsage(3.3);
  allProcessInfo.at(pids.at(8))->setCPUUsage(4.4);
  allProcessInfo.at(pids.at(9))->setCPUUsage(5.5);

  allProcessInfo.at(pids.at(10))->setCPUUsage(1.1);
  allProcessInfo.at(pids.at(11))->setCPUUsage(2.2);
  allProcessInfo.at(pids.at(12))->setCPUUsage(3.3);
  allProcessInfo.at(pids.at(13))->setCPUUsage(4.4);
  allProcessInfo.at(pids.at(14))->setCPUUsage(5.5);
  
  allProcessInfo.at(pids.at(15))->setCPUUsage(1.1);
  allProcessInfo.at(pids.at(16))->setCPUUsage(2.2);
  allProcessInfo.at(pids.at(17))->setCPUUsage(3.3);
  allProcessInfo.at(pids.at(18))->setCPUUsage(4.4);
  allProcessInfo.at(pids.at(19))->setCPUUsage(5.5);

  // unsigned ints
  allProcessInfo.at(pids.at(0))->setVIRT(111);
  allProcessInfo.at(pids.at(1))->setVIRT(222);
  allProcessInfo.at(pids.at(2))->setVIRT(333);
  allProcessInfo.at(pids.at(3))->setVIRT(444);
  allProcessInfo.at(pids.at(4))->setVIRT(555);

  allProcessInfo.at(pids.at(5))->setVIRT(111);
  allProcessInfo.at(pids.at(6))->setVIRT(222);
  allProcessInfo.at(pids.at(7))->setVIRT(333);
  allProcessInfo.at(pids.at(8))->setVIRT(444);
  allProcessInfo.at(pids.at(9))->setVIRT(555);

  allProcessInfo.at(pids.at(10))->setVIRT(111);
  allProcessInfo.at(pids.at(11))->setVIRT(222);
  allProcessInfo.at(pids.at(12))->setVIRT(333);
  allProcessInfo.at(pids.at(13))->setVIRT(444);
  allProcessInfo.at(pids.at(14))->setVIRT(555);

  allProcessInfo.at(pids.at(15))->setVIRT(111);
  allProcessInfo.at(pids.at(16))->setVIRT(222);
  allProcessInfo.at(pids.at(17))->setVIRT(333);
  allProcessInfo.at(pids.at(18))->setVIRT(444);
  allProcessInfo.at(pids.at(19))->setVIRT(555);

  // all sorted results should equal this pid list
  isEqual = { 5, 10, 15, 20, 4, 9, 14, 19, 3, 8, 13, 18, 2, 7, 12, 17, 1, 6, 11, 16 };
  
  // test characters
  sorted = sortValuesByPID(allProcessInfo,
			   pids,
			   &ProcessInfo::getS);
  EXPECT_EQ(sorted, isEqual);


  // test strings
  sorted = sortValuesByPID(allProcessInfo,
			   pids,
			   &ProcessInfo::getUSER);
  EXPECT_EQ(sorted, isEqual);  
  
  // test doubles
  sorted = sortValuesByPID(allProcessInfo,
			   pids,
			   &ProcessInfo::getCPUUsage);
  EXPECT_EQ(sorted, isEqual);  

  // test unsigned integers
  sorted = sortValuesByPID(allProcessInfo,
			   pids,
			   &ProcessInfo::getVIRT);
  EXPECT_EQ(sorted, isEqual);  		
		
  // clean up
  removeDeadProcesses(allProcessInfo, pids);

  // test they cleaned up
  EXPECT_EQ(allProcessInfo.size(), 0);
}
