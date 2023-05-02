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

	// �Ʒ� �ڵ��� ����� ������ ������
	//						raw reference  reference_wrapper
	std::cout << v1 << std::endl; // 20			10
	std::cout << v2 << std::endl; // 20			20
	std::cout << r1 << std::endl; // 20			20
	std::cout << r2 << std::endl; // 20			20
}
// C++ raw reference : �̵� �Ұ����� ����
//						���Կ���� "����Ű�� ���� ����"
// std::reference_wrapper : �̵� ������ ����
//						���Կ���� "���� ��ü�� �̵�"



