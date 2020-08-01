#include <iostream> 
#include <memory>
#include <utility>

using namespace std;

#if 0
void foo( int z )
{
    for ( int i = 0; i < z; i++ )
        cout << "i == " << i << endl;
}

class callable_object {
    void operator() ( int x )
    {
        for ( int i = 0; i <  x; i++ )
        {
            cout << "i==" << i << endl;
        }
    }
};

template< class T, class U >
class A {
    T x;
    U y;
    static int count;
};

class B {
    static int a; 
};

int main()
{
    unique_ptr<int> valuePtr(new int(15));
    unique_ptr<int> valuePtrNow(move(valuePtr));
    cout << "ValuePtrNow = " << *valuePtrNow;
    cout << "Has valuePtr an associated object ? " << boolalpha << static_cast<bool>(valuePtr) << '\n';
    B b;
    cout << "sizeof(b) is " << sizeof(b) << endl;

}
#endif 

#if 0
struct Object{
    unsigned char x, y, z, w;
};

int main(){
    Object obj;
    obj.x = 0x11;
    obj.y = 0x22;
    obj.z = 0x33;
    obj.w = 0x44;
    char* p = reinterpret_cast<char*> (&obj);
    for(int i=0; i<4; i++){
        printf("%0x\n",*((unsigned short*)++p));
    }
    return 0;
}
#endif

class TrackedObject{
    struct Position{
        int x;
        int y;
    };
    Position p;
    const int id;
    void display(){
        cout << id <<" "<< p.x << " " << p.y << endl;
    }
};
struct Car: TrackedObject{
    int color;
};
void doStuff(const Car &theCar){
    theCar.display();
}
int main(){
    Car c;
    c.id = 9;
    c.Position = (100,200);
    c.color = 1;
    doStuff(c);
}