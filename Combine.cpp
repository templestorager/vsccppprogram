#include <vector>
#include <iostream>
using namespace std;

// this method is based on a mysterious algorithm, which I don't understand yet :-) 
// Seems to be like this
// init an array [1...k, n+1]
// check the array starting from the begining, if the current is consecutive to the next, then reset its value to 
// to its rank (i.e., position idx plus one)
// otherwise in creases the value by one and continue to the next loop
// for example: n = 4, k = 2;
// [1,2,5]  -- > [1,2]
// [1,3,5]  -- > [1,3]
// [2,3,5]  -- > [2,3]
// [1,4,5]  -- > [1,4]
// [2,4,5]  -- > [2,4]
// [3,4,5]  -- > [3,4]
// Done. 

// for example: n = 5, k = 3
// [1,2,3,6] --> [1,2,3]
// [1,2,4,6] --> [1,2,4]
// [1,3,4,6] --> [1,3,4]
// [2,3,4,6] --> [2,3,4]
// [1,2,5,6] --> [1,2,5]
// [1,3,5,6] --> [1,3,5]
// [2,3,5,6] --> [2,3,5]
// [1,4,5,6] --> [1,4,5]
// [2,4,5,6] --> [2,4,5]
// [3,4,5,6] --> [3,4,5]

vector<vector<int>> combine(int n, int k) 
{
    vector<vector<int> > res;
    vector<int> tmp;
    for ( int i = 1; i <=k; i++ )
        tmp.push_back(i);
    tmp.push_back(n+1);
    int j = 0; 
    while ( j < k )
    {
        res.push_back(vector<int>(tmp.begin(),tmp.end()-1));
        j = 0;
        while ( j < k && tmp[j+1] == tmp[j] + 1 )
        {
            tmp[j] = j+1;
            j++;
        }
        tmp[j]++;
    }
    for( auto i : res )
    {
        cout << "[ ";
        for ( auto j : i )
            cout << j <<" ";
        cout <<"]" << endl;
    }
    return res;
}

int main()
{
    cout << "C(4,2) generating sequence is " << endl;
    combine(4,2);
    cout << "C(5,3) generating sequence is " << endl;
    combine(5,3);
}