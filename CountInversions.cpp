// Problem Description 
/* 
Inversion Count for an array indicates – how far (or close) the array is from being sorted. If array is already sorted then inversion count is 0. If array is sorted in reverse order that inversion count is the maximum.
Formally speaking, two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j
*/

#include <iostream>
#include <vector>

using namespace std;

#if 0
// This method needs two loops. In the second loop, if there is any element is less than the currently considered 
// element, then it is an inversion. 
// O(n^2), O(1)
int CountInversion( vector<int> data )
{
    int res = 0;
    int n = data.size();
    for ( int i = 0; i < n; i++ )
    {
        int Inv = 0;
        for ( int j = i+1; j < n; j++ )
        {
            if ( data[j] < data[i] )
                Inv++;
        }
        res += Inv;
    }

    return res;
}

int main()
{
    vector<int> data{8,4,2,1};
    cout << "The number of inversions is " << CountInversion(data) << endl;

}
#endif 

#if 1
// The following method couples the counting of inversions with the merge sort procedure, i.e., 
// when we compare the left side with the right side part, if we encounter the left element is larger
// than the right element, then we know we the elements starting from the left element till the end of the 
// left side are all larger than the right element being considered. Therefore, those are inversions.
// The inversion count will be the sum of the left side, the right side, and the number crossing both sides
// Note that: the regular merge sort requires O(n) auxiliary space. There is a bottom-up variation of merge sort, 
// which don't require extra space
// O(nlgn), O(n)
int mergesort_count( vector<int> &data, vector<int> &tmp, int l_start, int r_start, int r_end )
{
    int i = l_start,j = r_start, k = l_start;
    int count = 0;
    while ( i < r_start && j <= r_end )
    {
        if ( data[i] <= data[j] )
        {
            tmp[k++] = data[i++];
        }
        else 
        // data[i] > data[j]
        {
            tmp[k++] = data[j++];
            count += r_start - i;  // data[i...r_start-1] are all larger than data[j], i.e., r_start - 1 - i + 1 = r_start-i. 
        }
    }
    while ( i < r_start )
    {
        tmp[k++] = data[i++];
    }
    while ( j <= r_end )
    {
        tmp[k++] = data[j++];
    }

    // copy back the sorted in auxiliary to the original array 
    for ( int n = l_start; n <= r_end; n++ )
    {
        data[n] = tmp[n];
    }

    return count;
}

int mergesort_helper( vector<int> &data, vector<int> &tmp, int l, int r )
{
    int mid, count = 0;
    if ( r > l )
    {
        mid = l + ( r - l ) / 2;
        count += mergesort_helper( data, tmp, l, mid );
        count += mergesort_helper( data, tmp, mid+1, r);
        count += mergesort_count( data, tmp, l, mid+1, r );
    }

    return count;
}

int CountInersion_MergeSort( vector<int> &data )
{
    vector<int> tmp(data.size());
    return mergesort_helper( data, tmp, 0, data.size() - 1 );
}

int main()
{
    vector<int> test_data{1,20,6,4,5};
    cout << " The number of inversions is " << CountInersion_MergeSort( test_data ) << endl;

    return 0;
}
#endif