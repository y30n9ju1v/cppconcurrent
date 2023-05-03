#include <iostream>
#include <thread>
#include <future>

int add(int a, int b)
{
	return a + b;
}

int main()
{
	// packaged_task : 작업(함수)을 보관했다가 필요 할때 실행
	// async : 작업을 즉시 비동기(스레드)로 실행.

	std::future<int> ft = std::async(add, 1, 2);

	int ret = ft.get();

	std::cout << ret << std::endl;
}
