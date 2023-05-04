//00_false_sharing1
#include <iostream>
#include <thread>
#include "chronometry.h"

constexpr int sz = 10000000; // 0 7��. 

long long n1 = 0;
long long n2 = 0;
// �ٽ� : f1, f2 �� ���� �ٸ� ������ ��� ����(n1, n2)
void f1()
{
	// õ���� ���� n1 1����
	for (int i = 0; i < sz; i++)
	{
		n1 += 1;
	}
}
void f2()
{
	// f1 �Լ��� ����, �� n2�� ��� ����
	for (int i = 0; i < sz; i++)
	{
		n2 += 1;
	}
}

void single_thread()
{	
	// �ϳ��� ������� ���������� 2�� �۾� ����
	f1();
	f2();
}
void multi_thread()
{
	// 2���� ������� ���� �۾� ����
	std::thread t1(f1);
	std::thread t2(f2);

	t1.join();
	t2.join();
}

int main()
{
	chronometry(single_thread);
	chronometry(multi_thread);
}
