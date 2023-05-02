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
    //t.detach();

    // 주스레드 종료 전에 다른 스레드가 안전하게 종료될때까지 대기!
    t.join();
} // <= 이순간 주스레드는 종료 됩니다.
  // 새로운 스레드는 어떻게 될까요 ?

// 주 스레드의 종료 
// => 프로세스가 종료 됩니다.
// => 아직 살아있던 모든 스레드는 강제 종료 됩니다.
// 권장 : 주스레드는 종료 되기 전에 다른 스레드가 안전하게
//       종료될수 있도록 하는 것이 좋습니다.