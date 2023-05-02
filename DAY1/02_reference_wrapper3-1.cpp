#include <iostream>
#include <functional>

// 언제 reference_wrapper 를 사용하나요 ?
// => 값으로 설계된 코드에 "참조로 전달" 하고 싶을때

void foo(int& a) { a = 100; }

template<typename T>
void forward_foo(T value)
{
	foo(value);
}

int main()
{
	int n = 0;
	
	forward_foo(n); // 복사본 생성

//	std::reference_wrapper<int> r(n);
//	forward_foo(r); 

	std::cout << n << std::endl;
}