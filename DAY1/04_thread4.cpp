#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

// 핵심 : 스레드 ID 얻기

void foo()
{
    // 핵심 : 자기자신의 스레드 ID 얻기
    std::cout << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::thread t(&foo);
    
    std::this_thread::sleep_for(1s);

    // 자신(주스레드)가 생성한 새로운 스레드의 ID 얻기
    std::thread::id tid = t.get_id();
    
    std::cout << "created thread id : " << tid << std::endl;

    t.join();
}

