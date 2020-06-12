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

#if 0
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

#if 0

// Command to look at the memory layout of class
// clang -cc1 -fdump-record-layouts VirtualFunction.cpp
class Base {
    int Base_data;
public:
   virtual void Greeting() {
        cout << "Greetings from Base (100) " << endl;
    }
};

class Base2 {
    int Base2_data;
public:
    virtual void Greeting() {
        cout << "Greetings from Base2 (300) " << endl;
    }
};

class Derived : public Base {
    int Derived_data;
public:
    void Greeting() {
        cout << "Greetings from Derived (200) " << endl;
    }
};

class Derived3 : public Base2, public Base
{
    int Derived3_data;
public:
    void Greeting() {
        cout << "Greetings from Derived3 (400) " << endl;
    }
};

void Print( Base *pBase )
{
    pBase->Greeting();
}

void Print2 ( Base2 *pDerived3 )
{
    pDerived3->Greeting();
}

int main()
{
    Base *pBase = new Derived;
    pBase->Greeting();
    Print( pBase );
    Base *pB2 = new Derived3;
    pB2->Greeting();
    Print( pB2 );
    Base2 *pB3 = new Derived3;
    pB3->Greeting();
    Print2( pB3 );
}
#endif 

#if 0
class Parent {
    int Parent_data;
public:
    virtual void Foo() {}
    virtual void FooNotOverriden() {};
};

class Derived : public Parent {
    int Derived_data;
public:
    void Foo() override {}
};

void PauseBreak()
{
    cout << "Line for breakpoint" << endl;
}
int main()
{
    Parent p1, p2;
    Derived d1, d2;
    cout << "Done " << endl;
}
#endif 

class Mother {
    int Mother_data;
public:
    virtual void MotherFoo() {
        cout << "MotherFoo in Mother" << endl;
    }
    virtual void MotherMethod2() {
        cout << "Mother shouting another way " << endl;
    }
};

class Father {
    int Father_data;
public:
    virtual void FatherFoo() {
        cout << "FatherFoo in Father class" << endl;
    }
    virtual void FatherMethod2() {
        cout << "Father shouting another way " << endl;
    }
};

class Son : public Father, public Mother {
    int Son_data;
public:
    virtual void FatherFoo () override {
        cout << " FatherFoo in Son " << endl;
    }
    virtual void MotherFoo() override {
        cout << " MotherFoo in Son " << endl;
    }
};

void PrintFatherFoo( Father *pFather )
{
    pFather->FatherFoo();
}

void PrintfMotherFoo( Mother *pMother )
{
    pMother->MotherFoo();
}

int main()
{
    Son *ps = new Son;
    ps->MotherFoo();
    PrintfMotherFoo( ps );
    ps->FatherFoo();
    PrintFatherFoo( ps );   
}