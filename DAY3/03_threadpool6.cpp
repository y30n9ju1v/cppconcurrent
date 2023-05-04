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

	// 1. 사용자가 "함수 + 인자" 를 전달합니다.
	// 2. 위 정보를 가지고 packaged_task 를 생성합니다.
	//    function<> : 함수와 인자를 보관만 가능
	//    packaged_task<> : 함수와 인자를 보관 + future 얻기
	// 
	// 3. 반환값을 담은 future 객체를 미리 꺼냅니다.
	template<typename F, typename ... ARGS>
	decltype(auto) add_task(F task, ARGS&& ... args)
	{
		using RT = decltype( task(args...) );

		// package_task 를 힙에 할당하고 shared_ptr로 관리
		auto p = std::make_shared<std::packaged_task<RT()>>
					(std::bind(task, args...));

		std::future<RT> ret = p->get_future();

		{
			std::lock_guard<std::mutex> g(m);

			// vector 는 function<> 으로 보관됩니다.
			// => 위에서 만든 packaged_task 를 실행하는 
			//    람다를 보관하게 하면 됩니다.
			task_q.push([p]() { (*p)(); });
		}
		cv.notify_one();

		return ret;
	}
};




int main()
{
	ThreadPool tp(3);

	tp.add_task(foo);
	tp.add_task(goo, 1, 3.4);
	tp.add_task(foo);
	tp.add_task(goo, 2, 5.5);
	tp.add_task(foo);

	getchar();
}
