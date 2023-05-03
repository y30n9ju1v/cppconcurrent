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
	// 그럼 옵션이 시스템 상황에 맞지 않는 경우에는, 예외가 발생 할까요?
	// => 아래 처럼 한후. 멀티스레드가 지원되지 않은 시스템에서 실행하면
	//    "std::system_error" 타입의 예외 발생
	std::future<void> ft = std::async(std::launch::async, foo);
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
// "return 값"의 종류에 따른 제약은 없을까요?
// std::tuple 이라던지, task 자체도 return 할 수 있나요?
// => 특별한 제약없습니다. task 도 가능.