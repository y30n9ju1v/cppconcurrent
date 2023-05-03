#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

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



