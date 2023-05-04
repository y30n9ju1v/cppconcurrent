#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> Q;

std::mutex m;

std::condition_variable cv;


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
			cv.wait(ul, []() { !Q.empty(); });
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
