// Problem Description 
/*
 We have a collection of stones, each stone has a positive integer weight.

Each turn, we choose the two heaviest stones and smash them together.  Suppose the stones have weights x and y with x <= y.  The result of this smash is:

If x == y, both stones are totally destroyed;
If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
At the end, there is at most 1 stone left.  Return the weight of this stone (or 0 if there are no stones left.)

 

Example 1:

Input: [2,7,4,1,8,1]
Output: 1
Explanation: 
We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of last stone.

 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>


using namespace std;

int lastStoneWeight(vector<int>& stones) {
    int stonearray[4];
    memset( stonearray, 0, sizeof(stonearray) );
    for ( auto s : stones )
        stonearray[s]++;
    int n = stones.size();
    int idx = 3;
    while ( n > 1 && idx >= 0 )
    {
        if ( stonearray[idx] )
        {
            n -= (stonearray[idx] / 2) * 2;
            stonearray[idx] %= 2;
            if ( n <= 1 )
                break;
            int biggest = idx; 
            if ( stonearray[idx] )
            {
                while( !stonearray[--idx] );
                stonearray[idx]--;
                stonearray[biggest-idx]++;
                idx = max(biggest-idx, idx);
                n -= 1;
                if ( n <= 1 )
                    break;
            } 
            else 
            {
                idx--;
            }
        }
        else 
        {
            idx--;
        }     
    }
    if ( n == 0 )
        return 0; 
    else 
    {
        while (!stonearray[idx]) 
                idx--;
        return idx;
    }
}

int main()
{
    vector<int> stones{1,3};
    cout << "Last stone is " << lastStoneWeight(stones) << endl;
}