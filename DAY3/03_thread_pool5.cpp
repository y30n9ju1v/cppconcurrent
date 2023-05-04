#include <memory>
#include <iostream>
#include <future>
#include <functional>
#include <vector>

using F = std::function<void()>;

std::vector<F> v;


int add(int a, int b)
{
	std::cout << "add" << std::endl;

	return a + b;
}

// �ٽ� : �Լ��� ��ȯ ���� �������� 

int main()
{
	// �Լ��� ȣ���ϸ� ��� ��ȯ���� ������ �ֽ��ϴ�.
	int ret1 = add(1, 2);

	// packaged_task �� ����ϸ� ���� ������� ���� �Լ��� 
	// ����� ������ �ֽ��ϴ�.

	// 1. �Ʒ� ó�� ����� task ���� ���� �ʿ�
//	std::packaged_task<int(int, int)> task(add);
//	task(1, 2);

	// 2. �Ʒ� ó�� ����� task ���� ���� �ʿ� �����ϴ�.
	std::packaged_task<int()> task(
					std::bind(add, 1, 2));

	// add �� ������� �ʾ����� �̷��� ����� ���� ��ü��
	// ������ �ֽ��ϴ�.
	std::future<int> ft = task.get_future(); 

	task(); // add(1,2)


	int ret2 = ft.get(); // ��� ���

}