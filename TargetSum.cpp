#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int findTargetSumWays(vector<int>& nums, int S) {
    int n = nums.size();
    vector<unordered_map<int,int> > dp(n+1);
    dp[0][0]  = 1;

    for ( int i = 0; i < n; i++ ){
        for ( auto &a : dp[i] )
        {
            int sum = a.first, cnt = a.second;
            dp[i+1][sum+nums[i]] += cnt;
            dp[i+1][sum-nums[i]] += cnt;
        }
    }
    
    return dp[n][S];
}

int main()
{
    vector<int> data{0,0,0,1};
    findTargetSumWays(data,0);
}