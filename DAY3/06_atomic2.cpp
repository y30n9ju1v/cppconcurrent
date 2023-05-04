#include <iostream>
#include <thread>
#include <atomic>

//long x = 0; // �Ϲ� ��������. ++ ���� ������ ��Ƽ�����忡��
            // �������� �ʽ��ϴ�.

std::atomic<long> x = 0; // ++���� ������ ��Ƽ�����忡 ����

void foo()
{
    for (int i = 0; i < 100000; ++i)
    {
//      ++x; // x.operator++() ȣ��
             // atomic1.cpp �� ���� CPU ��� ���.

//      x.fetch_add(1);
        x.fetch_add(1, std::memory_order_relaxed);  
                        // => �� �ڵ庸�� �ణ �� ������ �ֽ��ϴ�.
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    std::thread t3(foo);
    t1.join();
    t2.join();
    t3.join();
    std::cout << x << std::endl;
}
