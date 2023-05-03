#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// 핵심 : promise 와 future 는 1회용 입니다.

void add(std::promise<int>&& p, int a, int b)
{
    std::this_thread::sleep_for(1s);

    // 1. set_value() 는 한번만 사용가능합니다.
    p.set_value(a + b); // ok
//  p.set_value(a + b); // 예외 발생..!

    // 2. 또한 하나의 promise 는 한개의 스레드만 사용해야 합니다.
    //    여러개 스레드가 공유 안됩니다.
    // => 여러개 스레드에서 공유하려면 직접 동기화 객체 사용하세요
    //    오후 수업
}

int main()
{
    std::promise<int> pm;

    // 핵심 2. promise 에서 future 객체는 한번만 꺼낼수있고
    //        복사도 안됩니다.
    std::future<int> ft = pm.get_future();
//  std::future<int> ft2 = pm.get_future(); // 예외
//  std::future<int> ft2 = ft;   // 에러. 복사 생성자 삭제됨.

    std::thread t(add, std::move(pm), 10, 20);
        
    // 핵심 3. get() 도 한번만 호출가능합니다.
    std::cout << ft.valid() << std::endl; // true
    int ret = ft.get();
//  int ret = ft.get(); // 예외!!

    // 핵심 4. get() 이 가능한지 확인하려면 valid() 함수
    std::cout << ft.valid() << std::endl; // false

    t.join();
}



