//00_false_sharing1
#include <iostream>
#include <thread>
#include "chronometry.h"

constexpr int sz = 10000000; // 0 7��. 

long long n1 = 0;
long long n2 = 0;

// �ذ�å 3. ���������� ���� �������� ����
// ���������� �����Ŀ�, ����� ���������� �ű⼼��.

void f1()
{
	int local = n1;
	for (int i = 0; i < sz; i++)
	{
		local += 1;
	}
	n1 = local;
}

void f2()
{
	int local = n2;
	for (int i = 0; i < sz; i++)
	{
		local += 1;
	}
	n2 = local;
}

void single_thread()
{
	f1();
	f2();
}
void multi_thread()
{
	std::thread t1(f1);
	std::thread t2(f2);

	t1.join();
	t2.join();
}

int main()
{
	chronometry(single_thread);
	chronometry(multi_thread);
	chronometry(single_thread);
	chronometry(multi_thread);

}
