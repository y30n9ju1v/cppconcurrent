#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

// async의 예외처리는 어떻게 하나요 ?
// => get 에서 catch 하면 됩니다.

void foo()
{
	throw std::runtime_error("foo fail");
}
int main()
{
	// 반환 값이 없으면 아래 처럼 하면 됩니다.
	std::future<void> ft = std::async(foo);
	try
	{
		ft.get();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	// async 사용시에 join이나 detach은 따로 필요하지 않나요 ?
	// => 필요 없습니다.
}