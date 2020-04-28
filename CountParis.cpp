// Problem Description
/*

*/

#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> val{2,5,7,4,6,8,3};
    int diff = 2, len = val.size();
    int i = 0, j = 1, pairs = 0;
    while ( i < len )
    {
        for ( j = i + 1; j < len; j++ )
        {
            if ( val[j] == (val[i]+diff) || val[j] == (val[i]-diff) )
            {
                pairs++;
                cout << "[" << val[i] << "," << val[j] << "]" << endl;
            }
        }
        i++;
    }

    cout << "paris = " << pairs << endl;
}