#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int singleNumber(vector<int>& nums) {
    unordered_map<int,int> countmap;
    countmap.clear();
    for ( int i = 0; i < nums.size(); i++ )
    {
        countmap[nums[i]]++;
    }
    for ( auto it = countmap.begin(); it != countmap.end(); it++ )
    {
        if ( it->second == 1 )
            return it->first;
    }
    return -1;
}

int main()
{
    vector<int> a{2,2,1};
    int singlenumber = singleNumber(a);
    cout << "singlenumber is " << singlenumber << endl;
}