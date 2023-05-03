#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

int add1(int a, int b)
{
	int s = a + b;
	return s;
}

// �Լ��� ����� �������� ���ؼ� out parameter�� ����ϴ� �ڵ�
// ���� : �ֽ����忡�� ������ ����� ��� �Ҽ� �����ϴ�.
// �ذ�å
// 1. promise & future
// 2. packaged_task
// 3. async
void add2(int a, int b, int& s)
{
	s = a + b;

	// ������ �Ϸᰡ �Ǿ��µ�.. ������ �۾��� �ð��� �ɸ��ٰ� ����
	std::this_thread::sleep_for(3s);
}
int main()
{
	// �ٽ� 1. �����尡 �ƴ� ���� ȣ���� �Լ��� ����� ��ȯ������ ������ �˴ϴ�.
	int ret1 = add1(1, 2);

	// �ٽ� 2. 
	int ret2 = 0;
	std::thread t(add2, 1, 2, std::ref(ret2));

	t.join();	// ������ ���ᰡ �ƴ� �������� ���Ḧ ���.
	std::cout << ret2 << std::endl;
}
