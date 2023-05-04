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
	~ThreadPool()
	{
		{
			std::lock_guard<std::mutex> g(m);
			stop = true;  // 종료하라고 flag 변경
		}
		cv.notify_all(); // 대기 중인 모든 스레드 깨우기.

		// 실제 종료될때 까지 대기
		for (auto& t : v)
			t.join();
	}

	void pool_thread_main()
	{
		while (true)
		{
			TASK task;
			{
				std::unique_lock<std::mutex> ul(m);

				cv.wait(ul, [this]() { return stop || !task_q.empty(); });

				if (stop == true && task_q.empty())
					break; // 무한루프 탈출...
							// 즉, 풀에 있는 스레드 종료

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
	//					  std::async(add, 1, 2);

	std::cout << "continue main" << std::endl;

	int ret = ft.get();

	std::cout << ret << std::endl;

}	// <== tp 소멸자 호출됩니다.
    // <== 풀에서 작업중인 스레드가 있다면 작업마칠때 까지 대기해야합니다.
// 우리가 만든 ThreadPool : 최초에 원하는 갯수만큼 의 스레드 생성
// 
// std::async : 구현에 따라 다를수 있지만 대부분
//			작업이 들어 오면 스레드 생성, 작업종료되면 대기 상태
//		    새로운 작업들어오면 대기중인 스레드 있으면 사용
//		    없으면 새로 생성