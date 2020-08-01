#include <iostream> 

template<typename T1, typename T2>
auto max (T1 a, T2 b)
{
  std::cout << " call non-return type version " << '\n';
  return  b < a ? a : b;
}

template<typename RT, typename T1, typename T2>
RT max (T1 a, T2 b)
{
  std::cout << " call the return type version " << '\n';
  return  b < a ? a : b;
}
