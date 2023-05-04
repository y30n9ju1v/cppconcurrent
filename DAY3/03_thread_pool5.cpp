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
	std::packaged_task<int(int, int)> task(add);

	// add �� ������� �ʾ����� �̷��� ����� ���� ��ü��
	// ������ �ֽ��ϴ�.
	std::future<int> ft = task.get_future(); 

	int ret2 = ft.get();

}