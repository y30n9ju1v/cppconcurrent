#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// 1. ��� ����
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1; 

// 2. std::condition_variable Ÿ���� �������� ����
std::condition_variable cv;



void consumer()
{
    // 3. �Һ���(��ȣ���)�� unique_lock ���� ���ؽ� ȹ����
    //    ��ȣ�� ��� �մϴ�.
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul);

    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{
    std::this_thread::sleep_for(10ms);
    {
        // �����ڴ� ��� lock_guard ���
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;
    }
    // 3. ������ ������ lock �� Ǯ�� ��ȣ�� �ָ� �˴ϴ�.
    cv.notify_one();
}


int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}