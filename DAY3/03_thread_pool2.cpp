#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std::literals;

void foo();

using TASK = void(*)();

std::queue<TASK> task_q;
std::mutex m;
std::condition_variable cv;

bool stop = false;
std::vector<std::thread> v;








int main()
{

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
