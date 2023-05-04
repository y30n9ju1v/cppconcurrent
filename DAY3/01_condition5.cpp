#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1;

// condition_varaible �ڵ� ����
// => flag ������ �Բ� ����ϴ� ���� �Ϲ����� ���� �Դϴ�.
std::condition_variable cv;

bool data_ready = false;
bool data_process = false;

void consumer()
{
    std::this_thread::sleep_for(10ms);
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul, []() { return data_ready; });

    std::cout << "consume : " << shared_data << std::endl;

    data_process = true;
    cv.notify_one();
}

void producer()
{
    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;
    }
    data_ready = true;
    cv.notify_one();

    // �Һ��ڿ��� �о��� �˷��־��µ�..
    // ���� �о����� Ȯ���ϰ� �ʹ�.!!
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul, []() { return data_process; });

    std::cout << "produce : data ó�� �Ϸ�" << std::endl;
}


int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}