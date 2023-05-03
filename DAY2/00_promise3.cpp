#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// 예외 전달

void divide(std::promise<int>&& p, int a, int b)
{
    if (b == 0)
    {
        // 스레드 함수에서 예외가 발생되면??
        // => 예외는 스레드 별로 따로 처리 됩니다.
        // => 하나의 스레드가 던진 예외를 다른 스레드가 catch 할수
        //    없습니다.
        // => 아래 throw 를 주 스레드가 catch 할수 없습니다.
        throw std::runtime_error("divide by zero");
    }
    p.set_value(a / b);
}



int main()
{
    std::promise<int> pm;
    std::future<int>  ft = pm.get_future();

    std::thread t(divide, std::move(pm), 10, 2);


    int ret = ft.get();

    t.join();
}



