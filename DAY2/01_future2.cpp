#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// �ٽ� : promise �� future �� 1ȸ�� �Դϴ�.

void add(std::promise<int>&& p, int a, int b)
{
    std::this_thread::sleep_for(1s);

    // 1. set_value() �� �ѹ��� ��밡���մϴ�.
    p.set_value(a + b); // ok
//  p.set_value(a + b); // ���� �߻�..!

    // 2. ���� �ϳ��� promise �� �Ѱ��� �����常 ����ؾ� �մϴ�.
    //    ������ �����尡 ���� �ȵ˴ϴ�.
    // => ������ �����忡�� �����Ϸ��� ���� ����ȭ ��ü ����ϼ���
    //    ���� ����
}

int main()
{
    std::promise<int> pm;

    // �ٽ� 2. promise ���� future ��ü�� �ѹ��� �������ְ�
    //        ���絵 �ȵ˴ϴ�.
    std::future<int> ft = pm.get_future();
//  std::future<int> ft2 = pm.get_future(); // ����
//  std::future<int> ft2 = ft;   // ����. ���� ������ ������.

    std::thread t(add, std::move(pm), 10, 20);
        
    // �ٽ� 3. get() �� �ѹ��� ȣ�Ⱑ���մϴ�.
    std::cout << ft.valid() << std::endl; // true
    int ret = ft.get();
//  int ret = ft.get(); // ����!!

    // �ٽ� 4. get() �� �������� Ȯ���Ϸ��� valid() �Լ�
    std::cout << ft.valid() << std::endl; // false

    t.join();
}



