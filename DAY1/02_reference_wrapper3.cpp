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
//	foo(n); // n을 참조로 전달.
	
	// forward_foo 는 값으로 설계된 함수 이므로 아래 처럼 보내면
	//forward_foo(n); // 복사본 생성

//	forward_foo(&n); // 주소를 보내면 ??
					// 메모리 정보(주소)를 보내긴했지만
					// 포인터 => 참조 로의 변환이 안되므로 error

	std::reference_wrapper<int> r(n);
	forward_foo(r); // ok.. 값으로 설계된 라이브러리에
					// 참조로 변수를 전달하는 기술.

	std::cout << n << std::endl;
}