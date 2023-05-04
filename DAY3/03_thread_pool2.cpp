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

bool stop = false; // ������ Ǯ ���� �Ҷ� ���

//-----------------------------
// ������ Ǯ�� ��� ������� �Ʒ� �Լ��� �����ϰ� �˴ϴ�.
void pool_thread_main()
{
}

void init_pool(int cnt)
{
	// ��û�� ������ŭ�� �����带 ���� pool_thread_main ����
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
