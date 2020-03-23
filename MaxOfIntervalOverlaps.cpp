// Problem Description
/*
Consider a big party where a log register for guest’s entry and exit times is maintained. Find the time at which there are maximum guests in the party. Note that entries in register are not in any order.
Example :

Input: arrl[] = {1, 2, 9, 5, 5}
       exit[] = {4, 5, 12, 9, 12}
First guest in array arrives at 1 and leaves at 4, 
second guest arrives at 2 and leaves at 5, and so on.

Output: 5
There are maximum 3 guests at time 5.  
*/

#include <iostream>
#include <algorithm> 
#include <vector>
#include <string>

using namespace std;

void MaxOverlap(vector<int> &entry, vector<int>& exit )
{
    int people = entry.size();
    int max_entry_time = *max_element(entry.begin(),entry.end());
    int max_exit_time  = *max_element(exit.begin(),exit.end());
    int max_slot       = max(max_entry_time, max_exit_time);
    int day_guests[max_slot+2];        // 0 is not used, max_slot+1 is after the max exit time 

    memset(day_guests, 0, sizeof(day_guests) );
    int max_guests = INT_MIN, cur_guests = 0, max_time;
    for ( int i = 0; i < people; i++ )
    {
        day_guests[entry[i]]++;
        day_guests[exit[i]+1]--;
    }

    for ( int i = 0; i <= max_slot; i++ )
    {
        cur_guests += day_guests[i];
        if ( max_guests < cur_guests )
        {
            max_guests = cur_guests;
            max_time  = i;
        }
    }
    cout << "Maximum value is " <<max_guests<<" at time " <<max_time <<endl;

}

void FindMaxGuest( int arrl[], int leave[], int sz)
{
    sort( arrl, arrl+sz );
    sort( leave, leave+sz);
    int cur_guests = 1, max_guests = 1, max_time = arrl[0];
    int arrl_idx = 1, leave_idx = 0;
    while ( arrl_idx < sz && leave_idx < sz )
    {
        if ( arrl[arrl_idx] <= leave[leave_idx] )
        {
            cur_guests++;
            if ( cur_guests > max_guests )
            {
                max_guests = cur_guests;
                max_time   = arrl[arrl_idx];
            }
            arrl_idx++;
        }
        else
        {
            cur_guests--;
            leave_idx++;
        }
    }
    cout << "Maximum Number of Guests = " << max_guests
         << " at time " << max_time << endl;
}

int main()
{
    int arrl[] = { 1, 2, 10, 5, 5 };
    int leave[] = { 4, 5, 12, 9, 12 };
    int sz = sizeof (arrl) / sizeof(arrl[0]);
    FindMaxGuest( arrl, leave, sz );
    // init vectors with arrays
    //MaxOverlap
    return 0;
}

