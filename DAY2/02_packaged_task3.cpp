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
	task(1, 2);
//	task(1, 2); // ���� �߻�
	task.reset();
	task(1, 2);


}


