#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

//std::mutex m;   // 1. m.lock()      : 획득할때 까지 대기
                  // 2. m.try_lock()  : 획득하지 못하면 false

std::timed_mutex m; // 위 2개 외에
                    // m.try_lock_for(시간)
                    // m.try_lock_until(시간)

int share_data = 0;

void foo()
{
    //m.lock();
    //if ( m.try_lock() )
    if ( m.try_lock_for(3s) )
    {
        share_data = 100;
        std::cout << "using share_data" << std::endl;
        std::this_thread::sleep_for(3s);
        m.unlock();
    }
    else
    {
        std::cout << "뮤텍스 획득 실패" << std::endl;
    }
}
int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}

// C++ 표준 뮤텍스는 6개 입니다.
// std::mutex,       std::recursive_mutex,       std::shared_mutex(C++17)
// std::timed_mutex, std::timed_recursive_mutex, std::timed_shared_mutex(C++17)


