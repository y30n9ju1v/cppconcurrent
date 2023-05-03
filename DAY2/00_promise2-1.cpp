#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;


//void add3(int a, int b, std::promise<int>& p)
void add3(int a, int b, std::promise<int>&& p)
{
	int s = a + b;

	p.set_value(s);

	std::this_thread::sleep_for(3s);
}

int main()
{
	std::promise<int> pr;
	std::future<int> ft = pr.get_future();

	// 주스레드에서는 future를 꺼낸후에는 promise 를 더이상
	// 필요 없습니다.
	// 그래서 스레드에 전달할때
	// 1. reference 로 전달해도 되고
	// 2. std::move 로 전달해도 됩니다.
//	std::thread t(add3, 1, 2, std::ref(pr));
	std::thread t(add3, 1, 2, std::move(pr));

	std::cout << "continue main\n";

	int ret = ft.get(); 

	std::cout << ret << std::endl;
}
