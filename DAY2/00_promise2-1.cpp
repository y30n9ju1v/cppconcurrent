#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;


//void add3(int a, int b, std::promise<int>& p)
void add3(int a, int b, std::promise<int>&& p)
{
	int s = a + b;

	p.set_value(s);

	std::this_thread::sleep_for(3s);
}

int main()
{
	std::promise<int> pr;
	std::future<int> ft = pr.get_future();

	// �ֽ����忡���� future�� �����Ŀ��� promise �� ���̻�
	// �ʿ� �����ϴ�.
	// �׷��� �����忡 �����Ҷ�
	// 1. reference �� �����ص� �ǰ�
	// 2. std::move �� �����ص� �˴ϴ�.
//	std::thread t(add3, 1, 2, std::ref(pr));
	std::thread t(add3, 1, 2, std::move(pr));

	std::cout << "continue main\n";

	int ret = ft.get(); 

	std::cout << ret << std::endl;
}
