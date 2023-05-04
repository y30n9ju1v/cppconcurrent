#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// 1. 헤더 포함
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1; 

// 2. std::condition_variable 타입의 전역변수 생성
std::condition_variable cv;



void consumer()
{
    // 3. 소비자(신호대기)는 unique_lock 으로 뮤텍스 획득후
    //    신호를 대기 합니다.
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul);

    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{
    std::this_thread::sleep_for(10ms);
    {
        // 생산자는 계속 lock_guard 사용
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;
    }
    // 3. 생산이 끝나면 lock 을 풀고 신호를 주면 됩니다.
    cv.notify_one();
}


int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}