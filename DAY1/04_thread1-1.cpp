#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

void foo()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "foo : " << i << std::endl;
        std::this_thread::sleep_for(100ms);
    }
}
int main()
{
    std::thread t(&foo); 

    // 스레드 생성후.. 주 스레드가 detach() (핸들닫기)..
    t.detach();

} // <= 이순간 주스레드는 종료 됩니다.
  // 새로운 스레드는 어떻게 될까요 ?
