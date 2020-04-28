// This file reveals the memory layout of class instances having virtual functions 
#include <iostream>

using namespace std;

#if 0
class Base {
public:
    virtual void f() { cout << "Base::f" << endl;}
    virtual void g() { cout << "Base::g" << endl;}
    virtual void h() { cout << "Base::h" << endl;}
};

int main()
{
    typedef void (*Fun) (void);
    Base b;
    Fun pFun = nullptr;
    cout << "The address of virtual function table " << (int*)&b << endl;
    cout << " The address of the first virtual funciton " << (int*)*(int*)(&b) << endl;

    // call the first virtual function 
    pFun = (Fun)*((int*)*(int*)(&b));
    pFun();
}
#endif

#if 0
class Trivial {
public:
    Trivial(){}
    void method() 
    {
        printf("method in class trivial\n");
    }
};

int main()
{
    Trivial t;
    t.method();
}

#endif

#if 0
// The following code test the Base and derived 
class Base{
public:
    Base(){
        printf("%d\n",a);
    }
private:
    int a = 128;
};

class Derived: public Base {
public:
    Derived(){
        printf("%d\n",b);
    }
private:
    int b = 256;
};

int main()
{
    Derived *m = new Derived();
}
#endif

#if 1
// The following code tests the virtual table 
class Base {
public:
    virtual ~Base(){}
    virtual void method() = 0;
};

class Derived : public Base {
public:
    virtual ~Derived(){}
    void method(){ cout << "method in Derived" << endl;}
};

int main()
{
    Base *m = new Derived();
    long ***mVtable = (long ***) &m;
    cout << "Address of m is: " << hex << (void*)&m << endl;
    cout << "Derived VTABLE: " << hex <<  **mVtable << endl;
    cout << "First entry of Derived VTABLE: " << hex << (void*)mVtable[0][0][0] << endl;
    cout << "Second entry of Derived VTABLE: " << hex << (void*)mVtable[0][0][1] << endl;
    cout << "Third entry of Derived VTABLE: " << hex << (void*)mVtable[0][0][2] << endl;
    // cout << "Address of FCT: " << hex << (void*) &assignableFct1;
    // mVtable[0][0][2] = (void*)(mVtable[0][0][0] + 8);
    
    delete m;
}
#endif