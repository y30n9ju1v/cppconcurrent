#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

void foo()
{
//	std::lock_guard<std::mutex> lg(m); // 생성자에서 m.lock()
//						// lock 을 획득하지 못하면 대기

	if (m.try_lock())
	{
//		std::lock_guard<std::mutex> g(m); // 버그...
						// m은 이미 lock 이 된 상태

		// 아래 처럼 하면.. 이미 lock 된 mutex 를
		// lock_guard로 관리(자동 unlock) 할수 있습니다.
		std::lock_guard<std::mutex> g(m, std::adopt_lock);

		std::cout << "using shared data" << std::endl;

		//m.unlock(); // 나쁜 코드
	}
	else
	{

	}
}



int main()
{
	std::thread t1(foo);
	std::thread t2(foo);
	t1.join();
	t2.join();
}



