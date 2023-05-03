#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

std::mutex m;
int share_data = 0; // ���� ���� �����ڿ����� ������ ���ô�.

void foo()
{
//  m.lock();   // ���ؽ��� ȹ������ ���� ��� ���..

    if (m.try_lock()) // ���ؽ��� ȹ������ ���ϸ� false ��ȯ
    {
        share_data = 100;
        m.unlock();
    }
    else
    {
        // ���ؽ� ȹ�濡 ������ ���.. 
        // �ٸ� �۾� ����.
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);

    t1.join();
    t2.join();
}



