// ============================================================================
// File: foo.hpp
// Description:
// ============================================================================
#ifndef FOO_HPP
#define FOO_HPP
#include <iostream>

class Foo{
public:
  // constructors
  Foo(const int inVal);

  // member functions
  void printFoo() const;

  // getters and setters
  const int getVal() const;
  
private:
  // member variables
  int m_val;
};

std::ostream& operator<<(std::ostream& out, const Foo& inFoo);

#endif
