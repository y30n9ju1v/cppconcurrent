#include <iostream>
#include <thread>
#include <future>
int add(int a, int b)
{
	std::cout << "add" << std::endl;
	return a + b;
}
int main()
{
	std::packaged_task<int(int, int)> task(add);
	// task �� ��� �۾��� 2�� �����ϴ� ���.
	// task �� ���������� promise �� ����ϰ� �˴ϴ�.
//	task(1, 2);
//	task(1, 2); // ���� �߻�
//	task.reset();
//	task(1, 2);

	std::future<int> ft1 = task.get_future();

	std::thread t1(std::ref(task), 1, 2);
	int ret1 = ft1.get();
	t1.join();

//	task.reset();

	std::future<int> ft2 = task.get_future();

	std::thread t2(std::ref(task), 1, 2);
	int ret2 = ft2.get();
	t2.join();


}


