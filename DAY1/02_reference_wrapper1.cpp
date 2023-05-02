#include <iostream>
#include <functional>

int main()
{
	int v1 = 10, v2 = 20;

//	int& r1 = v1;
//	int& r2 = v2;

	std::reference_wrapper<int> r1 = v1;
	std::reference_wrapper<int> r2 = v2;

	r1 = r2;

	// 아래 코드의 결과를 예측해 보세요
	//						raw reference  reference_wrapper
	std::cout << v1 << std::endl; // 20			10
	std::cout << v2 << std::endl; // 20			20
	std::cout << r1 << std::endl; // 20			20
	std::cout << r2 << std::endl; // 20			20
}
// C++ raw reference : 이동 불가능한 참조
//						대입연산시 "가리키던 값이 대입"
// std::reference_wrapper : 이동 가능한 참조
//						대입연산시 "참조 자체가 이동"



