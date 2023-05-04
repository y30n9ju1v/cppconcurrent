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


void consumer()
{
    std::this_thread::sleep_for(10ms);
    std::unique_lock<std::mutex> ul(m);

//  cv.wait(ul);        // ������ ���
//  cv.wait(ul, �Լ�); // 1. �Լ��� �����ؼ� ����� ���̸� ������
                      // 2. �����̸� unlock ���ϰ� ��ȣ�� �ö� ���� ���
                      // 3. ��ȣ�� ���� ����� 1������ �̵�
                        
    // �ᱹ, ������ �����ΰ�츸 ���..
    // ������ �ƴϸ� ��� ����
    cv.wait(ul, []() { return data_ready; });
   
    std::cout << "consume : " << shared_data << std::endl;
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
}





int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}