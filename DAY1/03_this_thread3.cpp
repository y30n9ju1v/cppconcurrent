#include <iostream>
#include <chrono>
#include <thread>
using namespace std::literals;

// std::this_thread �� 4�� �Լ�
// 1. get_id()
// 2. sleep_for()
// 3. sleep_until()
// 4. yield() : ���� ���� �ð��� ����..

void mysleep(std::chrono::microseconds us)
{
    auto target = std::chrono::high_resolution_clock::now() + us;

    while (std::chrono::high_resolution_clock::now() < target)
        std::this_thread::yield();
}

int main()
{
    mysleep(1s);
}
