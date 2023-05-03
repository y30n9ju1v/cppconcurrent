#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <semaphore>
using namespace std::literals;

std::mutex m; // 자원의 독점 - 
              // 주어진 구간을 한개의 스레드만 통과 할수 있습니다.

void Download(const std::string& name)
{
    m.lock();

    for (int i = 0; i < 100; i++)
    {
        std::cout << name;
        std::this_thread::sleep_for(30ms);
    }
    
    m.unlock();
}

int main()
{
    std::thread t1(Download, "1");
    std::thread t2(Download, "2");
    std::thread t3(Download, "3");
    std::thread t4(Download, "4");
    std::thread t5(Download, "5");

    t1.join();    t2.join();
    t3.join();    t4.join();
    t5.join();
}