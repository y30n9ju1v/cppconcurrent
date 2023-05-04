#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> Q;

std::mutex m;

std::condition_variable cv;

// 아래 코드는 cv 를 사용해서 Q가 비어있을때 
// 소비자를 대기하게 하는 코드 입니다.

// 마지막 문제는 생산자가 너무 빨라서 Q가 가득 찰때 입니다.
// => 과제로 해보세요..(Q.size() == 10000 등의 조건으로 해보세요)

void producer()
{
	while (true)
	{
		static int cnt = 0;
		{
			std::lock_guard<std::mutex> g(m);

			Q.push(++cnt);
			std::cout << "producer : " << cnt << std::endl;
			if (cnt == 1000000) cnt = 0;
		}
		// 생산자는 생산후에.. 신호만 주면됩니다.
		cv.notify_one(); // 소비자가 대기중이 었다면 이때
						 // 깨어나게 됩니다.
	}
}
void consume()
{
	while (true)
	{
		{
			// 1. unique_lock 으로 뮤텍스를 획득
			std::unique_lock<std::mutex> ul(m);

			// 2. 무조건 Q를 사용하지 말고..,.
			//    조건을 만족할때만 사용
			//    조건을 만족하지 않으면 unlock 하고 대기

//			cv.wait(ul, !Q.empty()); // error
							// 2번째 인자는 bool 이 아닌
							// 함수 이어야 합니다.
							// 아래 처럼 람다표현식등을 사용하세요

			cv.wait(ul, []() { return !Q.empty(); });
					// => 조건을 조사 할때 Q의 멤버함수를 사용
					// => 별도의 전역변수가 없어도 됩니다.




			int element = Q.front();
			Q.pop();
			std::cout << "\tconsume : " << element << ", current Q size : " << Q.size() << std::endl;
		}
	}
}

int main()
{
	std::thread t1(producer);
	std::thread t2(consume);

	t1.join();
	t2.join();
}
