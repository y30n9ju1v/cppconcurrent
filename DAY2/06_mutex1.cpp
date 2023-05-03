#include <iostream>
#include <thread>
#include <chrono>
#include <string_view>
#include <mutex>
using namespace std::literals;


std::mutex m;   // 자원을 독점할때 사용하는 도구
                // 오직 한개의 스레드만이 뮤텍스를 획득할수 있다.

void delay() { std::this_thread::sleep_for(20ms); }

void foo(const std::string& name)
{
//  int x = 0;  // 스레드 별도 따로 생성됨.
                // 항상 안전하다.!

    static int x = 0;  // 모든 스레드가 공유하는 공유 자원

    for (int i = 0; i < 10; i++)
    {
        m.lock();
        //--------------------------------
        x = 100;   delay();
        x = x + 1; delay();
        std::cout << name << " : " << x << std::endl; delay();
        //-------------------------------
        m.unlock();
    }
}

int main()
{
    std::thread t1(foo, "A");
    std::thread t2(foo, "\tB");
    t1.join();
    t2.join();
}



