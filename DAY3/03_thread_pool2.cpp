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
	while (true)
	{
		TASK task;
		{
			std::unique_lock<std::mutex> ul(m);

			// �Ʒ� �ڵ尡 Ǯ���� "�����尡 ���"���̶�� �ǹ� �Դϴ�.
			cv.wait(ul, []() { return !task_q.empty(); });

			task = task_q.front();
			task_q.pop();
		}
		task(); // �۾� ����.
	}
}

void init_pool(int cnt)
{
	// ��û�� ������ŭ�� �����带 ���� pool_thread_main ����
	for (int i = 0; i < cnt; i++)
		v.emplace_back(pool_thread_main);
//		v.push_back(std::thread(pool_thread_main)); // ���� ����
}

// �۾�(�Լ�)�� Q�� �ִ� �Լ�
void add_task(TASK task)
{
	{
		std::lock_guard<std::mutex> g(m);
		task_q.push(task);
	}
	cv.notify_one(); // �۾��� ��� �����Ƿ� 
					 // ������� ������� �߿��� �Ѱ��� �����!
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
