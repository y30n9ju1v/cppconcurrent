#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
    std::cout << "add : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);

    std::cout << "finish add\n";

    return a + b;
}

int main()
{

//    std::future<int> ft = std::async(add, 10, 20);
    
    // 아래 처럼 반환 값(future)를 받지 않으면
    // 마치 비동기 호출(스레드) 가 아닌 동기 호출처럼 보이게 됩니다.
    // => 하지만 스레드가 생성된 것은 맞습니다(ID로 확인)
    std::async(add, 10, 20);    // 1. 반환값으로 임시객체 반환
                                // 2. 임시객체 파괴, 소멸자 호출
                                // 3. 소멸자에서 get()으로 대기

    // 단, 리턴 값을 받으면 위처럼 대기 하지 않고
    // get() 할때 대기 하게 됩니다.

    std::cout << "continue main : " << std::this_thread::get_id() << std::endl;
} 



