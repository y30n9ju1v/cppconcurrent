#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// 핵심 : future로 결과 대기시 timeout 설정

void add(std::promise<int>&& p, int a, int b)
{
    std::this_thread::sleep_for(1s);
    p.set_value(a + b);
}

int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    std::thread t(add, std::move(pm), 10, 20);

    // 1. ft.get() 은 결과가 나올때 까지 무한히 대기 합니다.
    // int n1 = ft.get(); 

    // 2. timeout 을 지정하려면 wait_for 로 하세요
    std::future_status ret = ft.wait_for(2s);

    // std::future_status : enum 타입입니다.
    if (ret == std::future_status::ready)
    {
        std::cout << "set_value() 가 수행되어서 결과 있음\n";
        std::cout << ft.get() << std::endl; 
                    // 결과가 있으므로 대기 없이 즉시 꺼냄.
    }
    else if (ret == std::future_status::timeout)
    {
        std::cout << "대기시간초과\n" << std::endl;
    }
    else if (ret == std::future_status::deferred)
    {
        std::cout << "아직 스레드 실행안됨\n" << std::endl;
        // => std::async() 사용시에만 나올수 있는 값
        // => std::thread 로 만들 경우는 해당 안됨.
    }
//    t.join();
}



