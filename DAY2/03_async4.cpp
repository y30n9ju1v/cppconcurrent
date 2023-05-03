#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

void foo(std::promise<int>&& p)
{
    std::cout << "start foo" << std::endl;
    std::this_thread::sleep_for(3s);
    std::cout << "finish foo" << std::endl;
    p.set_value(10);
}
int main()
{
    std::promise<int> p;
    std::future<int> ft = p.get_future();

    std::thread t(foo, std::move(p));
    t.detach();

//  ft.get(); // foo 가 set_value 할때까지 대기(3초)

} // ft 파괴, 소멸자 호출

// async 가 반환하는 future : 소멸자에서  "get()" 합니다.
// promise에서 꺼내는 future : 소멸자에서  "get()" 하지 않습니다.




