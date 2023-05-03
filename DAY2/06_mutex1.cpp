#include <iostream>
#include <thread>
#include <chrono>
#include <string_view>
#include <mutex>
using namespace std::literals;


std::mutex m;   // �ڿ��� �����Ҷ� ����ϴ� ����
                // ���� �Ѱ��� �����常�� ���ؽ��� ȹ���Ҽ� �ִ�.

void delay() { std::this_thread::sleep_for(20ms); }

void foo(const std::string& name)
{
//  int x = 0;  // ������ ���� ���� ������.
                // �׻� �����ϴ�.!

    static int x = 0;  // ��� �����尡 �����ϴ� ���� �ڿ�

    for (int i = 0; i < 10; i++)
    {
        m.lock();
        // �Ʒ� ������ �Ѱ��� �����徿 ����ؾ� �մϴ� - ����ȭ(serialization)
        // ���� �Ʒ� ������ �Ӱ迵��(critical section) �̶�� �մϴ�.
        //--------------------------------
        x = 100;   delay();
        x = x + 1; delay();
        std::cout << name << " : " << x << std::endl; delay();
        //-------------------------------
        m.unlock();
    }
}

int main()
{
    std::thread t1(foo, "A");
    std::thread t2(foo, "\tB");
    t1.join();
    t2.join();
}



