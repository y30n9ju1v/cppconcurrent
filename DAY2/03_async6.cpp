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
	// �׷� �ɼ��� �ý��� ��Ȳ�� ���� �ʴ� ��쿡��, ���ܰ� �߻� �ұ��?
	// => �Ʒ� ó�� ����. ��Ƽ�����尡 �������� ���� �ý��ۿ��� �����ϸ�
	//    "std::system_error" Ÿ���� ���� �߻�
	std::future<void> ft = std::async(std::launch::async, foo);
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
// "return ��"�� ������ ���� ������ �������?
// std::tuple �̶����, task ��ü�� return �� �� �ֳ���?
// => Ư���� ��������ϴ�. task �� ����.