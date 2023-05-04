//00_false_sharing1
#include <iostream>
#include <thread>
#include "chronometry.h"

constexpr int sz = 10000000; // 0 7개. 

long long n1 = 0;
long long n2 = 0;
// 핵심 : f1, f2 는 서로 다른 변수에 결과 보관(n1, n2)
void f1()
{
	// 천만번 루프 n1 1증가
	for (int i = 0; i < sz; i++)
	{
		n1 += 1;
	}
}
void f2()
{
	// f1 함수와 동일, 단 n2에 결과 보관
	for (int i = 0; i < sz; i++)
	{
		n2 += 1;
	}
}

void single_thread()
{	
	// 하나의 스레드로 순차적으로 2개 작업 수행
	f1();
	f2();
}
void multi_thread()
{
	// 2개의 스레드로 각각 작업 수행
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
