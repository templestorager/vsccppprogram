// Problem Description 
/*
 
 Run Length Encoding
Given an input string, write a function that returns the Run Length Encoded string for the input string.
For example, if the input string is “wwwwaaadexxxxxx”, then the function should return “w4a3d1e1x6”.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace  std;

string RunLengthEncode( string str )
{
    string res;
    if ( str.length() == 0 )
        return "";
    for ( int i = 0; i < str.length(); i++ )
    {
        int len = 1; 
        res.push_back( str[i] );
        while ( i < str.length() - 1 )
        {
            if ( str[i+1] == str[i] )
            {
                i++;
                len++;
            }
            else
            {
                break;
            }
            
        }
        res += to_string(len);
    }
    return res;
}

int main()
{
    const string str = "wwwwxxxxxxxxxxxxxxxxaaaaa";
    string rlestr = RunLengthEncode(str);
    cout << "RLE is " << rlestr << endl;
    uint32_t DcwMask = 0x43;
    DcwMask &= ~(1 << 1);
    cout << " DcwMaskShift = " << hex << DcwMask << endl;
}