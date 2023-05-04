#include <iostream>
#include <mutex>
#include <thread>
#include <latch>
#include <barrier>
#include <chrono>
using namespace std::literals;


//std::latch complete_cnt(3); // 1회용입니다.
							// count 가 0이 되면 더이상
							// 사용할수 없습니다.

//std::barrier complete_cnt(3); // 여러번 사용가능한 latch

void goo() noexcept
{
	std::cout << "====== complete =====\n";
}

std::barrier complete_cnt(3, goo); // goo 는 반드시 예외가 
									// 없어야 합니다.

void foo(const std::string& name)
{
	std::cout << "start  work : " << name << std::endl;
	std::this_thread::sleep_for(1s);
	std::cout << "finish work : " << name << std::endl;

	complete_cnt.arrive_and_wait(); // wait 통과시
									// 카운트는 다시 3으로..

	std::cout << "have dinner : " << name << std::endl;

	complete_cnt.arrive_and_wait();

	std::cout << "go home     : " << name << std::endl;
}

int main()
{
	std::jthread t1(foo, "kim"),
		t2(foo, "lee"),
		t3(foo, "park");

	std::cout << "receive signal" << std::endl;
}
