#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

// �ý����� �ʱ�ȭ �ϴ� �Լ�
// => �Ʒ� �Լ��� �ѹ��� ȣ��(�ʱ�ȭ)�ϸ� �ȴٰ� ������ ���ô�.
void init(int a, double d)
{
    std::cout << "init" << std::endl;
    std::this_thread::sleep_for(2s);
}
void foo()
{
    std::cout << "start foo" << std::endl;
    
    // �Ʒ� ó�� ���� ȣ���ϸ� ������� �ѹ��� init �Լ��� ȣ��˴ϴ�.
    init(10, 3.4);    // �ʱ�ȭ

    std::cout << "finish foo" << std::endl;
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}



