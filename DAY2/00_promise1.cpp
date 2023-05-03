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

// 함수의 결과를 꺼내가기 위해서 out parameter를 사용하는 코드
void add2(int a, int b, int& s)
{
	s = a + b;
}
int main()
{
	// 핵심 1. 스레드가 아닌 직접 호출은 함수의 결과를 반환값으로 받으면 됩니다.
	int ret1 = add1(1, 2);

	// 핵심 2. 
	int ret2 = 0;
	std::thread t(add2, 1, 2, std::ref(ret2));

	t.join();
	std::cout << ret2 << std::endl;
}
