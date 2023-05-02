#include <iostream>
#include <thread>
#include <chrono>	// C++11
					// 시간 관련
using namespace std::literals; 

int main()
{
	std::chrono::seconds s1(10); // 10 초의 의미
	std::chrono::minutes m1(3);
	std::chrono::milliseconds ms(10);

	// 시간 관련 객체를 쉽게 만들려면
	// "user define literal" 사용
	auto s2 = 10s;
	auto m2 = 10min;

	// 현재스레드를 잠시 대기하는 방법(sleep)
	// std::this_thread::sleep_for(시간);
	// std::this_thread::sleep_for(10);	// error. 정수가 아닌
										// 시간 타입으로 전달.
	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::this_thread::sleep_for(10s);
}