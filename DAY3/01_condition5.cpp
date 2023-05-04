#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1;

// condition_varaible 코딩 관례
// => flag 변수와 함께 사용하는 것이 일반적인 관례 입니다.
std::condition_variable cv;

bool data_ready = false;
bool data_process = false;

void consumer()
{
    std::this_thread::sleep_for(10ms);
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul, []() { return data_ready; });

    std::cout << "consume : " << shared_data << std::endl;

    data_process = true;
    cv.notify_one();
}

void producer()
{
    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;
    }
    data_ready = true;
    cv.notify_one();

    // 소비자에게 읽어가라고 알려주었는데..
    // 정말 읽었는지 확인하고 싶다.!!
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul, []() { return data_process; });

    std::cout << "produce : data 처리 완료" << std::endl;
}


int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}