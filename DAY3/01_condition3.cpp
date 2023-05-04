#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1;
std::condition_variable cv;

// 아래 코드의 문제점은
// => 소비자가 아직 wait 하지 않았는데
// => 생산자가 먼저 도착해서 신호를 전달하는 경우 입니다.
// => 해결은 다음소스에서..
void consumer()
{
    std::this_thread::sleep_for(10ms);
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul);    

    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{
    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;
    }
    cv.notify_one(); // 생산자가 신호를 주는데..
                     // 소비자는 아직 wait 하고 있지 않습니다.
                     // 소비자가 나중에 wait 하고 있으므로
                     // 소비를 할수 없습니다.
}





int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}