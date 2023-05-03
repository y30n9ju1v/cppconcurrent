#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

// 1. std::once_flag 타입의 변수를 전역적으로 한개 선언
std::once_flag flag;

void init(int a, double d)
{
    std::cout << "init" << std::endl;
    std::this_thread::sleep_for(2s);
}

void foo()
{
    std::cout << "start foo" << std::endl;
    
    // 2. init() 호출시 직접 호출하지 말고 아래 처럼 하세요
    // init(10, 3.4); // 스레드당 한번씩 호출

    std::call_once(flag, init, 10, 3.4); // 최초에 1회만 호출

    std::cout << "finish foo" << std::endl;
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}



