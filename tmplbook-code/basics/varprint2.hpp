#include <iostream>

template<typename T>
void print (T arg)
{
  std::cout << arg << '\n';  // print passed argument
}

template<typename T, typename... Types>
void print (T firstArg, Types... args)
{
  std::cout << sizeof...(Types) << '\n';
  std::cout << sizeof...(args) << '\n';
  print(firstArg);           // call print() for the first argument
  print(args...);            // call print() for remaining arguments
}
