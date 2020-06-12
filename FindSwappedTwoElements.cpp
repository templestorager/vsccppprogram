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
            idx2 = i + 1;
            for ( int j = i+2; j < nums.size(); j++ )
            {
                if ( nums[j] < nums[idx2] )
                {
                    idx2 = j;
                }
            }
            
        }
        if ( idx2 != -1 )
            break;
    }
    
    x = nums[idx1];
    y = nums[idx2];
}

void FindSwappedValue2( const vector<int> &nums, int &x, int &y )
{
    int idx1 = -1, idx2 = -1;

    for ( int i = 0; i < nums.size()-1; i++ )
    {
        if ( nums[i] > nums[i+1] )
        {
            idx1 = i;
            for ( int j = i+1; j < nums.size(); j++ )
            {
                if ( nums[j] < nums[idx1+1] )
                {
                    idx2 = j;
                    break;
                }
            }

        }
        if ( idx2 != -1 )
            break;
    }

    x = nums[idx1];
    y = nums[idx2 != -1 ? idx2 : nums.size()-1];
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

void sortByOneSwap( vector<int> &arr ) 
{ 
    int n = arr.size();
    // Traverse the given array from rightmost side 
    for (int i = n-1; i > 0; i--) 
    { 
        // Check if arr[i] is not in order 
        if (arr[i] < arr[i-1]) 
        { 
            // Find the other element to be 
            // swapped with arr[i] 
            int j = i-1; 
            while (j>=0 && arr[i] < arr[j]) 
                j--; 
  
            // Swap the pair 
            cout << "Swapped values are " << arr[i] << " and " << arr[j+1] << endl;
            swap(arr[i], arr[j+1]); 
            break; 
        } 
    } 
} 

int main()
{
    int x, y;
    string a = "ABCDEF";
    vector<int> data{1,3,2,4};
    PrintVector(data);
    FindSwappedValue2( data,x,y);
    cout << "The swapped values are x = " << x << " y = " << y << endl;
    sortByOneSwap(data);
    cout << "After fix " << endl;
    PrintVector(data);

    cout << " Before pop_back a = " << a << endl;

    a.pop_back();

    cout << "After pop_back a = " << a << endl;

}