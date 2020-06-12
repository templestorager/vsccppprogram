#include <cstdio>
#include <iostream>
using namespace std;

class c1 {
    int i = 0; 
public:
    void setvalue( const int &value ) { 
        i = value;
    }
    int getvalue() { return i; }
    int getvalue() const { return i;}
};

int main()
{
    const int i = 0x27;
    c1 o1; 
    o1.setvalue( i );
    const c1 o2 = o1;
    cout << "value is " << o1.getvalue() << endl;
    return 0;
}