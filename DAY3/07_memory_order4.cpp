#include <thread>
#include <atomic>
#include <cassert>

std::atomic<int> data1 = 0;
std::atomic<int> data2 = 0;
std::atomic<int> flag = 0;

void foo()
{
    data1.store(100, std::memory_order_relaxed);
    data2.store(200, std::memory_order_relaxed);
//  flag.store(1, std::memory_order_relaxed);
        // => flag 의 동시 접근만 보장, 위 2줄이
        //    이코드의 아래 줄로 내려 올수도 있습니다.

    flag.store(1, std::memory_order_release);
        // => 이 코드의 위에 있는 코드의 결과는
        //    acquire 이후에는 반드시 적용되어야 한다.
}

void goo()
{
    if ( flag.load( std::memory_order_acquire) > 0)
    {
        assert(data1.load(std::memory_order_relaxed) == 100);
        assert(data2.load(std::memory_order_relaxed) == 200);
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(goo);
    t1.join(); t2.join();
}