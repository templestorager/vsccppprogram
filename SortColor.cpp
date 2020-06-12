#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define COLOR_NUM 7

void PrintColors( const vector<int> &colors );

// The array contains three distinct values 0,1,2, representing three colors, respectively
int sortColors( const vector<int> &arr )
{
    int swaps = 0;
    vector<int> data(arr.begin(),arr.end());
    int i = 0, j = 0, k = arr.size() - 1;
    while ( j <= k )
    {
        if ( data[j] == 0 )
        {
            swap( data[j++],data[i++] );
            swaps++;
        }
        else if ( data[j] == 2 )
        {
            swap( data[j],data[k--] );
            swaps++;
        }
        else 
        {
            j++;
        }
    }

    PrintColors(data);
    return swaps;
}

int SortColorsMinSwaps( const vector<int> &colors )
{
    vector<int> data(colors.begin(), colors.end());
    int swaps = 0;
    int count[3];
    memset( count, 0, sizeof(count) );
    for ( auto c : colors )
        count[c]++;
    int idx_0 = 0, idx_1 = count[0], idx_2 = count[1]+count[0]; 
    int boundary_0 = count[0], boundary_1 = count[1] + count[0], boundary_2 = colors.size(); 
    // first put all zeros in their positions 
    int j = idx_1, k = idx_2;
    int m = idx_1, n = idx_2;
    bool found;
    for ( int i = idx_0; i < boundary_0; i++ )
    {
        if ( data[i] == 0 )
            continue;
        found = false;
        if ( data[i] == 1 )
        {
            // first look 0 in the 1 region, to minimize move this 1 again
            while ( j < boundary_1 )
            {
                if ( data[j] == 0 )
                {
                    swap(data[i],data[j++]);
                    swaps++;
                    found = true;
                    break;
                }
                else
                {
                    j++;
                }
            }
            if ( !found )
            {
                while ( k < boundary_2 )
                {
                    if ( data[k] == 0 )
                    {
                        swap(data[i],data[k++]);
                        swaps++;
                        break;
                    }
                    else
                    {
                        k++;
                    }
                }
            }
        }
        else if ( data[i] == 2 )
        {
            // first look 0 in the 2 region, to minimize move this 1 again
            found = false;
            while ( n < boundary_2 )
            {
                if ( data[n] == 0 )
                {
                    swap(data[i],data[n++]);
                    swaps++;
                    found = true;
                    break;
                }
                else
                {
                    n++;
                }
            }
            if ( !found )
            {
                while ( m < boundary_1 )
                {
                    if ( data[m] == 0 )
                    {
                        swap(data[i],data[m++]);
                        swaps++;
                        break;;
                    }
                    else
                    {
                        m++;
                    }
                }
            }
        }
    }

    // Then we put 1 and 2 in order 
    int l = idx_2; 
    for ( int i = idx_1; i < boundary_1; i++ )
    {
        if ( data[i] == 1 )
            continue;
        else 
        {
            while ( l < boundary_2 )
            {
                if ( data[l] == 1 )
                {
                    swap( data[i],data[l++] );
                    swaps++;
                    break;
                }
                else 
                {
                    l++;
                }
            }
        }
    }

    PrintColors( data );

    return swaps;
}

void GenerateColors( vector<int> &colors, int n )
{
    srand(time(NULL));
    for ( int i = 0; i < n; i++ )
    {
        colors.push_back(rand()%3);
    }
}

void PrintColors( const vector<int> &colors )
{
    if ( colors.size() == 0 )
    {
        cout << "The array is empty " << endl;
    }
    else 
    {
        cout << "[" ;
        for ( int i = 0; i < colors.size() - 1; i++ )
            cout << colors[i] <<",";
        cout << colors[colors.size()-1] <<"]" << endl;
    }
}

int main()
{
    #if 0
    vector<int> colors;
    GenerateColors( colors, COLOR_NUM );
    cout << "before Sorting " << endl;
    PrintColors( colors );
    int swaps = sortColors(colors);
    cout << "it takes " << swaps << " swaps to sort using regular sorting  " << endl;
    swaps = SortColorsMinSwaps( colors );
    cout << "it takes " << swaps << " swaps to sort using min swap sorting  " << endl;
    #endif 
    int swaps;
    vector<int> test{0,0,0,1,1,1,2,2};
    swaps = sortColors( test );
    cout << "it takes " << swaps << " swaps to sort using min swap sorting  " << endl;
}