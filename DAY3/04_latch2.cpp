#include <iostream>
#include <mutex>
#include <thread>
#include <latch>
#include <chrono>
using namespace std::literals;


std::latch complete_cnt(3); 

void foo(const std::string& name)
{
	std::cout << "start  work : " << name << std::endl;
	std::this_thread::sleep_for(1s);
	std::cout << "finish work : " << name << std::endl;

//	complete_cnt.count_down(); // --cnt

	complete_cnt.arrive_and_wait(); // --cnt 한후에
									// cnt == 0 까지 대기
	

	std::cout << "go home     : " << name << std::endl;
}

int main()
{
	std::jthread t1(foo, "kim"),
		t2(foo, "lee"),
		t3(foo, "park");

	std::cout << "receive signal" << std::endl;
}
