// Problem Description
// Longest common subsequence 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int longestCommonSubsequence(string text1, string text2) {
    int len1 = text1.size(), len2 = text2.size();
    // int dp[len1+1][len2+1];
    vector<vector<int> > dp(len1+1,vector<int>(len2+1,0));
    for ( int r = 0; r <= len1; r++ )
        dp[r][0] = 0;
    for ( int c = 0; c <= len2; c++ )
        dp[0][c] = 0;
    for ( int r = 1; r <= len1; r++ )
    {
        for ( int c = 1; c <= len2; c++ )
        {
            if ( text1[r-1] == text2[c-1] )
            {
                dp[r][c] = dp[r-1][c-1] + 1;
            }
            else {
                dp[r][c] = max(dp[r-1][c],dp[r][c-1]);
            }
        }
    }
    
    return dp[len1][len2];
}

int main()
{
    string str1 = "a", str2 = "n";
    int lcslen = longestCommonSubsequence(str1,str2);

    cout << "lcslen = " << lcslen << endl;
}