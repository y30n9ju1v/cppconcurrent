#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>&& p, int a, int b)
{
    std::this_thread::sleep_for(1s);
    p.set_value(a + b);
}
int main()
{
    std::promise<int> pm;

    

    // 핵심1 : future 는 한번만 꺼낼수 있고, 복사도 안됩니다.
//  std::future<int> ft = pm.get_future();
//  std::future<int> ft2 = pm.get_future(); // 예외
//  std::future<int> ft2 = ft; // error.

    // 핵심 2. shared_future 를 사용하면 2개 이상의 스레드에서
    //   대기 가능합니다.
    std::future<int> ft = pm.get_future(); // future를 먼저 꺼내고
    std::shared_future<int> sft1 = ft.share(); 
//  std::shared_future<int> sft2 = ft.share(); // 예외
    std::shared_future<int> sft3 = sft1;       // 복사 가능

    std::thread t(add, std::move(pm), 10, 20);

    // 핵심 3. shared_future 를 꺼낸 경우는 주스레드가 대기시에도
    //        shared_future 사용해야 합니다.
    // => 또다른 스레드에 shared_future 를 보내서 get() 할수도 있습니다.
 // int ret1 = ft.get();
    int ret1 = sft1.get();

    t.join();
}




