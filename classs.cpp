#include <cstdio>
#include <sstream>
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

class c2 {
    int a;
public:
    c2(){cout<<"C2 Constructor " << endl;}
    c2( int x) : a(x) {}
    void fun() { cout <<" Funct " << endl;}
    void fun2() { cout <<" Funct " << endl;}
};

void swap_limb( uint8_t &val )
{
    val = ((val&0xF) << 4) | ((val>>4) & 0xF);
}
#if 1
int main()
{
    const int i = 0x27;
    c1 o1; 
    o1.setvalue( i );
    const c1 o2 = o1;
    cout << "value is " << o1.getvalue() << endl;
    c2 o3;
    cout << "sizeof(o3) is " << sizeof(o3) << endl;
    o3.fun();
    uint8_t val = 0x12;
    printf("val = %x\n",val);
    cout << "Before swap val = " << std::hex << val << endl;
    swap_limb(val);
    cout << "After swap val = " << std::hex << val << endl;
    printf("val = %x\n",val);

    return 0;
}
#endif

#if 0
int main()
{
    uint8_t val = 42;
    std::cout << "The number 42 in octal:   " << std::oct << val << '\n'
              << "The number 42 in decimal: " << std::dec << val << '\n'
              << "The number 42 in hex:     " << std::hex << val << '\n';
    int n;
    std::istringstream("2A") >> std::hex >> n;
    std::cout << std::dec << "Parsing \"2A\" as hex gives " << n << '\n';
    // the output base is sticky until changed
    std::cout << std::hex << "42 as hex gives " << 42
        << " and 21 as hex gives " << 21 << '\n';
}
#endif