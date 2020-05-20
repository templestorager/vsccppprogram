// Problem Description 
/*
Given an almost sorted array where only two elements are swapped, how to sort the array efficiently?
*/
#include <iostream>
#include <vector>

using namespace std;

void FindSwappedValue( const vector<int> &nums, int &x, int &y )
{
    int idx1 = -1, idx2 = -1;
    
    for ( int i = 0; i < nums.size()-1; i++ )
    {
        if ( nums[i] > nums[i+1] )
        {
            idx1 = i;
            for ( int j = i+1; j < nums.size(); j++ )
            {
                if ( nums[j] < nums[idx1] )
                {
                    idx2 = j;
                    break;
                }
            }
        }
    }
    
    x = nums[idx1];
    y = nums[idx2];
}

void PrintVector( const vector<int> &vec )
{
    if ( vec.size() == 0 )
        cout << "[ ] " << endl;
    else 
    {
        cout << "[ " ;
        for ( int i = 0; i < vec.size()-1; i++ )
        {
            cout << vec[i] <<" ";
        }
        cout << vec[vec.size()-1] << " ]" << endl;
    }
}

int main()
{
    int x, y;
    vector<int> data{10, 30, 20, 40, 50, 60, 70};
    PrintVector(data);
    FindSwappedValue( data,x,y);
    cout << "The swapped values are x = " << x << " y = " << y << endl;
}