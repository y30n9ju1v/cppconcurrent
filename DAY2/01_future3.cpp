#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>&& p, int a, int b)
{
    std::this_thread::sleep_for(1s);
    p.set_value(a + b);
}
int main()
{
    std::promise<int> pm;

    

    // �ٽ�1 : future �� �ѹ��� ������ �ְ�, ���絵 �ȵ˴ϴ�.
//  std::future<int> ft = pm.get_future();
//  std::future<int> ft2 = pm.get_future(); // ����
//  std::future<int> ft2 = ft; // error.

    // �ٽ� 2. shared_future �� ����ϸ� 2�� �̻��� �����忡��
    //   ��� �����մϴ�.
    std::future<int> ft = pm.get_future(); // future�� ���� ������
    std::shared_future<int> sft1 = ft.share(); 
//  std::shared_future<int> sft2 = ft.share(); // ����
    std::shared_future<int> sft3 = sft1;       // ���� ����

    std::thread t(add, std::move(pm), 10, 20);

    // �ٽ� 3. shared_future �� ���� ���� �ֽ����尡 ���ÿ���
    //        shared_future ����ؾ� �մϴ�.
    // => �Ǵٸ� �����忡 shared_future �� ������ get() �Ҽ��� �ֽ��ϴ�.
 // int ret1 = ft.get();
    int ret1 = sft1.get();

    t.join();
}




