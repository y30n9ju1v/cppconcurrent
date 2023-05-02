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
}


