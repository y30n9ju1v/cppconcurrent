#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex       m1, m2, m3;
std::timed_mutex tm1, tm2, tm3;

int main()
{
    // 핵심 1. 생성 방법.
    std::unique_lock<std::mutex> u1;    // 아직 뮤텍스 연결안됨
    std::unique_lock<std::mutex> u2(m1);// 생성자에서 m.lock()                 

    std::unique_lock<std::mutex> u3(m2, std::try_to_lock);
                                        // 생성자에서 m.try_lock()
                                        // 획득 못해도 대기 안함.
                                        // 획득여부는 아래 코드로 조사
    if (u3.owns_lock())
        std::cout << "acquire lock" << std::endl;
    else
        std::cout << "fail to lock" << std::endl;


    // 핵심 2. 이미 lock 한 mutex 의 unlock 만 관리할때
    m3.lock(); // 이미 획득
    std::unique_lock<std::mutex> u4(m3, std::adopt_lock);   


    // 핵심 3. mutex는 연결하지만 lock 은 나중에.
    std::unique_lock<std::timed_mutex> u5(tm1, std::defer_lock);
    auto ret = u5.try_lock_for(2s);


    // 핵심 4. timed_lock 사용시 chrono 시간도 전달가능..
    std::unique_lock<std::timed_mutex> u6(tm2, 2s);  // tm2.try_lock_for() 사용
    std::unique_lock<std::timed_mutex> u7(tm3, std::chrono::steady_clock::now() + 2s);
    // tm3.try_lock_until() 사용
}
