// Problem Description

#include <unordered_set>
#include <iostream>
using namespace std;

bool isHappyHelper( unordered_set<int>& s, int n )
{
    if ( s.count(n) )
        return false;
    int sum = 0; 
    s.insert(n);
    while(n)
    {
        sum += (n%10)*(n%10);
        n /= 10;
    }
    
    if ( sum == 1 )
        return true;
    else 
    {
        //s.insert(sum);
        return isHappyHelper(s,sum);
    }
}

bool isHappy(int n) {
    unordered_set<int> s;
    return isHappyHelper(s,n);
}

int main()
{
    int a = 19;
    bool res = isHappy(a);
}