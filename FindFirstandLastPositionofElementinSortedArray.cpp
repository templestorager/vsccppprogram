// 

#include <iostream>
#include <vector>

using namespace std;

vector<int> searchRange(vector<int>& nums, int target) {
    int pos = INT_MAX, first_pos, last_pos;
    int l = 0, r = nums.size();
    while ( l < r )
    {
        int mid = (l+r)/2;
        if ( nums[mid] == target ) 
        {
            pos = mid;
            break;
        }
        else if ( nums[mid] > target )
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    
    if ( pos == INT_MAX )
    {
        return {-1,-1};
    }
    first_pos = last_pos = pos;
    while( first_pos > 0 && nums[first_pos-1] == target )
        first_pos--;
    while(last_pos < nums.size()-1 && nums[last_pos+1] == target )
        last_pos++;
    return {first_pos,last_pos};
}

int main()
{
    vector<int> res; 
    vector<int> data{1};
    int target = 1;
    res = searchRange(data,target);
    cout << "res is [ " << res[0] <<"," << res[1] <<" ]" <<endl;
}