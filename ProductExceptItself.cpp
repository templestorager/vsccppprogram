#include <iostream>
#include <vector>

using namespace std;

vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> L_P(n), R_P(n);
    vector<int> res;
    for ( int i = 0; i < n; i++ )
    {
        if ( i == 0 )
            L_P[i] = 1;
        else 
            L_P[i] = L_P[i-1] * nums[i-1];
    }
    
    for ( int i = n - 1; i >= 0; i-- )
    {
        if ( i == n - 1 )
            R_P[i] = 1;
        else 
            R_P[i] = R_P[i+1] * nums[i+1];
    }
    
    for ( int i = 0; i < n; i++ )
    {
        res[i] = L_P[i] * R_P[i];
    }
    
    return res;
}

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        for ( int i = 0; i < n; i++ )
        {
            if ( i == 0 )
                res[i] = 1;
            else 
                res[i] = res[i-1] * nums[i-1];
        }
        
        int R = 1;
        
        for ( int i = n-1; i >= 0; i-- )
        {
            res[i] *= R;
            R *= nums[i];
        }
        
        return res;
    }
};

int main()
{
    vector<int> data{1,2,3,4};

}