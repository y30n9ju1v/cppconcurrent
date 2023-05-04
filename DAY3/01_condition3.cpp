#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1;
std::condition_variable cv;

// �Ʒ� �ڵ��� ��������
// => �Һ��ڰ� ���� wait ���� �ʾҴµ�
// => �����ڰ� ���� �����ؼ� ��ȣ�� �����ϴ� ��� �Դϴ�.
// => �ذ��� �����ҽ�����..
void consumer()
{
    std::this_thread::sleep_for(10ms);
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul);    

    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{
    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;
    }
    cv.notify_one(); // �����ڰ� ��ȣ�� �ִµ�..
                     // �Һ��ڴ� ���� wait �ϰ� ���� �ʽ��ϴ�.
                     // �Һ��ڰ� ���߿� wait �ϰ� �����Ƿ�
                     // �Һ� �Ҽ� �����ϴ�.
}





int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}