#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::timed_mutex m;

int main()
{
    std::unique_lock<std::timed_mutex> u1;  // u1 �� ���ؽ�����ȵ�
    std::unique_lock<std::timed_mutex> u2(m);// u2 m.lock()���� m����

    // �ٽ�. ����� �ȵ����� move �� ����
//  u1 = u2;  // error
    u1 = std::move(u2);  // ok

    std::cout << u1.owns_lock() << std::endl; //true

    if (u1) // u1.owns_lock() 
        std::cout << "acquire" << std::endl;

    // �Ҹ��� ���� �ڵ� unlock �ܿ�.. ��������� unlock �� ����..
    u1.unlock();

    std::cout << u1.owns_lock() << std::endl;  

    if (u1.try_lock_for(2s))
    {
        //....
        u1.unlock();
    }

    u1.release();
}



