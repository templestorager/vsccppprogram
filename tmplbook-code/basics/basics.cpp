// This program file contains code snippet to demonstrate the very basics of cpp, more of lauguage itself 
#include <iostream> 
#include "complex.hpp"

// constexpr function could take both const and non-const arguments, the difference lies in that 
// they return const and non-const values, respectively, which could impact how we use the returned 
// value, e.g., in a constexpr expression 
constexpr auto AddOne( int val )
{
    return val + 1;
}

void ConstExpFunctionTest( )
{
    const int C_sz = 10;
    constexpr int n = AddOne(C_sz);
    int sz = 9;
    //constexpr int n2 = AddOne(sz);      // error: since AddOne return non-const result due to non-const argument
}

int main()
{
    // for assignmenet of "=" and the general {}-list: "=" might cause loss of information due to 
    // implicit conversion. So prefer the {}-list style, which will cause compile errors 
    int i1 = 7.2;  // i1 becomes 7
    // int i2{7.2};   // error;
    // int i3 = {7.2};  // error: static_cast<int>(7.2)
    float i4{7.2};   // no error.
    std::cout << i1 << '\n';
    // const and constexpr 
    const int dmv = 17;
    int var = 17;
    constexpr double max1 = 1.4 * dmv;
   // constexpr double max2 = 1.4 * var;      // error: var must be const 
    const double max3 = 1.4 * var;
    ConstExpFunctionTest();         // test constexpr functions
    std::cout << "sizeof(int) is " << (int) sizeof(int) << '\n';
    static_assert(sizeof(int) >= 4, "Int size should be more than 4 bytes" );

    std::string str;
    getline(std::cin,str);
    std::cout <<" Your input: " << str << '\n';
}