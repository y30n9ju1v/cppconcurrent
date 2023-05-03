#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

// 시스템을 초기화 하는 함수
// => 아래 함수는 한번만 호출(초기화)하면 된다고 가정해 봅시다.
void init(int a, double d)
{
    std::cout << "init" << std::endl;
    std::this_thread::sleep_for(2s);
}
void foo()
{
    std::cout << "start foo" << std::endl;
    
    // 아래 처럼 직접 호출하면 스레드당 한번씩 init 함수가 호출됩니다.
    init(10, 3.4);    // 초기화

    std::cout << "finish foo" << std::endl;
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}



