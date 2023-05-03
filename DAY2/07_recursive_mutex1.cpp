#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

//std::mutex m;   // �����ڶ� �ѹ��� lock ����

std::recursive_mutex m; // ���ؽ� �����ڰ� ������ lock ����
                        // ��, unlock()�� ���� Ƚ�� ��ŭ�ؾ� �Ѵ�.
                        
int share_data = 0;

void foo()
{
    std::cout << "wait mutex" << std::endl;

    m.lock();
    m.lock(); // mutex �����ڰ� �ٽ� �ѹ� lock

    share_data = 100;
    std::cout << "using share_data" << std::endl;
    m.unlock();
    m.unlock();
}


int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}




