//00_false_sharing1
#include <iostream>
#include <thread>
#include "chronometry.h"

constexpr int sz = 10000000; // 0 7��. 


// �ذ�å 1. 2���� ���������� ĳ�� ũ�� ��ŭ �������� �մϴ�.
// �ϳ��� CPU ĳ���� 2�� ������ ���ÿ� �ö󰥼� ����

/*
long long n1 = 0;
char padding[64];
long long n2 = 0;
*/

// 2. C++11 �� alignas ���
// => n1, n2 �ּҸ� ����� ������. alignas �� �����Ƿ� ���������� �����µ�
//    alignas ����ϸ� ũ�⸸ŭ �������� �˴ϴ�
alignas(64) long long n1 = 0;
alignas(64) long long n2 = 0;


void f1()
{

	for (int i = 0; i < sz; i++)
	{
		n1 += 1;
	}
}
void f2()
{
	for (int i = 0; i < sz; i++)
	{
		n2 += 1;
	}
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
