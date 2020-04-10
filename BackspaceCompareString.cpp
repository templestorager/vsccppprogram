#include <iostream>
#include <string>
using namespace std;

bool backspaceCompare(string S, string T) 
{
    int i = S.size() - 1, j = T.size() - 1;
    int numback1 = 0, numback2 = 0;
    while ( i >= 0 || j >= 0 )
    {
        while( i >= 0 && ( numback1 > 0 || S[i] == '#' ) )
        {
            if ( S[i] == '#' )
                numback1++;
            else
                numback1--;
            i--;
            // S[i--] == '#' : numback1++ : numback1--;
        }
        while ( j >= 0 && (numback2 > 0 || T[j] == '#' ) )
        {
            if ( T[j] == '#' )
                numback2++;
            else
                numback2--;
            j--;
            // T[i--] == '#' : numback2++ : numback2--;
        }
        if ( i < 0 || j < 0 )
            return i == j;
        if ( S[i--] != T[j--] )
            return false;
    }
    return i == j;
 }

int main()
{
    bool res;
    string str1 = "ab##", str2 = "c#d#";
    res = backspaceCompare(str1,str2);
    cout << (res ? "True" : "False") <<endl;
}