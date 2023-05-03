#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

//std::mutex m;   // 1. m.lock()      : ȹ���Ҷ� ���� ���
                  // 2. m.try_lock()  : ȹ������ ���ϸ� false

std::timed_mutex m; // �� 2�� �ܿ�
                    // m.try_lock_for(�ð�)
                    // m.try_lock_until(�ð�)

int share_data = 0;

void foo()
{
    //m.lock();
    //if ( m.try_lock() )
    if ( m.try_lock_for(3s) )
    {
        share_data = 100;
        std::cout << "using share_data" << std::endl;
        std::this_thread::sleep_for(3s);
        m.unlock();
    }
    else
    {
        std::cout << "���ؽ� ȹ�� ����" << std::endl;
    }
}
int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}

// C++ ǥ�� ���ؽ��� 6�� �Դϴ�.
// std::mutex,       std::recursive_mutex,       std::shared_mutex(C++17)
// std::timed_mutex, std::timed_recursive_mutex, std::timed_shared_mutex(C++17)


