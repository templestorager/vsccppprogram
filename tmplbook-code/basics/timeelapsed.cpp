#include <iostream> 
#include <thread>
using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();
    std::this_thread::sleep_for(milliseconds{20});
    auto end = high_resolution_clock::now();
    std::cout << duration_cast<nanoseconds>(end-start).count() << " nanoseconds passed\n";
}