#include <iostream>

int main()
{
	int arr1[4] = { 1,2,3,4 };
	int arr2[4] = { 5,6,7,8 };
	int arr3[4] = { 0 };

	// MIMD : Multiple Instruction Multiple Data
	//        => 여러개의 명령으로 여러개의 데이타 처리
	// SIMD : Single Instruction Multiple Data

	for (int i = 0; i < 4; i++)
	{
		arr3[i] = arr1[i] + arr2[i];
	}

	for (auto e : arr3)
		std::cout << e << std::endl;
}