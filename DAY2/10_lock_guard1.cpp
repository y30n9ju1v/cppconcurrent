#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

// 핵심 : 사용자가 직접 lock(), unlock()을 사용하면
//       공유 자원 사용시 문제(예외)가 발생하면
//       대기 중인 스레드가 깨어날수 없게 됩니다.(deadlock)

/*
m.lock();

// 여기서 예외가 나오면 unlock 안됩니다.

m.unlock();
*/

std::mutex m;

void goo()
{
    m.lock();    
    
    std::cout << "using shared data" << std::endl;
    throw std::runtime_error("goo fail");

    m.unlock();
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



