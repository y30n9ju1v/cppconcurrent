#include <iostream>
#include <thread>
#include <atomic>

//long x = 0; // 일반 전역변수. ++ 등의 연산이 멀티스레드에서
            // 안전하지 않습니다.

std::atomic<long> x = 0; // ++등의 연산이 멀티스레드에 안전

void foo()
{
    for (int i = 0; i < 100000; ++i)
    {
//      ++x; // x.operator++() 호출
             // atomic1.cpp 와 같은 CPU 명령 사용.

//      x.fetch_add(1);
        x.fetch_add(1, std::memory_order_relaxed);  
                        // => 위 코드보다 약간 더 빠를수 있습니다.
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    std::thread t3(foo);
    t1.join();
    t2.join();
    t3.join();
    std::cout << x << std::endl;
}
