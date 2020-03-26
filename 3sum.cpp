// Problem Description 
/* Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > threeSum(vector<int>& nums) 
{
    vector<vector<int> > res;
    sort(nums.begin(), nums.end());
    if ( nums.size() == 0 || nums.front() > 0 || nums.back() < 0 ) 
    {
        return res;
    }
    cout<< " nums.size() - 2 is " << nums.size() - 2 << endl;
    for ( int i = 0; i < nums.size() - 2; i++ ) 
    {
        if ( nums[i] > 0 ) 
            break;
        if ( i > 0 && nums[i] == nums[i-1] )
                continue;

        int target = 0 - nums[i], j = i+1, k = (int)nums.size() - 1;
        while ( j < k )
        {
            int val = nums[j] + nums[k];
            if ( val == target )
            {
                res.push_back({nums[i],nums[j],nums[k]});
                while ( j < k && nums[j] == nums[j+1] ) j++;
                while ( j < k && nums[k] == nums[k-1] ) k--;
                j++;
                k--;
            }
            else if ( val < target )
            {
                j++;
            }
            else{
                k--;
            }
        }
    }
    for ( int i = 0; i < res.size(); i++ )
    {
        cout<<"{ " <<res[i][0]<< " "<< res[i][1]<<" "<< res[i][2]<<" }"<<endl;
    }
    return res;
}

int main()
{
    // vector<int> test_data{ -1, 4, -1, 0, 0, 0, 0, 0, 1, 2 };
    vector<int> test_data{ 0 };
    char ch;
    int i;
    i = 321;
    ch = i;
    char a = 'A';
    int  b = 0xA;
    cout << " i = 0x" << hex << i << " ch = 0x" << hex << (int)ch << endl;
    threeSum(test_data);
    cout << "*************************" << endl;
    cout << "a = " << (int) a << "b = " << (int)b << endl;

    return 0;
}
