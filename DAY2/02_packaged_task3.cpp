#include <iostream>
#include <thread>
#include <future>
int add(int a, int b)
{
	return a + b;
}

int main()
{
	std::packaged_task<int(int, int)> task(add);
	// task 에 담긴 작업을 2번 실행하는 경우.
	task(1, 2);
	task(1, 2);


}


