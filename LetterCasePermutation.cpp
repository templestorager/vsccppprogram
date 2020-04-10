#include <iostream> 
#include <string>
#include <vector>

using namespace std;

vector<string> letterCasePermutation_OrderChange(string S) {
    vector<string> res{""};
    for ( auto c : S )
    {
        if ( isdigit(c) )
        {
            for ( auto &str : res )
                str.push_back(c);
        }
        else 
        {
            int len = res.size();
            for ( int i = 0; i < len; i++ )
            {
                res.push_back(res[i]);
                res.back().push_back(toupper(c));
                res[i].push_back(tolower(c));
            }
        }
    } 
    for ( auto & str : res )
    {
        cout << "[ ";
        for ( auto c : str )
            cout << c <<" ";
        cout <<"]" <<endl;
    }
    return res;
}

// This recursion uses dfs which is a common approach. 
// Notice there is a difference that it doesn't pop the last element like in many other problems.
// The reason is it has to take the path (i.e., the current char has to be included)
void helper(vector<string> &res, int idx, string &s)
{
    if ( idx == s.size() )
    {
        res.push_back(s);
        cout << "[ ";
        for (auto c : s )
            cout << c << " ";
        cout << "]" <<endl;
        return;
    }
    helper(res,idx+1,s);
    if ( isalpha(s[idx]) )
    {
        s[idx] ^= 32;
        helper(res,idx+1,s);
    }
}

vector<string> letterCasePermutation_Recursion(string S) 
{
    vector<string> res;
    helper(res,0,S);
    return res;
}

vector<string> letterCasePermutation_OrderInPosition(string S) 
{
    vector<string> res;
    int cnt = 0;
    for ( auto c : S )
        if ( isalpha(c) )
            cnt++;
    for ( int i = 0; i < (1 << cnt); i++ )
    {
        int shift = 0; 
        string str;
        for ( auto c : S ) 
        {
            if ( isdigit(c) )
                str.push_back(c);
            else 
            {
                if ( i & ( 1 << shift++ ) )
                    str.push_back(toupper(c));
                else
                    str.push_back(tolower(c));
            }
        }
        res.push_back(str);
    }
    for ( auto & str : res )
    {
        cout << "[ ";
        for ( auto c : str )
            cout << c <<" ";
        cout <<"]" <<endl;
    }
    return res;
}
    
int main()
{
    string str[2] = {"Abc", "a1b2"};
    for ( int i = 0; i < 2; i++ )
    {
        cout << "Processing string " << str[i] << endl;
        cout << "The order of outcome using order change is " << endl;
        letterCasePermutation_OrderChange(str[i]);
        cout << endl;
        cout << "The order of outcome using recursion is " << endl;
        letterCasePermutation_Recursion(str[i]);
        cout << endl;
        cout << "The order of outcome using order change in position is " << endl;
        letterCasePermutation_OrderInPosition( str[i] );
        cout << endl;
    }
    for ( int i = 0; i < str[0].size(); i++ )
        cout << str[0][i];
        cout << endl;
    for ( auto c : str[0] )
        cout << c;
    cout <<endl;
}