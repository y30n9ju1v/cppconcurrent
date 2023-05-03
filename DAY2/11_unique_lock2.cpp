#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex       m1, m2, m3;
std::timed_mutex tm1, tm2, tm3;

int main()
{
    // �ٽ� 1. ���� ���.
    std::unique_lock<std::mutex> u1;    // ���� ���ؽ� ����ȵ�
    std::unique_lock<std::mutex> u2(m1);// �����ڿ��� m.lock()                 

    std::unique_lock<std::mutex> u3(m2, std::try_to_lock);
                                        // �����ڿ��� m.try_lock()
                                        // ȹ�� ���ص� ��� ����.
                                        // ȹ�濩�δ� �Ʒ� �ڵ�� ����
    if (u3.owns_lock())
        std::cout << "acquire lock" << std::endl;
    else
        std::cout << "fail to lock" << std::endl;


    // �ٽ� 2. �̹� lock �� mutex �� unlock �� �����Ҷ�
    m3.lock(); // �̹� ȹ��
    std::unique_lock<std::mutex> u4(m3, std::adopt_lock);   


    // �ٽ� 3. mutex�� ���������� lock �� ���߿�.
    std::unique_lock<std::timed_mutex> u5(tm1, std::defer_lock);
    auto ret = u5.try_lock_for(2s);


    // �ٽ� 4. timed_lock ���� chrono �ð��� ���ް���..
    std::unique_lock<std::timed_mutex> u6(tm2, 2s);  // tm2.try_lock_for() ���
    std::unique_lock<std::timed_mutex> u7(tm3, std::chrono::steady_clock::now() + 2s);
    // tm3.try_lock_until() ���
}
