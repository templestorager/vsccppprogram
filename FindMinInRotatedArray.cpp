#include <vector>
#include <iostream>

using namespace std;

int findMinHelper( vector<int> &nums, int l, int r )
{
    int mid = l + (r-l) / 2;
    if ( nums[l] <= nums[r] )
        return nums[l];
    return min(findMinHelper(nums,l,mid),findMinHelper(nums,mid+1,r));
}
int findMin(vector<int>& nums) {
    return findMinHelper(nums,0,nums.size()-1);
}

int main()
{
    vector<int> data{4,6,7,0,2,3};
    int min_val = findMin(data);
    cout << "min_val is " << min_val << endl;
}