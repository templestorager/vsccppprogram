#include <iostream>
#include <vector>
using namespace std;

void sortColors(vector<int>& nums) 
{
    int r = 0, w = 0, b = 0;
    for ( int i = 0; i < nums.size(); i++ )
    {
        switch(nums[i])
        {
            case 0:
                r++;
                break;
            case 1:
                w++;
                break;
            case 2:
                b++;
                break;
            default :
                cout << " a = " << nums[i] << endl;
                
        }
    }
    nums.clear();
    while(r--)
        nums.push_back(0);
    while(w--)
        nums.push_back(1);
    while(b--)
        nums.push_back(2);      
}

void printvec(const vector<int> vals)
{
    int i;
    cout << "[";
    for ( i = 0; i < (int)vals.size() - 1; i++ )
    {
        cout << vals[i] << ",";
    }

    if ( i > 0 )
        cout << vals[i] <<"]" << endl;
    else
    {
        cout << "]" << endl;
    }
    
}

void sortColors3Way(vector<int>& nums) 
{
    int r_top = 0, w_top = 0, b_bottom = nums.size() - 1;
    while ( w_top <= b_bottom )
    {
        if ( nums[w_top] == 0 )
        {
            swap(nums[w_top],nums[r_top]);
            w_top++;
            r_top++;
        }
        else if ( nums[w_top] == 2 ) 
        {
            swap(nums[w_top],nums[b_bottom]);
            b_bottom--;
        }
        else
        {
            w_top++;
        }
    }
}

int main()
{
    vector<int> flags{2,0,1};
    cout << "Before sorting: " << endl;
    printvec(flags);
    sortColors3Way(flags);
    cout << "After sorting: " << endl;
    printvec(flags);
}

