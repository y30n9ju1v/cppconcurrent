#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;


// 1. Write하는 동안 다른 스레드는 읽을수 없어야 합니다.
// 2. Read하는 동안 다른 스레드는 쓸수 없어야 합니다.
// 3. Write하는 동안 다른 스레드는 쓸수 없어야 합니다.
// 
// 4. Read하는 동안 다른 스레드는 읽을도 됩니다. =>핵심

//std::mutex m;

std::shared_mutex m;
int share_data = 0;


// shared_mutex 동작 방식

// m.lock() 하면 : 다른 스레드의 m.lock(), m.lock_shared()는
//                  모두 대기
//              => "쓰는 동안" 은 "모두 금지"

// m.lock_shared() : 다른 스레드의 m.lock()은 대기
//                               m.lock_shared()는 대기 안함
//              => "읽는 동안" 은 "쓰기 금지", "읽기 가능"

// Writer : m.lock(), m.unlock()
// Reader : m.lock_shared(), m.unlock_shared()


void Writer()
{
    while (1)
    {
        m.lock();
        share_data = share_data + 1;
        std::cout << "Writer : " << share_data << std::endl;
        std::this_thread::sleep_for(1s);
        m.unlock();
        std::this_thread::sleep_for(10ms);
    }
}
void Reader(const std::string& name)
{
    while (1)
    {
        m.lock_shared();
        std::cout << "Reader(" << name << ") : " << share_data << std::endl;
        std::this_thread::sleep_for(500ms);

        m.unlock_shared();
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



