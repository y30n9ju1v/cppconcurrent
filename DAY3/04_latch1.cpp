#include <iostream>
#include <mutex>
#include <thread>
#include <latch>

// C++11 : mutex, conditional_variable
// C++17 : shared_mutex
// C++20 : semaphore, latch, barrier

// latch : 카운팅 기반의 간단한 동기화 도구
//         없어도 condition_variable로 만들면 되지만
//         직접 구현할 필요 없이 간단하게 사용가능.

std::latch complete_cnt(3); // 내부적으로 "3"을 보관합니다.
							// wait() 멤버 함수로 0이 될때까지
							// 대기 가능. 

void foo(const std::string& name)
{
	std::cout << "start  work : " << name << std::endl;
	std::cout << "finish work : " << name << std::endl;

	complete_cnt.count_down(); // 카운트 감소
	
	std::cout << "go home     : " << name << std::endl;
}
int main()
{
	std::jthread t1(foo, "kim"), 
		         t2(foo, "lee"), 
		         t3(foo, "park");
	
	complete_cnt.wait(); // 카운트가 0이 될때까지 대기

	std::cout << "receive signal" << std::endl;
}
