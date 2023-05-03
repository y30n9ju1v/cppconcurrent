#include <iostream>
#include <thread>
#include <string_view>
// 3�� ����� ���������� ��ȯ �ϴ� �Լ�
// => �Ʒ� �ڵ�� �̱۽����忡���� �����մϴ�.
// => ��Ƽ ������ ���?
int next3times()
{
//	int n = 0;
	static int n = 0;
	n = n + 3;
	return n;
}

void foo(const std::string& name)
{
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
}

int main()
{
//	foo("A");

	std::thread t1(&foo, "A");
	std::thread t2(&foo, "\tB");

	t1.join();
	t2.join();
}



