#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;


// 1. Write�ϴ� ���� �ٸ� ������� ������ ����� �մϴ�.
// 2. Read�ϴ� ���� �ٸ� ������� ���� ����� �մϴ�.
// 3. Write�ϴ� ���� �ٸ� ������� ���� ����� �մϴ�.
// 
// 4. Read�ϴ� ���� �ٸ� ������� ������ �˴ϴ�. =>�ٽ�

//std::mutex m;

std::shared_mutex m;
int share_data = 0;

void Writer()
{
    while (1)
    {
        m.lock();
        share_data = share_data + 1;
        std::cout << "Writer : " << share_data << std::endl;
        std::this_thread::sleep_for(1s);
        m.unlock();
        std::this_thread::sleep_for(10ms);
    }
}
void Reader(const std::string& name)
{
    while (1)
    {
        m.lock_shared();
        std::cout << "Reader(" << name << ") : " << share_data << std::endl;
        std::this_thread::sleep_for(500ms);

        m.unlock_shared();
        std::this_thread::sleep_for(10ms);
    }
}

int main()
{
    std::thread t1(Writer);
    std::thread t2(Reader, "A");
    std::thread t3(Reader, "B");
    std::thread t4(Reader, "C");
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}



