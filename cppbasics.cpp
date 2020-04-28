// This file tests the basics of cpp, mainly the semantics things 
#include <iostream>
#include <algorithm>
#include <numeric>
#include <time.h>
#include <thread>

using namespace std;

// test memory location 
struct S {
    char a;
    int b : 5,
          : 0,
        d : 8;
    struct { 
        int ee : 8;
    } e;
} obj; 

#if 0
int main()
{
    cout << " The number of bits in a byte is " << __CHAR_BIT__ << endl;
    cout << " Or use the value of " << numeric_limits<unsigned char>::digits << endl;

    // Any attempt to read or write to an object whose type is volatile-qualified through a 
    // non-volatile lvalue results in undefined behavior:

    volatile int n = 1;
    int *p = (int *)&n;
    int val = *p;       // undefined behavior 
    cout << " val = " << val << " address of n is  " << hex << p << endl;

    const int *p1 = (const int[]) { 1,2,3};
    const int *p2 = (const int[]) {2,3,4};
    cout << "p1 = " << p1 <<" p2 = " << p2 << endl;
}
#endif 

#if 0
int main()
{
    clock_t t = clock();
    double  d = 0.0;
    for ( int n = 0; n < 100000; n++ )
        for ( int m = 0; m < 10000; m++ )
            d += m*n;       // reads and writes to a non-volatle 
    cout << "Modified a non-volatile variable 100m times."
         << " Time taken: %.2f second " << (double)(clock()-t)/CLOCKS_PER_SEC << endl;
    t = clock();
    volatile double  vd = 0.0;
    for ( int n = 0; n < 100000; n++ )
        for ( int m = 0; m < 10000; m++ )
            vd += m*n;       // reads and writes to a non-volatle 
    cout << "Modified a volatile variable 100m times."
         << " Time taken: %.2f second " << (double)(clock()-t)/CLOCKS_PER_SEC << endl;

}
#endif

