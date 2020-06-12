#include <iostream>
#include <vector>

using namespace std;

// This idea is based on the transformation distance between from a permutation to another permutation 
// after we sort the vector according to the element value, then this is the permuation we should be in
// but at the begining we are at the sorted order of the index. So we need to go step by step to make it 
// to the original index order, which is the number of swaps. 
// Complete the minimumSwaps function below.
int minimumSwaps(vector<int> arr) {
    vector<pair<int,int>> vec(arr.size());
    int swaps = 0;
    for( int i = 0; i < arr.size(); i++ )
    {
        vec[i].first  = arr[i];
        vec[i].second = i;
    }

    sort( vec.begin(), vec.end() );

    for ( int i = 0; i < vec.size(); i++ )
    {
        if ( vec[i].second == i )
        {
            continue;
        }
        else 
        {
            swap(vec[i].first, vec[vec[i].second].first);
            swap(vec[i].second,vec[vec[i].second].second);

            if ( i != vec[i].second )
                i--;
            swaps++;
        }
    }

    return swaps;
}

int main()
{
    vector<int> arr{3,1,2};
    int res = minimumSwaps( arr );
    cout << "minimum swap is " << res << endl;
    return res;
}