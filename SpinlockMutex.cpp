#include <atomic>
#include <iostream>
#include <thread>
using namespace std;
/*
 The following code uses atomic to implement a spinlock 
 */

class Spinlock {
    std::atomic_flag  flag;
public:
    Spinlock() : flag(ATOMIC_FLAG_INIT) {}
    void lock() {
        while ( flag.test_and_set() );
    }

    void unlock(){
        flag.clear();
    }
};

Spinlock spin;

void workthread()
{
    spin.lock();
    cout << "The work thread has acquired the spinlock " << endl;
    spin.unlock();
}

int main()
{
    std::thread t1(workthread);
    std::thread t2(workthread);

    t1.join();
    t2.join();
}