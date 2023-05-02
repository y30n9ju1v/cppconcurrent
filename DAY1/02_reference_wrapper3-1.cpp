#include <iostream>
#include <functional>

// 언제 reference_wrapper 를 사용하나요 ?
// => 값으로 설계된 코드에 "참조로 전달" 하고 싶을때

void foo(int& a) { a = 100; }

template<typename T> void forward_foo(T value)
{
	foo(value);
}
int main()
{
	int n = 0;
	
//	forward_foo(n); // 복사본 생성
					// 에러는 아니지만, n이 변경되지 않음
//	forward_foo(&n);// error. 포인터=> 참조 변환 안되므로

//	std::reference_wrapper<int> r(n);
//	forward_foo(r); 

	// std::ref() 가 std::reference_wrapper 를 생성해주는
	// 도움함수 입니다.
	forward_foo( std::ref(n) );

	std::cout << n << std::endl;
}
// std::ref 원리
template<typename T>
std::reference_wrapper<T> ref(T& obj)
{
	return std::reference_wrapper<T>(obj);
}