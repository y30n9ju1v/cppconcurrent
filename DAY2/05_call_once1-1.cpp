#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

// 1. std::once_flag Ÿ���� ������ ���������� �Ѱ� ����
std::once_flag flag;

void init(int a, double d)
{
    std::cout << "init" << std::endl;
    std::this_thread::sleep_for(2s);
}

void foo()
{
    std::cout << "start foo" << std::endl;
    
    // 2. init() ȣ��� ���� ȣ������ ���� �Ʒ� ó�� �ϼ���
    // init(10, 3.4); // ������� �ѹ��� ȣ��

    std::call_once(flag, init, 10, 3.4); // ���ʿ� 1ȸ�� ȣ��

    std::cout << "finish foo" << std::endl;
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}



