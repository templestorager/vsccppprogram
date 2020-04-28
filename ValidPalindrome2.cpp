#include <iostream>
#include <string>

using namespace std;

bool validPalindrome(string s) {
    int i = 0, j = s.size() - 1;
    while( i < j )
    {
        if ( s[i] == s[j] )
        {
            i++;
            j--;
        }
        else if ( helper(s,i+1,j) || helper(s,i,j-1) )
        {
            return true;
        } 
        else 
        {
            return false;
        }
    }
    return true;
}
bool helper(string s, int l, int r )
{
    while( l < r )
    {
        if ( s[l] == s[r] ) 
        {
            l++;
            r--;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool validPalindrome(string s) {
    return helper(s,0,s.size()-1);
}

int main()
{
    string str ="abc";
    validPalindrome(str);
}