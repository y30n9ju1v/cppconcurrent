//00_false_sharing1
#include <iostream>
#include <thread>
#include "chronometry.h"

constexpr int sz = 10000000; // 0 7개. 


// 해결책 1. 2개의 전역변수를 캐쉬 크기 만큼 떨어지게 합니다.
// 하나의 CPU 캐쉬에 2개 변수가 동시에 올라갈수 없게

/*
long long n1 = 0;
char padding[64];
long long n2 = 0;
*/

// 2. C++11 의 alignas 사용
// => n1, n2 주소를 출력해 보세요. alignas 가 없으므로 연속적으로 나오는데
//    alignas 사용하면 크기만큼 떨어지게 됩니다
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
