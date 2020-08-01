// This small program tests the factory method design pattern 

#include <iostream>
#include <memory>       // smart pointers 
using namespace std;

class Base {
public:
    Base() = default;
    virtual ~Base() = default;
    virtual auto getType() const -> string {
        return "Base";
    }
    void showType() {
        cout << "Class type = " << this->getType() << endl;
    }
};

class DerivedA : public Base {
public:
    DerivedA() {};
    auto getType() const -> string {
        return "DerivedA";
    }
};

class DerivedB : public Base {
public:
    DerivedB() {}
    auto getType() const -> string {
        return "DerivedB";
    }
};

// use a factory function instead of a factory method 
auto simpleFactory( const string &name)  -> unique_ptr<Base> {
    if ( name == "Base" )
        return make_unique<Base>();
    if ( name == "DerivedA" )
        return make_unique<DerivedA>();
    if ( name == "DerivedB" )
        return make_unique<DerivedB>();
    return nullptr;
}

int main()
{
    auto base = simpleFactory("Base");
    if ( base )
        puts("A base object was created !");
    base->showType();
}