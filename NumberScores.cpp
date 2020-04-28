// Problem Description
/*
    Find the score for each number, you got points for:
    +1 for number divisible by 7
    +2 for even digits
    +4 for each 9
    +5 for 2 consecutive 1 and +5 for each consecutive followine one
    +N2 for every continous sequnce of the form 123 or 4567 of length N

    e.g. If the number is 11129 you get:

    5+5 points for conseutive 1s,
    2 points for an even digit(2)
    1+1+2^2+1 for the increasing sequence of lengths 1,1,2, 1
    0 points for divisibility by 7
    4 points for the 9
*/

#include <stack>
#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

int rulediv7( int num )
{
    if ( num % 7 == 0 )
        return 1;
    else
    {
        return 0;
    }
}

int evenruleand9( int num )
{
    int score = 0;
    while ( num ) 
    {
        if ( (num % 10) % 2 == 0 )
            score += 2;
        if ( num % 10 == 9 )
            score += 4;
        num /= 10;
    }
    return score;
}

int calconsecutive1( int num )
{
    stack<int> s;
    int score = 0;
    int last_num = -1, num1 = 0;
    while ( num )
    {
        s.push(num%10);
        num /= 10;
    }
    if ( s.empty() ) 
        return 0;
    while ( !s.empty() )
    {
        if ( s.top() == 1 )
        {
            if ( last_num == -1 )
            {
                num1 = 1;
                last_num = 1;
            }
            else if ( last_num == 1 )
            {
                if( ++num1 >= 2 )
                    score += 5;
            }
        }
        else {
            num1 = 0;
        }
        s.pop();
    }

    return score;
}

int seqlenrule( int num )
{
    stack<int> s;
    int score = 0, seqlen = 0, num1 = 0;
    int last_num = -1;
    while( num )
    {
        s.push(num%10);
        num /= 10;
    }
    if ( s.empty() )
        return 0;
    while( !s.empty() )
    {
        int tmp = s.top();
        s.pop();
        if ( last_num == -1 )
        {
            seqlen = 1;
            last_num = tmp;
        }
        else if ( tmp == last_num + 1 )
        {
            seqlen++;
            last_num = tmp;
        } else 
        {
            score += seqlen * seqlen;
            last_num = tmp;
            seqlen = 1;
        }
    }

    score += seqlen * seqlen;
    return score;
}

#if 0
int main()
{
    int num = 11129;
    stack<int> digits;
    int scores = 0;
    bool first_num = true;
    int num1 = 0, seqlen = 0, last_num = -1;
    if ( num % 7 == 0 )
        scores += 1;
    int tmp = num;
    while ( tmp )
    {
        digits.push( tmp%10 );
        tmp /= 10;
    }
    while( !digits.empty() )
    {
        int val = digits.top();
        if ( val % 2 == 0 )
            scores += 2;
        if ( val == 9 )
            scores += 4;
        if ( first_num )
        {
            last_num = val;
            seqlen = 1;
        }
        switch (val)
        {
        case 1:
            if ( last_num == 1 )
            {
                num1++;
                if ( num1 >= 2 )
                    scores += 5;
            }
            else 
            {
                num1 = 0;
            }
            // intentional fall through 
        default:
            if ( !first_num )
            {
                if ( val == last_num+1 )
                {
                    seqlen++;
                }
                else
                {
                    scores += seqlen * seqlen;
                    seqlen = 1;
                }
            }
        }
        first_num = false;
        last_num = val;
        digits.pop();
    }
    scores += seqlen * seqlen;
    cout << " The number score of " << num << " is " << scores << endl;
    cout << " The number score of " << num << " is " << rulediv7(num) + evenruleand9(num) + seqlenrule(num) + calconsecutive1(num) << endl;
    cout << " Consecutive 1 score is " << num << "(" << calconsecutive1(num) <<")" << endl;
}

#endif

#if 0
int main()
{
    int num = 6732;
    stack<int> digits;
    int scores = 0;
    bool first_num = true;
    int num1 = 0, seqlen = 0, last_num;
    if ( num % 3 == 0 )
        scores += 2;
    int tmp = num;
    while ( tmp )
    {
        digits.push( tmp%10 );
        tmp /= 10;
    }
    while( !digits.empty() )
    {
        int val = digits.top();
        if ( val % 2 == 0 )
            scores += 4;
        if ( val == 7 )
            scores += 1;
        if ( first_num )
        {
            last_num = val;
            seqlen = 1;
        }
        switch (val)
        {
        case 5:
            if ( last_num == 1 )
            {
                num1++;
                if ( num1 >= 2 )
                    scores += 3;
            }
            else 
            {
                num1 = 0;
            }
            // intentional fall through 
        default:
            if ( !first_num )
            {
                if ( val == last_num-1 )
                {
                    seqlen++;
                }
                else
                {
                    scores += seqlen * seqlen;
                    seqlen = 1;
                }
            }
        }
        first_num = false;
        last_num = val;
        digits.pop();
    }

    scores += seqlen * seqlen;

    cout << " The number score of " << num << " is " << scores << endl;
}
#endif

// The contribution rules of individual digit 
// Digit   Score 
//   7       1
//  even     4
//  num % 3  2
int CalDigitScore( const int num )
{
    int score = 0, val, tmp = num;
    if ( tmp % 3 == 0 )
        score += 2;
    while(tmp)
    {
        val = tmp % 10;
        if ( val == 7 )
            score += 1;
        if ( val % 2 == 0 )
            score += 4;
        tmp /= 10;
    }

    return score;
}

// Two consecutive results in x, one additional x
int CalConsecutiveScore( const vector<int> digits,  int target, int inc )
{
    int score = 0, i, j;
    if ( digits.size() == 0 )
        return score;
    for ( i = 0; i < digits.size(); i++ )
    {
        if ( digits[i] != target )
            continue;
        int len = 1;
        for ( j = i+1; j < digits.size(); j++ )
        {
            if ( digits[j] == digits[i] )
            {
                len++;
            }
            else
            {
                if ( len >= 2 )
                {
                    score += (len-1) * inc;
                }
                break;
            }
        }
        if ( j == digits.size() && len >= 2 )
        {
            score += (len-1) * inc;
        }
    }

    return score;
}

// Two consecutive results in x, one additional x
int CalConsecutiveScoreSame( const vector<int> digits,  int target, int inc )
{
    int score = 0,i;
    int len;
    if ( digits.size() == 0 )
        return score;
    for ( i = 0; i < digits.size(); i++ )
    {
        if ( digits[i] == target )
        {
            len = 0;
            while ( i < digits.size() )
            {
                if ( digits[i] == target ){
                    if ( ++len >= 2 )
                        score += inc;
                }
                else
                {
                    break;
                }
                i++;
            }
        }
    }

    return score;
}


int CalSeqScore( const vector<int> digits, bool dec )
{
    int score = 0, curlen;
    if ( digits.size() == 0 )
        return score;
    int curdigit = digits[0]; 
    curlen = 1;
    for ( int i = 1; i < digits.size(); i++ )
    {
        if ( digits[i] == (dec ? curdigit - 1 : curdigit + 1)  )
        {
            curlen++;
        }
        else
        {
            score += curlen * curlen;
            curlen = 1;
        }
    }
    score += curlen * curlen;
    return score;
}

int AcquireReleaseLock()
{
    vector<string> events{"ACQUIRE 364","ACQUIRE 84","RELEASE 364","RELEASE 84"};
    string action;
    long lockid;
    if ( events.size() == 0 )
        return 0;
    set<int>  lockshold_set;
    stack<int> lockshold_st; 
    size_t space_pos;
    for ( int i = 0; i < events.size(); i++ )
    {
        space_pos = events[i].find(' ');
        action = events[i].substr(0,(int)space_pos);
        lockid = stol(events[i].substr(space_pos+1));
        cout << "Action is " << action << " Lockid is " << lockid << endl;
        if ( action == "ACQUIRE" )
        {
            if ( lockshold_set.count(lockid) )
            {
                return i+1;
            }
            lockshold_st.push(lockid);
            lockshold_set.insert(lockid);
        }
        else 
        {
            if ( lockshold_st.top() != lockid )
                return i+1;
            lockshold_st.pop();
            lockshold_set.erase(lockid);
        }
    }
    return lockshold_st.empty() ? 0 : events.size() + 1;
}

int main()
{
    #if 0
    int num = 2222;
    vector<int> digits;
    int tmp = num;
    while ( tmp )
    {
        digits.insert(digits.begin(),num % 10);
        tmp /= 10;
    }
    cout << "Score of individual digits is " << CalDigitScore(num) << endl;
    cout << "Score of consecutive is " << CalConsecutiveScore(digits,5,3) << endl;
    cout << "Score of consecutive is " << CalConsecutiveScoreSame(digits,2,6) << endl;
    cout << "Score of sequence is " << CalSeqScore(digits,true) << endl;
    cout << "Total score of " << num << " is " << CalSeqScore(digits,true) + CalConsecutiveScore(digits,5,3) + CalDigitScore(num) << endl;
    #endif 
    int res = AcquireReleaseLock();
    cout << "return value is " << res << endl;
}