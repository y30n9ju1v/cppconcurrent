#include <iostream>
#include <functional>
using namespace std::placeholders;

void foo(int n, int& r)
{
	r = 100;
}
int main()
{
	std::function<void(int)> f;

//	{
		int n = 0;
		// 2항함수인 foo 의 2번째 인자를 "n"으로 고정한 
		// 인자가 한개인 새로운 함수 f 만들기.
		// f 가 내부적으로 "0" 을 보관할까요 ? "n"을 보관할까요?
		// f = std::bind(&foo, _1, n);  // n 이 아닌 "n의 값(0)" 보관

		f = std::bind(&foo, _1, std::ref(n) ); // n을 참조로고정

//	} // <== n 은 이순간 파괴

	f(0); // f 는 인자가 한개인 단항함수
		  // foo(0, n)
	std::cout << n << std::endl;
}

