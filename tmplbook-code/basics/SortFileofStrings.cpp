// This is a very interesting and elegant solution to sort and remove duplicate from a file containing strings
#include <iostream> 
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;
#if 0
int main()
{
    string from, to;
    cin >> from >> to; 
    ifstream is {from};
    ofstream os {to};
    set<string> b{std::istream_iterator<string>{is},std::istream_iterator<string>{}};
    copy( b.begin(), b.end(), ostream_iterator<string>{os,"\n"});
    
    return !is.eof() || !os;
}
#endif 
// The following is a decoupled version which is easier to understand

int main()
{

    string from, to;
    cin >> from >> to;
    ifstream is {from};
    istream_iterator<string> ii{is};
    istream_iterator<string> eos{};
    ofstream os {to};
    ostream_iterator<string> oo {os,"\n"};
    vector<string> b{ii,eos};
    sort(b.begin(),b.end());
    unique_copy(b.begin(),b.end(),oo);

    return !is.eof() || !os;
}