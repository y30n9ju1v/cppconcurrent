#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// 일반 함수 : 반환 값으로 결과 반환
int add1(int a, int b)
{
	int s = a + b;
	return s;
}

// out parameter 사용
void add2(int a, int b, int& s)
{
	s = a + b;
	std::this_thread::sleep_for(3s);
}

// promise 를 사용하는 모델
void add3(int a, int b, std::promise<int>& p)
{
	int s = a + b;

	// 연산이 종료되었으면 결과를 promise 객체의 멤버 함수로 알려준다
	// => 이순간 연산의 결과를 대기중인 스레드가 깨어 나게 됩니다.
	p.set_value(s);

	std::this_thread::sleep_for(3s);
}

int main()
{
	// 1. promise 객체를 생성합니다
	std::promise<int> pr;

	// 2. promise 객체에서 미래의 결과를 담은 future 객체 꺼냅니다.
	std::future<int> ft = pr.get_future();

	// 3. 스레드를 생성할때 promise 객체를 참조로 전달
	std::thread t(add3, 1, 2, std::ref(pr));

	// 이제 주스레드는 다른 작업을 수행하면 됩니다.
	std::cout << "continue main\n";

	// 4. 스레드의 결과가 필요 할때 future 객체에서 꺼내면 됩니다.
	int ret = ft.get(); // 결과가 있으면 즉시 꺼내고
						// 없으면(스레드가 아직 연산중이면)
						// 결과가 나올때 까지 대기.

	std::cout << ret << std::endl;
}
// promise 만 사용하면 되지 ?? 왜 future 로 나누나요 ?
// => 일반화된 모델 설계
// => promise & future
// => packaged_task & future
// => async & future

// 여러개의 future 를 만들어서 여러 스레드가 
// 하나의 결과를 대기하는 기술도 가능