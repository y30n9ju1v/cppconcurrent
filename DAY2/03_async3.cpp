#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
    std::cout << "add : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);

    std::cout << "finish add\n";

    return a + b;
}

int main()
{
    std::future<int> ft = std::async(add, 10, 20);

    std::cout << "continue main : " << std::this_thread::get_id() << std::endl;

    // async �� ��ȯ�� future �� get() ���� ������  ?
//  int ret = ft.get(); // �̼��� ����� ���ö� ���� ���.
    
} // <= �̼��� ft �� �ı� �˴ϴ�.
  // <= ft �� �Ҹ��ڰ� ȣ��Ǵµ�.. ft.get() �� �ѹ��� ���� �������
  // <= �Ҹ��ڰ� ft.get() �� �����ؼ� ����� ��� �ϱ� �˴ϴ�.


