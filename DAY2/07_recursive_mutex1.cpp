#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

//std::mutex m;   // 소유자라도 한번만 lock 가능

std::recursive_mutex m; // 뮤텍스 소유자가 여러번 lock 가능
                        // 단, unlock()도 동일 횟수 만큼해야 한다.
                        
int share_data = 0;

void foo()
{
    std::cout << "wait mutex" << std::endl;

    m.lock();
    m.lock(); // mutex 소유자가 다시 한번 lock

    share_data = 100;
    std::cout << "using share_data" << std::endl;
    m.unlock();
    m.unlock();
}


int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}




