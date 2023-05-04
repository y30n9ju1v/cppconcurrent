#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std::literals;

void foo();

//-------------------------------------------
class ThreadPool
{
	std::vector<std::thread> v;

	using TASK = void(*)();

	std::queue<TASK> task_q;
	std::mutex m;
	std::condition_variable cv;
	bool stop = false; 

public:
	ThreadPool(int cnt)
	{
		// pool_thread_main 멤버 함수 이므로
		// std::thread t(&ThreadPool::pool_thread_main, this) 가되어야 합니다.
		for (int i = 0; i < cnt; i++)
			v.emplace_back(&ThreadPool::pool_thread_main, this);
	}

	void pool_thread_main()
	{
		while (true)
		{
			TASK task;
			{
				std::unique_lock<std::mutex> ul(m);

				cv.wait(ul, [this]() { return !task_q.empty(); });

				task = task_q.front();
				task_q.pop();
			}
			task(); 
		}
	}

	void add_task(TASK task)
	{
		{
			std::lock_guard<std::mutex> g(m);
			task_q.push(task);
		}
		cv.notify_one(); 
	}

};

int main()
{
	ThreadPool tp(3);

	tp.add_task(foo);
	tp.add_task(foo);
	tp.add_task(foo);
	tp.add_task(foo);
	tp.add_task(foo);

	getchar();
}





//--------------------------------------------------
void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
}
