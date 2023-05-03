#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

void goo()
{
    // 자원의 획득/반납은 반드시 직접하지 말고
    // 생성자/소멸자에 의존해야 합니다.
    std::lock_guard<std::mutex> g(m); // g의 생성자에서
                                      // m.lock()
//    m.lock();

    std::cout << "using shared data" << std::endl;
    throw std::runtime_error("goo fail");

//    m.unlock();
}   // <<= 지역변수인 g 파괴, 소멸자 호출
    // <<= 소멸자에서 unlock 수행



void foo()
{
    try { goo(); }
    catch (...)
    {
        std::cout << "goo에서 예외 발생" << std::endl;
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}



