#include <iostream>
#include <thread>
#include <string_view>
// 3의 배수를 순차적으로 반환 하는 함수
// => 아래 코드는 싱글스레드에서는 안전합니다.
// => 멀티 스레드 라면?
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



