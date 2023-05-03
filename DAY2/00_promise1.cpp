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
// 단점 : 주스레드에서 연산의 결과를 대기 할수 없습니다.
// 해결책
// 1. promise & future
// 2. packaged_task
// 3. async
void add2(int a, int b, int& s)
{
	s = a + b;

	// 연산은 완료가 되었는데.. 마무리 작업에 시간이 걸린다고 가정
	std::this_thread::sleep_for(3s);
}
int main()
{
	// 핵심 1. 스레드가 아닌 직접 호출은 함수의 결과를 반환값으로 받으면 됩니다.
	int ret1 = add1(1, 2);

	// 핵심 2. 
	int ret2 = 0;
	std::thread t(add2, 1, 2, std::ref(ret2));

	t.join();	// 연산의 종료가 아닌 스레드의 종료를 대기.
	std::cout << ret2 << std::endl;
}
