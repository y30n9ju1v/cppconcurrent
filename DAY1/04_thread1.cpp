#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

void foo()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "foo : " << i << std::endl;
        std::this_thread::sleep_for(100ms);
    }
}
int main()
{
//  foo(); // 주 스레드가 그냥 실행

    // 핵심 1. 스레드를 생성하는 방법
    std::thread t(&foo);  // 이순간 스레드가 생성되어서 foo 실행
                          // 별도의 "start()" 같은 함수는 없습니다.

    // 핵심 2. 스레드를 생성한 경우 반드시 아래 2개중 한개를 해야 합니다.
    // join   : 스레드 종료시 까지 대기
    // detach : 스레드 분리(핸들 닫기)
    // 
//  t.join();  // 스레드 종료시까지 현재스레드(주스레드) 대기

    t.detach(); // 스레드 분리
                // 새로운 스레드에 관심없으므로 독립적으로 실행하라는것
                // 내부적으로 관리하던 스레드 핸들을 닫는 작업
    std::cout << "continue main" << std::endl;
}
