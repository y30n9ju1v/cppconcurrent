#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

void foo()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "foo : " << i << std::endl;
        std::this_thread::sleep_for(100ms);
    }
}
int main()
{
//  foo(); // �� �����尡 �׳� ����

    // �ٽ� 1. �����带 �����ϴ� ���
    std::thread t(&foo);  // �̼��� �����尡 �����Ǿ foo ����
                          // ������ "start()" ���� �Լ��� �����ϴ�.

    // �ٽ� 2. �����带 ������ ��� �ݵ�� �Ʒ� 2���� �Ѱ��� �ؾ� �մϴ�.
    // join   : ������ ����� ���� ���
    // detach : ������ �и�(�ڵ� �ݱ�)
    // 
//  t.join();  // ������ ����ñ��� ���罺����(�ֽ�����) ���

    t.detach(); // ������ �и�
                // ���ο� �����忡 ���ɾ����Ƿ� ���������� �����϶�°�
                // ���������� �����ϴ� ������ �ڵ��� �ݴ� �۾�
    std::cout << "continue main" << std::endl;
}
