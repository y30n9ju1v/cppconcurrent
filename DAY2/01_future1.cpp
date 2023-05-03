#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// �ٽ� : future�� ��� ���� timeout ����

void add(std::promise<int>&& p, int a, int b)
{
    std::this_thread::sleep_for(1s);
    p.set_value(a + b);
}

int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    std::thread t(add, std::move(pm), 10, 20);

    // 1. ft.get() �� ����� ���ö� ���� ������ ��� �մϴ�.
    // int n1 = ft.get(); 

    // 2. timeout �� �����Ϸ��� wait_for �� �ϼ���
    std::future_status ret = ft.wait_for(2s);

    // std::future_status : enum Ÿ���Դϴ�.
    if (ret == std::future_status::ready)
    {
        std::cout << "set_value() �� ����Ǿ ��� ����\n";
        std::cout << ft.get() << std::endl; 
                    // ����� �����Ƿ� ��� ���� ��� ����.
    }
    else if (ret == std::future_status::timeout)
    {
        std::cout << "���ð��ʰ�\n" << std::endl;
    }
    else if (ret == std::future_status::deferred)
    {
        std::cout << "���� ������ ����ȵ�\n" << std::endl;
        // => std::async() ���ÿ��� ���ü� �ִ� ��
        // => std::thread �� ���� ���� �ش� �ȵ�.
    }
//    t.join();
}



