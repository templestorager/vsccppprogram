#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    vector<bool> res(candies.size());
    // int max_candy = std::max_element(candies.begin(),candies.end());
    if ( candies.size() == 0 )
    {
        return res;
    }
    #if 1
    int max_candy = candies[0];
    for ( int i = 1; i < candies.size(); i++ )
    {
        if ( candies[i] > max_candy )
            max_candy = candies[i];
    }
    #endif 
    for ( int i = 0; i < candies.size(); i++ )
    {
        if ( candies[i] + extraCandies >= max_candy )
        {
            res[i] = true;
        }
        else 
        {
            res[i] = false;
        }
    }
    
    return res;
}

int main()
{
    vector<int> candies{1,3,4,5,6};
    uint32_t Data = (uint32_t)(0x81<<24)|(0x80<<16);
    cout << "Data = " << Data << endl;
    int extracandy = 2;
    kidsWithCandies( candies, extracandy );
}