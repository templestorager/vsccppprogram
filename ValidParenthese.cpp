// Problem Description
/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true
Example 2:

Input: "()[]{}"
Output: true
Example 3:

Input: "(]"
Output: false
Example 4:

Input: "([)]"
Output: false
Example 5:

Input: "{[]}"
Output: true

*/
#include <iostream>
#include <string> 
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        unordered_set<char> open{'(','{','['};
        unordered_map<char, char> validpair{{')','('},{']','['},{'}','{'}};
        stack<char> st; 
        for ( auto c : s ) 
        {
            if ( open.count(c) )
            {
                st.push(c);
            }
            else if ( st.empty() || st.top() != validpair[c] )
            {
                return false;
            }
            else 
            {
                st.pop();
            }
        }
        
        if ( !st.empty() )
            return false;
        return true;
    }
};

int main()
{
    string p = "[](][)";
    Solution s;
    bool IsValid = s.isValid(p);
    cout << "IsValid is " << IsValid << endl;
    //cin.clear();
    //cin.ignore( std::numeric_limits<streamsize>::max(),'\n');
    cin.get();
}