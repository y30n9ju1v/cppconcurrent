#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std::literals;

void foo();

//-------------------------------------------
std::vector<std::thread> v;

using TASK = void(*)();

std::queue<TASK> task_q;
std::mutex m;
std::condition_variable cv;

bool stop = false; // 스레드 풀 종료 할때 사용

//-----------------------------
// 스레드 풀의 모든 스레드는 아래 함수를 실행하게 됩니다.
void pool_thread_main()
{
	while (true)
	{
		TASK task;
		{
			std::unique_lock<std::mutex> ul(m);

			// 아래 코드가 풀에서 "스레드가 대기"중이라는 의미 입니다.
			cv.wait(ul, []() { return !task_q.empty(); });

			task = task_q.front();
			task_q.pop();
		}
		task(); // 작업 실행.
	}
}

void init_pool(int cnt)
{
	// 요청한 갯수만큼의 스레드를 만들어서 pool_thread_main 실행
	for (int i = 0; i < cnt; i++)
		v.emplace_back(pool_thread_main);
//		v.push_back(std::thread(pool_thread_main)); // 위와 동일
}

// 작업(함수)를 Q에 넣는 함수
void add_task(TASK task)
{
	{
		std::lock_guard<std::mutex> g(m);
		task_q.push(task);
	}
	cv.notify_one(); // 작업이 들어 왔으므로 
					 // 대기중인 스레드들 중에서 한개를 깨운다!
}  
int main()
{
	init_pool(3);

	add_task(foo);
	add_task(foo);
	add_task(foo);
	add_task(foo);
	add_task(foo);

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
