#include <iostream>
#include <thread>
#include <future>

int add(int a, int b)
{
	return a + b;
}

int main()
{
	// packaged_task : �۾�(�Լ�)�� �����ߴٰ� �ʿ� �Ҷ� ����
	// async : �۾��� ��� �񵿱�(������)�� ����.

	std::future<int> ft = std::async(add, 1, 2);

	int ret = ft.get();

	std::cout << ret << std::endl;
}
