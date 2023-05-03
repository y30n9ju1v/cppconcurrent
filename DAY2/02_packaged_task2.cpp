#include <iostream>
#include <thread>
#include <future>

// 39 page

// �Ϲ� �Լ���� �Ʒ� ó�� ����� �˴ϴ�.
// => �̹� �Ʒ� ó�� ������� �Լ��� ������� �����ؼ� ��� ���
int add(int a, int b)
{
	return a + b;
}

int main()
{
	// 1. packaged_task Ÿ���� ��ü�� �����մϴ�.
	std::packaged_task<int(int, int)> task(add);

	// 2. packaged_task ��ü���� future�� �����ϴ�.
	std::future<int> ft = task.get_future();

	// 3. �ֽ����尡 �����ص� �˴ϴ�.
	task(1, 2);  // () �����ڰ� ������ �Ǿ� �����Ƿ�
				 // �̷��� ȣ�Ⱑ��
	int ret1 = ft.get();
}



