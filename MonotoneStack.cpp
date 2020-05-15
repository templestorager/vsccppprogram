// This program implements the monotone stack for a given array 
// Monotone stack can be used to find the previous less element (PLE) and next less element (NLE)
// Monotone stack can also be used to find the previous bigger element (PBE ) and next bigger element (NBE)
// Increasing stack is convenient for finding the first element less than the element on the left-side 
// Decreasing stack is convenient for finding the first element larger than the element on the left-side 
#include <iostream>
#include <vector> 
#include <stack>

using namespace std;

// This function returns previous less element array for a given array using an increasing monotone stack 
// Note the value for the last element is always -1 
// For example, given { 1, 4, 3, 7 }, the result is {-1,0,0,2}. 
// This function returns the index of the previous less element. If there is no previous less element, then it is -1
vector<int> FindPreviousLessElement( vector<int> &A )
{
    vector<int> PreviousLessElement;
    stack<int> s;
    for ( int i = 0; i < A.size(); i++ )
    {
        while ( !s.empty() && A[i] <= A[s.top()] )
            s.pop();
        PreviousLessElement.push_back( s.empty() ? -1 : s.top() );
        s.push(i);
    }
    return PreviousLessElement;
}

// This function returns next less element array for a given array using an increasing monotone stack 
vector<int> FindNextLessElement( vector<int> &A )
{
    vector<int> NextLessElement( A.size(),A.size() );
    stack<int> s;
    for ( int i = 0; i < A.size(); i++ )
    {
        while( !s.empty() && A[i] < A[s.top()] )
        {
            auto x = s.top();
            s.pop();
            NextLessElement[x] = i;
        }
        s.push(i);
    }

    return NextLessElement;
}

// This implements the same function as the above one, but starting from the end 
vector<int> FindNextLessElementReverse( vector<int> &A )
{
    vector<int> NextLessElement( A.size(), A.size() );
    stack<int> s;
    for ( int i = A.size() - 1; i >= 0; i-- )
    {
        while ( !s.empty() && A[i] <= A[s.top()] )
            s.pop();
        NextLessElement[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }

    return NextLessElement;
}

vector<int> FindPreviousLargeElement( vector<int> &A )
{
    vector<int> PreviousLargeElement;
    stack<int> s;
    for ( int i = 0; i < A.size(); i++ )
    {
        while ( !s.empty() && A[s.top()] <= A[i] )
            s.pop();
        PreviousLargeElement.push_back(s.empty() ? -1 : s.top());
        s.push(i);
    }

    return PreviousLargeElement;
}

vector<int> FindNextLargeElementReverse( vector<int> &A )
{
    vector<int> NextLargeElement(A.size());
    stack<int> s;
    for ( int i = A.size() - 1; i >= 0; i-- )
    {
        while( !s.empty() && A[i] >= A[s.top()] )
            s.pop();
        NextLargeElement[i] = s.empty() ? -1 :s.top();
        s.push(i);
    }

    return NextLargeElement;
}

vector<int> FindNextLargeElement( vector<int> &A )
{
    vector<int> NextLargeElement(A.size(),-1);
    stack<int> s;
    for ( int i = 0; i < A.size(); i++ )
    {
        while ( !s.empty() && A[i] > A[s.top()] )
        {
            auto top = s.top();
            s.pop();
            NextLargeElement[top] = i;
        }
        s.push(i);
    }
    return NextLargeElement;
}

void PrintVector( vector<int> &data )
{
    cout << "[ ";
    for ( int i = 0; i < data.size() - 1; i++ )
    {
        cout << data[i] << " " ;
    }
    if ( data.size() > 0 )
        cout << data[data.size()-1] << " ]" << endl;
    else 
        cout << " ]" << endl;
}

int main()
{
    vector<int> A{9,7,8,4};
    vector<int> res;
    res = FindPreviousLessElement( A );
    cout << "The previous less element array is " << endl;
    PrintVector( res );
    cout << endl;
    res = FindNextLessElement( A );
    cout << "The next less element array is " << endl;
    PrintVector( res );
    cout << endl;
    res = FindNextLessElementReverse( A );
    cout << "The next less element array (reverse) is " << endl;
    PrintVector( res );
    cout << endl;
    res = FindPreviousLargeElement( A );
    cout << "The previous large element array is " << endl;
    PrintVector( res );
    cout << endl;
    res = FindNextLargeElement( A );
    cout << "The Next large element array is " << endl;
    PrintVector( res );
    cout << endl;
    res = FindNextLargeElementReverse( A );
    cout << "The next large element array (reverse) is " << endl;
    PrintVector( res );
    cout << endl;

    return 0;
}