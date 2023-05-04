#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

// �Ʒ� �ڵ�� "mutex" �� ����ȭ �ڿ��� ���������� ���� �ڵ� �Դϴ�.

// ���� : �����ڰ� �ð��� �ɸ��µ�(10ms) 
//       �����ϱ� ���� �Һ��ڰ� �Һ�(�����Ⱚ -1)�� �ϰ� �˴ϴ�.

std::mutex m;
int shared_data = -1; // �����Ⱚ

void consumer()
{
    std::lock_guard<std::mutex> lg(m);
    std::cout << "consume : " << shared_data << std::endl;
}
void producer()
{
    std::this_thread::sleep_for(10ms);
    std::lock_guard<std::mutex> lg(m);
    shared_data = 100;
    std::cout << "produce : " << shared_data << std::endl;
}
int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join(); 
    t2.join();
}