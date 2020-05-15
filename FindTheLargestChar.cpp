// Problem Description 
/*
    Given a string, find the biggest char that has both upper case and lower case appeared in the string. 
    Return a string containing the upper case of it if found. Otherwise, return "NO". 
    S=“aaBabcDaA”, the output is “B”
    S=“Codility”, the output is “NO”
*/

#include <iostream> 

using namespace std;

string FindChar( string s )
{
    bool lower, upper;
    for ( char c = 'z'; c >= 'a'; c-- )
    {
        lower = false;
        upper = false;
        for ( int i = 0; i < s.size(); i++ )
        {
            if ( s[i] == c )
            {
                lower = true;
                break;
            }
        }

        for ( int i = 0; i < s.size(); i++ )
        {
            if ( s[i] == c-32 )
            {
                upper = true;
                break;
            }
        }

        if ( lower && upper )
        {
            return string(1,c-32);
        }
    }

    return "NO";
}

string FindCharMap( string s )
{
    // map UPPER case to the pair indicating lower and upper appearance  
    bool SeenUpper[26];
    bool SeenLower[26];
    string res = "NO";
    memset( SeenLower, false, 26 );
    memset( SeenUpper, false, 26 );
    for ( int i = 0; i < s.size(); i++ )
    {
        if ( isupper(s[i]) )
            SeenUpper[s[i]-'A'] = true;
        if ( islower(s[i]) )
            SeenLower[s[i]-'a'] = true;
    }

    for ( int i = 25; i >= 0; i-- )
    {
        if ( SeenLower[i] && SeenUpper[i] )
        {
            res = string(1,'A'+i );
            break;
        }
    }

    return res;
}

int main()
{
    string s1 = "aaBabcDaA";
    string s2 = "Codility";
    cout << "The result of s1 is " << FindCharMap(s1) << endl;
    cout << "The result of s2 is " << FindCharMap(s2) << endl;
}