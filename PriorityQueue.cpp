// The file tests the c++ priority queue data structure
// Definition:
//  A priority queue is a container adaptor that provides constant time lookup of the largest 
//  (by default) element, at the expense of logarithmic insertion and extraction.
//  A user-provided Compare can be supplied to change the ordering, e.g. using std::greater<T> 
//  would cause the smallest element to appear as the top().
// Note that the Compare parameter is defined such that it returns true if its first argument 
// comes before its second argument in a weak ordering. But because the priority queue outputs 
// largest elements first, the elements that "come before" are actually output last. 
// That is, the front of the queue contains the "last" element according to the weak ordering 
// imposed by Compare.

// Return true means come before, and the element comes before will output last....


#include <queue>
#include <vector>
#include <iostream>
#include <functional>
#include <utility>

using namespace std;

using my_pair_t = pair<size_t,bool>;
using my_container_t = vector<my_pair_t>;

#if 0
// this main test various priority queue constructors
int main()
{
    priority_queue<int> pq;
    pq.push(5);
    cout << pq.size() << endl;

    priority_queue<int> pq2(pq);
    cout << pq2.size() << endl;

    vector<int> vec = {3,1,4,1,5};
    priority_queue<int> pq3(less<int>(),vec);
    cout << pq3.size() << endl;
}
#endif 

#if 0
// this main test using custom compare 
int main()
{
    auto my_comp = 
        [] (const my_pair_t &e1, const my_pair_t& e2) 
        {
            return e1.first > e2.first;
        };
    priority_queue<my_pair_t,my_container_t,decltype(my_comp)> pq(my_comp);
    pq.push(make_pair(5,true));
    pq.push(make_pair(3,false));
    pq.push(make_pair(7,true));
    cout << boolalpha;
    while ( !pq.empty()) 
    {
        const auto& p = pq.top();
        cout << p.first <<" " << p.second << endl;
        pq.pop();
    }
}
#endif

template<typename T> void print_queue( T& q ){
    while( !q.empty() )
    {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
}

int main()
{
    priority_queue<int> q;
    for ( int n : {1,8,5,6,3,4,0,9,7,2} )
        q.push(n);
    print_queue( q );

    priority_queue<int,vector<int>, greater<int> > q2;
    for ( int n : {1,8,5,6,3,4,0,9,7,2} )
        q2.push( n );
    print_queue( q2 );

    // Using lambda to compare elements
    auto cmp = [](int left, int right) {return (left ^ 1) < (right ^ 1);};
    priority_queue<int,vector<int>,decltype(cmp)> q3(cmp);

    for ( int n : {1,8,5,6,3,4,0,9,7,2} )
        q3.push( n );
    print_queue(q3);


}