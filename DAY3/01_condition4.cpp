#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1;

// condition_varaible 코딩 관례
// => flag 변수와 함께 사용하는 것이 일반적인 관례 입니다.
std::condition_variable cv;

bool data_ready = false;


void consumer()
{
    std::this_thread::sleep_for(10ms);
    std::unique_lock<std::mutex> ul(m);

//  cv.wait(ul);        // 무조건 대기
//  cv.wait(ul, 함수); // 1. 함수를 실행해서 결과가 참이면 대기안함
                      // 2. 거짓이면 unlock 을하고 신호가 올때 까지 대기
                      // 3. 신호가 오면 깨어나면 1번으로 이동
                        
    // 결국, 조건이 거짓인경우만 대기..
    // 거짓이 아니면 대기 안함
    cv.wait(ul, []() { return data_ready; });
   
    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{
    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;
    }
    data_ready = true;
    cv.notify_one(); 
}





int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}