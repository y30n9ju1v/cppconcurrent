#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

void foo(std::promise<int>&& p)
{
    std::cout << "start foo" << std::endl;
    std::this_thread::sleep_for(3s);
    std::cout << "finish foo" << std::endl;
    p.set_value(10);
}
int main()
{
    std::promise<int> p;
    std::future<int> ft = p.get_future();

    std::thread t(foo, std::move(p));
    t.detach();

//  ft.get(); // foo �� set_value �Ҷ����� ���(3��)

} // ft �ı�, �Ҹ��� ȣ��

// async �� ��ȯ�ϴ� future : �Ҹ��ڿ���  "get()" �մϴ�.
// promise���� ������ future : �Ҹ��ڿ���  "get()" ���� �ʽ��ϴ�.




