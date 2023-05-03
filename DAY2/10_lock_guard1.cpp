#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

// �ٽ� : ����ڰ� ���� lock(), unlock()�� ����ϸ�
//       ���� �ڿ� ���� ����(����)�� �߻��ϸ�
//       ��� ���� �����尡 ����� ���� �˴ϴ�.(deadlock)

/*
m.lock();

// ���⼭ ���ܰ� ������ unlock �ȵ˴ϴ�.

m.unlock();
*/

std::mutex m;

void goo()
{
    m.lock();    
    
    std::cout << "using shared data" << std::endl;
    throw std::runtime_error("goo fail");

    m.unlock();
}

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


