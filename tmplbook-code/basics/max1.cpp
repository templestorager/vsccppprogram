#include "max1.hpp"
#include <iostream>
#include <string>

int main()
{
  int i = 42;
  std::cout << "max(7,i):   " << ::max(7,i) << '\n';

  double f1 = 3.4;
  double f2 = -6.7;
  std::cout << "max(f1,f2): " << ::max(f1,f2) << '\n';

  std::string s1 = "mathematics";
  std::string s2 = "math";
  std::cout << "max(s1,s2): " << ::max(s1,s2) << '\n';
  std::cout << "max(4,7.2) is " << ::max(4,7.2) << '\n';
  std::cout << "max(4,7.2) with double return type is " << ::max3<double>(4,7.2) << '\n';
  std::cout << "max(4,7.2) with int return type is " << ::max3<int>(4,7.2) << '\n';
  std::cout << "max(4,7.2) using auto return type is " << ::max_auto(4,7.2) << '\n';
}
