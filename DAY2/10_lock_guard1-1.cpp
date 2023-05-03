#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

void goo()
{
    // �ڿ��� ȹ��/�ݳ��� �ݵ�� �������� ����
    // ������/�Ҹ��ڿ� �����ؾ� �մϴ�.
    std::lock_guard<std::mutex> g(m); // g�� �����ڿ���
                                      // m.lock()
//    m.lock();

    std::cout << "using shared data" << std::endl;
    throw std::runtime_error("goo fail");

//    m.unlock();
}   // <<= ���������� g �ı�, �Ҹ��� ȣ��
    // <<= �Ҹ��ڿ��� unlock ����



void foo()
{
    try { goo(); }
    catch (...)
    {
        std::cout << "goo���� ���� �߻�" << std::endl;
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}



