#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

// 아래 코드는 "mutex" 로 동기화 자원의 동시접근을 막는 코드 입니다.

// 단점 : 생산자가 시간이 걸리는데(10ms) 
//       생산하기 전에 소비자가 소비(쓰레기값 -1)를 하게 됩니다.

std::mutex m;
int shared_data = -1; // 쓰레기값

void consumer()
{
    std::lock_guard<std::mutex> lg(m);
    std::cout << "consume : " << shared_data << std::endl;
}
void producer()
{
    std::this_thread::sleep_for(10ms);
    std::lock_guard<std::mutex> lg(m);
    shared_data = 100;
    std::cout << "produce : " << shared_data << std::endl;
}
int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join(); 
    t2.join();
}