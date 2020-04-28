#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <future>
#include <condition_variable>
#include <chrono> 

using namespace std;

#if 0
volatile int counter(0);

mutex mtx;

void attempt_10k_increase () 
{
    for ( int i = 0; i < 10000; i++ )
    {
        if ( mtx.try_lock() )
        {
            ++counter;
            mtx.unlock();
        }
    }
}

int main()
{
    thread threads[10];
    for ( int i = 0; i < 10; i++ )
    {
        threads[i] = thread(attempt_10k_increase);
    }

    for ( auto & th : threads )
        th.join();
    cout << counter << " obtained locks times " << endl;
}
#endif

#if 0
void f(vector<int>& vec, int *f_return_val)
{
    cout << "Output from funciont f" << endl;
    cout << "[";
    for( int i = 0; i < vec.size()-1; i++ )
        cout << vec[i] << "(f)";
    cout << vec[vec.size()-1];
    cout << "]";
    *f_return_val = 0x1234;
    cout << endl;
}

struct F 
{
    vector<int> &loc_v;
    int *F_return_val;
    F(vector<int>& arg_v, int *F_res) : loc_v{arg_v}, F_return_val{F_res} {}
    void operator()()
    {
        cout << "output from function class " << endl;
        cout << "[";
        for( int i = 0; i < loc_v.size()-1; i++ )
            cout << loc_v[i] << "(F) ";
        cout << loc_v[loc_v.size()-1];
        cout << "]";
        *F_return_val = 0xFFFF;
    };
};

void foo( int i )
{
    cout << "foo_init" << endl;
}

void foo ( char *pc )
{
    cout << "foo_char *" << endl;
}

int main()
{
    int f_res, F_res;
    vector<int> data{1,2,3,4,5,6};
    thread t1{bind(f,data, &f_res)};
    thread t2{F(data,&F_res)};
    cout << "Main Thread Id is " << this_thread::get_id() << " and it's priority is " << endl;
    cout << "T1 Thread Id is " << t1.get_id() << " and it's priority is "  << endl;
    cout << "T2 Thread Id is " << t2.get_id() << " and it's priority is "  << endl;
    cout << " hardware concurrent is " << thread::hardware_concurrency() << endl;

    t1.join();
    t2.join();
    cout << "f_res = " << hex << f_res << "F_res = " << hex << F_res << endl;
    cout << endl;
    foo ( 0 );

    // 
    atomic<int> cnt{0};

    // namda function with "&" indicates the function (executed by a thread) can access variables  in the main thread
    auto f = [&]{cnt++;};
    cout << "Before incrementd by three threads count = " << cnt << endl;
    thread t_cnt1{f},t_cnt2{f},t_cnt3{f};
    t_cnt1.join();
    t_cnt2.join();
    t_cnt3.join();
    cout << "After incrementd by three threads count = " << cnt << endl;
}
#endif

#if 0
// this following code function demonstrates the deadlock case

void print()
{
    std::cout << "Critical section Thread_id is  " << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::mutex mutex1, mutex2;
    std::thread t1([&mutex1,&mutex2]{
        #if 0
        std::cout << "Acquiring First mutex...(t1)" << std::endl;
        mutex1.lock();
        print();
        std::cout << "Acuquring Second mutex...(t1)" << std::endl;
        mutex2.lock();
        print();
        mutex1.unlock();
        mutex2.unlock();
        #endif
        #if 0
        std::lock(mutex1,mutex2);
        std::lock_guard<std::mutex> lock1(mutex1,std::adopt_lock);
        std::lock_guard<std::mutex> lock2(mutex2,std::adopt_lock);
        print();
        #endif
        #if 0
        std::unique_lock<std::mutex> lock1(mutex1,std::defer_lock);
        std::unique_lock<std::mutex> lock2(mutex2,std::defer_lock);
        std::lock(lock1,lock2);
        #endif
        std::scoped_lock<std::mutex,std::mutex> lock(mutex1,mutex2);
        print();

    });

    std::thread t2([&mutex1,&mutex2]{
        #if 0
        std::cout << "Acquiring second mutex...(t2)" << std::endl;
        mutex2.lock();
        print();
        std::cout << "Acquiring First mutex...(t2)" << std::endl;
        mutex1.lock();
        print();
        mutex2.unlock();
        mutex1.unlock();
        #endif
        #if 0
        std::lock(mutex1,mutex2);
        std::lock_guard<std::mutex> lock1(mutex1,std::adopt_lock);
        std::lock_guard<std::mutex> lock2(mutex2,std::adopt_lock);
        print();
        #endif
        #if 0
        std::unique_lock<std::mutex> lock1(mutex1,std::defer_lock);
        std::unique_lock<std::mutex> lock2(mutex2,std::defer_lock);
        std::lock(lock2,lock1);
        #endif
        std::scoped_lock<std::mutex,std::mutex> lock(mutex1,mutex2);
        print();
    });
    t1.join();
    t2.join();
    return 0;
}
#endif


#if 0 
// The following code demonstrates the an example the synchronization between producer and consumer 
// or sender/receiver using mutex and conditional variable

std::mutex mutex1;
std::condition_variable cv;
bool ready = false;

void print()
{
    std::cout << "Waiting for other thread to signal ready!" << std::endl;
    std::unique_lock<std::mutex> lock(mutex1);
   // while (!ready )
    {
        cv.wait(lock,[](){ready == true;});
    }
    std::cout << "thread is executing now..." << std::endl;
}

void execute()
{
    std::cout << "Thread is ready to execute... " << std::endl;
    ready = true;
    cv.notify_all();
}

int main()
{
    std::thread t1(print);
    std::thread t2(print);
    std::thread t3(execute);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
#endif 

#if 0
// This following code illustrates using atomic class to realize lock and mutex 

class Atomic_counter 
{
public:
    std::atomic<int> n;
    std::mutex cout_m;
    Atomic_counter () : n(0) {}
    void increment() {
        std::lock_guard<std::mutex> lock_cout(cout_m);
        cout << "Increment 1 by thread " << std::this_thread::get_id() << endl;
        ++n;
    }
};

int main()
{
    Atomic_counter counter;
    std::thread t1([&counter]{
        for ( int i = 0; i < 100000; i++ ){
            counter.increment();
        }
    });
    std::thread t2([&counter]{
        for( int i = 0; i < 100000; i++ ){
            counter.increment();
        }
    });
    t1.join();
    t2.join();
    std::cout << counter.n << std::endl;
    return 0;
}

#endif


#if 0
// The following code illustrates the use of promise and future 
void func(std::promise<int> *p)
{
    int a = 10, b = 5;
    int result = a + b;
    std::cout << "From inside the Thread..." << std::endl;
    p->set_value(result);
}

int main()
{
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread th(func,&p);
    std::cout << f.get() << std::endl;
    th.join();

}
#endif

#if 0
// The following tests async usage 
// Note: std::async return a future object
int main()
{
    std::mutex cout_m;
    std::vector<std::future<int>> f;
    for ( int i = 0; i < 5; i++ )
    {
        f.push_back(std::async([&](int x){
            std::lock_guard<std::mutex> lock1(cout_m);
            cout << "Thread " << std::this_thread::get_id() << " calculating squared " << endl;
            return x*x;
        },i));
    }

    for ( auto &result : f )
    {
        std::cout << result.get() << std::endl;
    }
}
#endif

// The following code test throw exception in a thread 

#if 0
int func()
{
    throw std::runtime_error("An error has occurred!!");
}

int main()
{
    auto f = std::async(func);
    try {
        std::cout << "From main..." << f.get() << std::endl;
    }
    catch ( std::runtime_error const & error ){
        std::cout << "Caught Exception: " << error.what() << std::endl;
    }
}
#endif

#if 0
// the following code tests the use of lock_guard
int g_i = 0;
std::mutex g_i_mutex;

void safe_increment()
{
    const std::lock_guard<std::mutex> lock(g_i_mutex);
    ++g_i;
    std::cout << std::this_thread::get_id() << ":" << g_i << endl;
}

int main()
{
    std::cout << "main" << g_i << '\n';
    std::thread t1(safe_increment);
    std::thread t2(safe_increment);

    t1.join();
    t2.join();
    std::cout << "Main: " << g_i << '\n';
}
#endif

#if 0
// The following code tests conditional variable 
std::condition_variable cv;
std::mutex cv_m;
int i = 0;
bool done = false;

void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cout << "Waiting....\n";
    cv.wait(lk,[]{return i == 1; });
    std::cout << "...finished waiting. i == 1"  << endl;
    done = true;
}

void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Notifying falsely..." << endl;
    cv.notify_one();
    std::unique_lock<std::mutex> lk(cv_m);
    i = 1;
    while ( !done )
    {
        std::cout << "Notifying true change...\n",
        lk.unlock();
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        //lk.lock();
    }
}

int main()
{
    std:thread t1(waits), t2(signals);
    t1.join();
    t2.join();
}
#endif

#if 1
// The following code tests the cv used between a worker_thread and the main thread 
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
void worker_thread()
{
    // wait until main sends data 
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk,[]{return ready;});
    // after the wait, we own the lock 
    std::cout << "Worker thread is processing data \n";
    data += "after processing";

    // Send the data back to main
    processed = true;
    std::cout << "Work thread signals data processing completed \n";
    // Mannual unlocking is done before notifying to vaoid waking up 
    // the waiting thread only to block again.
    lk.unlock();
    cv.notify_one();
}

int main()
{
    std::thread worker(worker_thread);
    data = "Example data";
    {
        std::lock_guard<std::mutex> lk(m);      // note we have to put lock_guard in a scope to leverage its exceptional-safety 
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
    // wait for the worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk,[]{return processed;});
    }
    std::cout << "Back in the main(), data = " << data << endl;
    worker.join();
    return 0;
}
#endif