// This utility functions plays with the iterators of containters 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;

void Vector_Iterator()
{
    cout << "Vector Interators " << endl;
    vector<int> vect;
    for ( int cnt = 0; cnt < 6; cnt++ )
        vect.push_back( cnt );
    vector<int>::reverse_iterator it = vect.rbegin();
    while ( it != vect.rend() )
    {
        cout << *it << " " ;
        it++;
    }
    cout << endl;
}

int main()
{
    Vector_Iterator();
}