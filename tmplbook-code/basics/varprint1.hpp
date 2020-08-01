#include <iostream>

#if 1
void print ()
{
}
#endif

template<typename T, typename... Types>
void print (T firstArg, Types... args)
{
  std::cout << firstArg << '\n';  // print first argument
  print(args...);                 // call print() for remaining arguments
}

#if 0

template<typename T, typename... Types> 
void print ( T firsArg, Types... args )
{
  std::cout << firstArg << '\n';
  print( args... );
}
#endif