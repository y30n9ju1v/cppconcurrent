#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
    std::cout << "add : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);
    return a + b;
}


int main()
{
    // std::launch::async    : 비동기로 실행, 즉, 스레드를 생성해서 실행
    // std::launch::deferred : 지연된 실행
    //                         스레드 만들지 말고, 결과가 필요할때
    //                         주스레드가 호출.!
//  std::future<int> ft = std::async(std::launch::async,    add, 10, 20);
//  std::future<int> ft = std::async(std::launch::deferred, add, 10, 20);


    // std::launch::async || std::launch::deferred
    // ==> 스레드를 만들수 있으면 스레드로, 
    // ==> 스레드가 지원되지 않은 OS 라면 지연된 실행으로
    // ==> 옵션 생략시, 디폴트값
    std::future<int> ft = std::async( add, 10, 20);


    std::cout << "continue main : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);

    int ret = ft.get(); // 결과가 필요
                        // "지연된 실행"의 경우 이때 주스레드가 호출

    std::cout << "result : " << ret << std::endl;
}



