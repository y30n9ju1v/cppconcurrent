#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
    std::cout << "add : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);

    std::cout << "finish add\n";

    return a + b;
}

int main()
{

//    std::future<int> ft = std::async(add, 10, 20);
    
    // �Ʒ� ó�� ��ȯ ��(future)�� ���� ������
    // ��ġ �񵿱� ȣ��(������) �� �ƴ� ���� ȣ��ó�� ���̰� �˴ϴ�.
    // => ������ �����尡 ������ ���� �½��ϴ�(ID�� Ȯ��)
    std::async(add, 10, 20);    // 1. ��ȯ������ �ӽð�ü ��ȯ
                                // 2. �ӽð�ü �ı�, �Ҹ��� ȣ��
                                // 3. �Ҹ��ڿ��� get()���� ���

    // ��, ���� ���� ������ ��ó�� ��� ���� �ʰ�
    // get() �Ҷ� ��� �ϰ� �˴ϴ�.

    std::cout << "continue main : " << std::this_thread::get_id() << std::endl;
} 



