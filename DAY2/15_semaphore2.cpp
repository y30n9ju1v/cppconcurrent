#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <semaphore>
using namespace std::literals;

// 세마 포어 ( C++20 부터 지원됩니다.)
// => 주어진 구간을 N개 스레드가 통과 가능

// 템플릿 인자 : 최대 카운트
// 생성자 인자 : 현재 카운트

// 규칙 : 0 <= 현재 카운트 <= 최대 카운트

std::counting_semaphore<3> sem(3);

void Download(const std::string& name)
{
    sem.acquire(); // if ( sem.count == 0 )
                    //   대기
                    // else 
                    //   (--sem.count); 통과

    for (int i = 0; i < 100; i++)
    {
        std::cout << name;
        std::this_thread::sleep_for(30ms);
    }

    sem.release(); // sem.counter += 1
}



int main()
{
    std::thread t1(Download, "1");
    std::thread t2(Download, "2");
    std::thread t3(Download, "3");
    std::thread t4(Download, "4");
    std::thread t5(Download, "5");

    std::this_thread::sleep_for(2s);
    std::cout << "\n main \n";

    //sem.release();
    //sem.release(2);

    t1.join();    t2.join();
    t3.join();    t4.join();
    t5.join();
}