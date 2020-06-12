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

#if 0
// The following code explores the virtual table memory layout in a multiple inheritance scenarios
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

class Uncle {
    virtual void UncleFoo() {
        cout << "UncleFoo in Father class" << endl;
    }
    virtual void UncleMethod2() {
        cout << "Uncle shouting another way " << endl;
    }
};

class Son : public Father, public Mother, public Uncle {
    int Son_data;
public:
    virtual void FatherFoo () override {
        cout << " FatherFoo in Son " << endl;
    }
    virtual void MotherFoo() override {
        cout << " MotherFoo in Son " << endl;
    }
    virtual void UncleFoo () override {
        cout << " UncleFoo in Son " << endl;
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
    Mother m1,m2;
    Father f1,f2;
    Uncle  u1,u2;
    Son *ps = new Son;
    ps->MotherFoo();
    PrintfMotherFoo( ps );
    ps->FatherFoo();
    PrintFatherFoo( ps );   
}

// Check the output seriously, you will get it .. 
/*
Starting program: /home/huststorager/Desktop/VisualStudioCodeSources/vsccppprogram/VirtualFunction 
(gdb) info vtbl m1
vtable for 'Mother' @ 0x400fc0 (subobject @ 0x7fffffffdca0):
[0]: 0x400b54 <Mother::MotherFoo()>
[1]: 0x400b80 <Mother::MotherMethod2()>
(gdb) info vtbl f1
vtable for 'Father' @ 0x400fa0 (subobject @ 0x7fffffffdcc0):
[0]: 0x400bac <Father::FatherFoo()>
[1]: 0x400bd8 <Father::FatherMethod2()>
(gdb) info vtbl f2
vtable for 'Father' @ 0x400fa0 (subobject @ 0x7fffffffdcd0):
[0]: 0x400bac <Father::FatherFoo()>
[1]: 0x400bd8 <Father::FatherMethod2()>
(gdb) info vtbl ps
vtable for 'Son' @ 0x400f10 (subobject @ 0x614c20):
[0]: 0x400c5c <Son::FatherFoo()>
[1]: 0x400bd8 <Father::FatherMethod2()>
[2]: 0x400c88 <Son::MotherFoo()>
[3]: 0x400cba <Son::UncleFoo()>

vtable for 'Mother' @ 0x400f40 (subobject @ 0x614c30):
[0]: 0x400cb3 <non-virtual thunk to Son::MotherFoo()>
[1]: 0x400b80 <Mother::MotherMethod2()>

vtable for 'Uncle' @ 0x400f60 (subobject @ 0x614c40):
[0]: 0x400ce5 <non-virtual thunk to Son::UncleFoo()>
[1]: 0x400c30 <Uncle::UncleMethod2()>
(gdb) 
*/
#endif 

#if 1
// The following code explore the case of virtual inheritance 
class GrandParent{
public:
    
};
#endif