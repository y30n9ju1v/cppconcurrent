#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> Q;

std::mutex m;

// 아래 코드는 "mutex" 로 동시접근을 막고 있습니다.
// => 생산자/소비자가 동시에 Q에 접근할수 없습니다.

// 하지만 Q에 데이타가 없을때(비었을때)
// 소비자가 소비하면 문제가 됩니다.
// => Q가 비었으면 소비자가 대기하다가
// => 생산자가 생산하면 소비자가 깨어나야 합니다.

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
	}
}
void consume()
{
	while (true)
	{
		{
			std::lock_guard<std::mutex> g(m);
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
