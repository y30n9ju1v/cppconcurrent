#include <iostream>
#include <functional>

// 표준의 reference 의 원리를 생각해 봅시다.
template<typename T>
class reference_wrapper
{
	T* ptr;
public:
	reference_wrapper(T& obj) : ptr(&obj) {}

	// raw reference 로 암시적 변환 허용
	operator T& () { return *ptr; }
};

// reference_wrapper 개념
// => T& 처럼 참조로 동작하게 만든 간단한 클래스
// => raw reference 와의 차이점 대입 연산시
//    raw reference(T&) : 가리키던 값이 이동
//    reference_wrapper : 참조객체 자체가 이동

// 원리
// => 내부적으로 대상체의 주소를 보관
// => raw reference 로 변환도 가능


int main()
{
	int v1 = 10, v2 = 20;
	reference_wrapper<int> r1 = v1;
	reference_wrapper<int> r2 = v2;

	r1 = r2; // r1.operator=(r2)인데..
				// 컴파일러가 제공하는 디폴트 버전 사용
				// 결국의 객체의 주소 대입. => 참조가 이동하는 효과

	int& r = r1; // raw reference 와 호환 가능하게.
				 // r1.operator int&() 라는 변환 연산자 필요

	std::cout << v1 << std::endl; // 
	std::cout << v2 << std::endl; // 
	std::cout << r1 << std::endl; // 
	std::cout << r2 << std::endl; // 
		// 1. cout 으로 출력 가능한 타입으로 변환되는지 조사		
		// 2. cout << r2.operator int&() 로 변경!
}


