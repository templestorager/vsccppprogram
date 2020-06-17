// Problem Description
/*
Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/


#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int lengthOfLongestSubstring(string s) 
{
    int left = 0, len = 0, n = s.size(), i = 0;
    unordered_set<char> window;
    while ( i < n )
    {
        if ( !window.count(s[i]) )
        {
            window.insert( s[i++] );
            len = max( len, (int)window.size());
        }
        else 
        {
            window.erase(s[left++]);
        }
    }
    return len;
}

int main()
{
    string s = "abcabcbb";
    int len = lengthOfLongestSubstring( s );
    cout << "Len = " << len << endl;
}