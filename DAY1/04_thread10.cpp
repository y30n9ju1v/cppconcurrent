#include <vector>
#include <algorithm>
#include <thread>
#include <iostream>
#include <execution>
#include <syncstream> // C++20 부터 제공되는 헤더

void foo(int a)
{
	// std::cout : 여러 스레드가 동시에 화면 출력하면
	//			   출력 자체가 동기화안됩니다
//	std::cout << a << " : " << std::this_thread::get_id() << std::endl;

	std::osyncstream out(std::cout);

	out << a << " : " << std::this_thread::get_id() << std::endl;
}   

int main() 
{
	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };

//	std::for_each(v.begin(), v.end(), foo);

	// C++17 부터 STL 알고리즘의 병렬 버전을 제공
	// => 69개의 알고리즘이 병렬 버전 사용가능
	// => 우리가 만든 "parallel_sum" 과 유사합니다.
	std::for_each(std::execution::par, v.begin(), v.end(), foo);
	    
}