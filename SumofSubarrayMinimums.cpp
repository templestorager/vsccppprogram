#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void ComputePrevLessIdxArray( vector<int> &PreviousLessIdx, const vector<int> &A )
{
    // IMS: increasing monotone stack 
    stack<int> ims;
    PreviousLessIdx.clear();
    for ( int i = 0; i < A.size(); i++ )
    {
        while ( !ims.empty() && A[ims.top()] >= A[i] )
            ims.pop();
        PreviousLessIdx.push_back( ims.empty() ? -1 : ims.top() );
        ims.push(i);
    }
}

void ComputeNextLessIdxArray( vector<int> &NextLessIdx, const vector<int> &A )
{
    stack<int> ims; 
    NextLessIdx.clear();
    NextLessIdx = vector<int>(A.size());
    for ( int i = A.size() - 1; i >= 0; i-- )
    {
        while( !ims.empty() && A[ims.top()] > A[i] )
        {
            ims.pop();
        }
        NextLessIdx[i] = ims.empty() ? A.size() : ims.top();
        ims.push(i);
    }
}

int sumSubarrayMins(vector<int>& A) 
{
    int sum = 0, M = 1000;
    int n = A.size();
    vector<int> left, right;
    if ( n == 0 )
        return sum;
    ComputePrevLessIdxArray(left,A);
    ComputeNextLessIdxArray(right,A);
    for ( int i = 0; i < n; i++ )
    {
        sum += (i-left[i]) * (right[i]-i) % M *A[i] % M;
        sum %= M;
    }
    
    return sum;
}

int main()
{
    vector<int> A{71,55,82,55};
    int sum = sumSubarrayMins(A);

    cout << "Sum = " << sum << endl;
}