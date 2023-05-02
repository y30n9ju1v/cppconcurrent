#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

// �ٽ� : ������ ID ���

void foo()
{
    // �ٽ� : �ڱ��ڽ��� ������ ID ���
    std::cout << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::thread t(&foo);
    
    std::this_thread::sleep_for(1s);

    // �ڽ�(�ֽ�����)�� ������ ���ο� �������� ID ���
    std::thread::id tid = t.get_id();
    
    std::cout << "created thread id : " << tid << std::endl;

    t.join();
}

