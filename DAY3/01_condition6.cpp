#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;


int share_data = 0;


bool data_ready = false;

// std::condition_variable : unique_lock 으로만 사용가능
// std::mutex m;
// std::condition_variable cv;

// std::condition_variable_any : lock()/unlock() 이 있는 모든 lock management 클래스와 같이 사용가능
std::shared_mutex m;
std::condition_variable_any cv;

void Writer()
{
    while (1)
    {
        {
            std::lock_guard<std::shared_mutex> g(m);

            share_data = share_data + 1;
            std::cout << "Writer : " << share_data << std::endl;
            std::this_thread::sleep_for(1s);
            
            data_ready = true;
        }
        //cv.notify_one();
        cv.notify_all();
    }
}



void Reader(const std::string& name)
{
    while (1)
    {
        {
            //  condition_variable 은 shared_lock 안됩니다.
            //  condition_variable_any 은 shared_lock 됩니다.
            std::shared_lock<std::shared_mutex> ul(m);   

            cv.wait(ul, []() { return data_ready; } );
                    // lock 이 아니라 lock_shared 를 사용하게 됩니다.

            std::cout << "Reader(" << name << ") : " << share_data << std::endl;
            std::this_thread::sleep_for(500ms);
        }
        std::this_thread::sleep_for(10ms);
    }
}


int main()
{
    std::thread t1(Writer);
    std::thread t2(Reader, "A");
    std::thread t3(Reader, "B");
    std::thread t4(Reader, "C");
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}



