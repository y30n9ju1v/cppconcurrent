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


void hoo()
{
    // 함수가 종료되기 전에 lock 을 해지 하려면 
    // 어떻게 하나요 ??
    // => {} 를 사용하세요
    {
        std::lock_guard<std::mutex> g(m);
        // ...
    } // <== 여기서 unlock 됩니다

    //....
}



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



