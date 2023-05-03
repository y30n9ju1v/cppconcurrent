#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// 예외 전달

void divide(std::promise<int>&& p, int a, int b)
{
    try
    {
        if (b == 0)
        {
            throw std::runtime_error("divide by zero");
        }
        p.set_value(a / b);
    }
    catch (...)
    {
        // 현재 스레드에서 발생된 예외를
        // promise 를 통해서 주스레드에 전달합니다.
        // 주스레드가 ft.get() 할때 예외가 발생합니다.
        p.set_exception(std::current_exception());
    }
}

int main()
{
    std::promise<int> pm;
    std::future<int>  ft = pm.get_future();

    std::thread t(divide, std::move(pm), 10, 2);


    try
    {
        int ret = ft.get();
    }
    catch (std::exception& e)
    {
        std::cout << "예외 : " << e.what() << std::endl;
    }
    t.join();
}
// 결론. promise 는
// 1. 연산의 결과 값도 전달하고
// 2. 예외도 전달 가능합니다.


