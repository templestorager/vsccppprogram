template<typename T>
T max (T a, T b)
{
  // if b < a then yield a else yield b
  return  b < a ? a : b;
}

template<typename T1, typename T2> 
T2 max( T1 a, T2 b )
{
  return b < a ? a : b;
}

template <typename RT, typename T1, typename T2>
RT max3( T1 a, T2 b)
{
  return b < a ? a : b;
}

template <typename T1, typename T2>
auto max_auto(T1 a, T2 b)
{
  return b < a ? a : b;
}