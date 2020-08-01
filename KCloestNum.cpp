#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size(), pos, left, right;
        if ( arr[0] >= x ) 
            return vector<int>(arr.begin(),arr.begin()+k);
        if ( arr[n-1] <= x )
            return vector<int>(arr.end()-k,arr.end());
        pos = FindBinaryPosition( arr, x );
        left = max(pos - k + 1,0);
        right = min(pos + k - 1,n-1);
        while ( right - left + 1 > k )
        {
            if ( abs(arr[left]-x) > abs(arr[right]-x) )
                left++;
            else 
                right--;
        }
        
        return vector<int> (arr.begin()+left, arr.begin()+right+1);
    }
    
    int FindBinaryPosition( vector<int> &arr, int val )
    {
        int i = 0, j = arr.size()-1;
        while ( i < j )
        {
            int mid = i + (j-i)/2;
            if ( arr[mid] < val ) 
                i = mid + 1;
            else if ( arr[mid] == val )
                return mid;
            else 
                j = mid;
        }
        
        return i;
    }
};

int main()
{
    Solution s;
    vector<int> data = {0,0,1,2,3,3,4,7,7,8};
    int k = 3, x = 5;
    s.findClosestElements(data,k,x);
    return 0;
}