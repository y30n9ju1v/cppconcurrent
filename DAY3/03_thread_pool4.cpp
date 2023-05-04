#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>
using namespace std::literals;

void foo();

//-------------------------------------------
class ThreadPool
{
	std::vector<std::thread> v;

//	using TASK = void(*)(); // 이렇게 하면 인자 없는 함수만 가능
	using TASK = std::function<void()>;
							// 이렇게 하면 std::bind()로인자를
							// 고정해서 모든 함수 보관가능

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

	// 모든 모양의 함수를 받기 위해 가변인자 템플릿 도입
	template<typename ... ARGS>
	void add_task(TASK task, ARGS&& ... args)
	{
		// "함수 + 인자들" 을 묶어서 f에 보관
		std::function<void()> f = std::bind(task, args...);
//		f(); // f는 인자 없는 함수 처럼 사용.. 
			 // task(인자들) 로 호출
		{
			std::lock_guard<std::mutex> g(m);
			task_q.push(f);
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
