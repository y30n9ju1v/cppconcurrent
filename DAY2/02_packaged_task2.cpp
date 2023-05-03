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
//	task(1, 2);  // () �����ڰ� ������ �Ǿ� �����Ƿ�
				 // �̷��� ȣ�Ⱑ��
				 // add(1, 2)
//	int ret1 = ft.get();

	// 4. ���ο� �����带 ���鶧 1��° ���ڷ� task �����ϸ� �˴ϴ�.
	// std::ref(task)  : task �� ��� ����ϰ� ������
	// std::move(task) : task ��ü�� ���̻� �ʿ� ���ٸ�
	//std::thread t(std::ref(task), 1, 2); 
	std::thread t(std::move(task), 1, 2);
	
	int ret2 = ft.get();
	t.join();
}

// promise & future : �Լ����ڷ� promise �� �޾ƾ� �մϴ�
// 
// packaged_task    : ������ �Լ��� �ƴ� �Ϲ� �Լ� �������
//						������� �Լ��� ������� �����ؼ� ��� ���
//						"����" �ߴٰ� "���Ҷ� ����"

