#include <iostream>
#include <thread>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
	std::this_thread::sleep_for(2s);
	return a + b;
}

int main()
{
//	int              r1 = add(1, 2); // �ֽ����尡 ����
//	std::future<int> r2 = std::async(add, 1, 2); // ������� ����.

	// packaged_task : �۾�(�Լ�)�� �����ߴٰ� �ʿ� �Ҷ� ����
	// async : �۾��� ��� �񵿱�(������)�� ����.
	std::future<int> ft = std::async(add, 1, 2);

	std::cout << "continue main" << std::endl;

	int ret = ft.get();

	std::cout << ret << std::endl;
}

// std::async : "return ��" ������ �Լ��� ��� ������� ����
//              ���������δ� �ٽ� std::thread ����ؼ� ����
//              �ַ� "������ Ǯ"�� ����
// 
// ==> �Ʒ� ����� ��� "std::thread" ���
// packaged_task : "return ��" ���� �� �Լ��� �����ߴٰ�
//                 std::thread �� �����ؼ� ��� ���
//----------------------------------------
// promise / future : ����� ��� ���� ����
//----------------------------------------
// std::thread : C++���� �����带 ����� Ŭ����
//-----------------------------------------
// OS : CreateThread(), pthread_create()