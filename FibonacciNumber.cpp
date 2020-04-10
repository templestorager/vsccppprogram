// Problem Description 
/* 
 This utility program compares the time of computing the nth fibonacci number using different 
 method:
 1. Regular recursion 
 2. Dynamic programming: Memoization (top-down)
 3. Dynamic programming: Tabulation (bottom-up)
 */

#include <iostream>
#include <time.h>

using namespace std;

#define FIN_NUM     40
#define MAX_SPACE   ( FIN_NUM + 1 )

long long fib_recurision( int n )
{
    if ( n <= 1 )
        return n;
    else 
        return fib_recurision(n-1) + fib_recurision(n-2);
}

static int lookuptable[MAX_SPACE];
void init_memoization_table()
{
    for ( int i = 0; i < MAX_SPACE; i++ )
        lookuptable[i] = -1;
}

long long fib_memoization( int n )
{
    if ( lookuptable[n] == -1 )
    {
        if ( n <= 1 )
        {
            lookuptable[n] = n;
        }
        else
        {
            lookuptable[n] = fib_memoization(n-1) + fib_memoization(n-2);
        }
    }
    return lookuptable[n];
}

long long fib_tabulation( int n )
{
#if 1
    if ( n <= 1 )
    return n;
    long f0 = 0, f1 = 1, res;
    for ( int i = 2; i <= n; i++ )
    {
        res = f0 + f1; 
        f0 = f1;
        f1 = res;
    }

    return res;
#endif
#if 0
    long long f[n+1];
    f[0] = 0, f[1] = 1;
    for ( int i = 2; i <= n; i++ )
        f[i] =f[i-1] + f[i-2];
    return f[n];
#endif
}

int main()
{
    clock_t start, end;
    long value;
    cout << "calculating fibnacci(" << FIN_NUM << ") takes " << endl;
    cout << "   Method          Time(us)        Value " << endl;
    cout << "   Recursion        " << "  ";
    start = clock();
    value = fib_recurision( FIN_NUM );
    end = clock();
    cout << (double) ((end-start)/(CLOCKS_PER_SEC/1000000)) <<"        " << value <<endl;
    cout << "   Memoization        " << "  ";
    start = clock();
    init_memoization_table();
    value = fib_memoization( FIN_NUM );
    end = clock();
    cout << (double) ((end-start)/(CLOCKS_PER_SEC/1000000)) <<"           " << value <<endl;
    cout << "   Tabulation         " << "  ";
    start = clock();
    value = fib_tabulation( FIN_NUM );
    end = clock();
    cout << (double) ((end-start)/(CLOCKS_PER_SEC/1000000)) <<"           " << value <<endl;
}

