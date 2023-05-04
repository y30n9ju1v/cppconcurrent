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
}

void init_pool(int cnt)
{
	// 요청한 갯수만큼의 스레드를 만들어서 pool_thread_main 실행
	for (int i = 0; i < cnt; i++)
		v.emplace_back(pool_thread_main);
}

int main()
{
	init_pool(10);
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
