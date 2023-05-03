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
    std::future<int> ft = std::async(add, 10, 20);

    std::cout << "continue main : " << std::this_thread::get_id() << std::endl;

    // async 가 반환한 future 를 get() 하지 않으면  ?
//  int ret = ft.get(); // 이순간 결과가 나올때 까지 대기.
    
}



