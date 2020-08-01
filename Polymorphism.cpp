#include <iostream> 
#include <chrono>
using namespace std::chrono;
using namespace std;

#if 0
class Animal {
public:
    void Sound(){ cout << " Animal Sound " << endl;}
};

class Cow : public Animal {
public:
    void Sound() { cout << " Cow Sound " << endl; }
};

class Elephant : public Animal {
public:
    void Sound() { cout << " Elephant Sound " << endl; }
};

class Horse : public Animal {
public:
    void Sound() { cout << " Horse Sound " << endl; }
};

int main()
{
    // Cow, Elephant, Horse 
    Animal *animals[3];   
    animals[0] = new Cow; 
    animals[1] = new Elephant;
    animals[2] = new Horse; 
    for ( int i = 0; i < 3; i ++ )
    {
        animals[i]->Sound();
    }
}
#endif

#if 0
class NV_C {
    int a;
public:
    void MySize() 
    { 
        cout << " Non-virtual class size is " << sizeof(NV_C) << endl; 
    }
};

class Vir_C {
    int a;
public:
    virtual void MySize() 
    { 
        cout << " Virtual class size is " << sizeof(Vir_C) << endl; 
    }
};

int main()
{
    NV_C nvc;
    Vir_C vc;
    nvc.MySize();
    vc.MySize();
}
#endif 