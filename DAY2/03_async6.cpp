#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

// async�� ����ó���� ��� �ϳ��� ?
// => get ���� catch �ϸ� �˴ϴ�.

void foo()
{
	throw std::runtime_error("foo fail");
}
int main()
{
	// ��ȯ ���� ������ �Ʒ� ó�� �ϸ� �˴ϴ�.
	std::future<void> ft = std::async(foo);
	try
	{
		ft.get();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	// async ���ÿ� join�̳� detach�� ���� �ʿ����� �ʳ��� ?
	// => �ʿ� �����ϴ�.
}