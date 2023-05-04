// 03_threadpool6.cpp

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <functional>
#include <memory>
#include <future>
#include <condition_variable>
using namespace std::literals;

void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
}

void goo(int a, double d)
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "goo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
}

//-------------------------------------------
class ThreadPool
{
	std::vector<std::thread> v;
	using TASK = std::function<void()>;
	std::queue<TASK> task_q;
	std::mutex m;
	std::condition_variable cv;
	bool stop = false;

public:
	ThreadPool(int cnt)
	{
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

	template<typename F, typename ... ARGS>
	decltype(auto) add_task(F task, ARGS&& ... args)
	{
		using RT = decltype(task(std::forward<ARGS>(args)...));

		auto p = std::make_shared<std::packaged_task<RT()>>
			(std::bind(task, std::forward<ARGS>(args)...));

		std::future<RT> ret = p->get_future();

		{
			std::lock_guard<std::mutex> g(m);

			task_q.push([p]() { (*p)(); });
		}
		cv.notify_one();

		return ret;
	}
};
//---------------------------------------------
int add(int a, int b)
{
	std::this_thread::sleep_for(5s);
	return a + b;
}

int main()
{
	ThreadPool tp(3);
	
	std::future<int> ft = tp.add_task(add, 1, 2);

	std::cout << "continue main" << std::endl;

	int ret = ft.get();

	std::cout << ret << std::endl;


	getchar();
}
