#include <iostream>
#include <functional>

// ǥ���� reference �� ������ ������ ���ô�.
template<typename T>
class reference_wrapper
{
	T* ptr;
public:
	reference_wrapper(T& obj) : ptr(&obj) {}

	// raw reference �� �Ͻ��� ��ȯ ���
	operator T& () { return *ptr; }
};

// reference_wrapper ����
// => T& ó�� ������ �����ϰ� ���� ������ Ŭ����
// => raw reference ���� ������ ���� �����
//    raw reference(T&) : ����Ű�� ���� �̵�
//    reference_wrapper : ������ü ��ü�� �̵�

// ����
// => ���������� ���ü�� �ּҸ� ����
// => raw reference �� ��ȯ�� ����


int main()
{
	int v1 = 10, v2 = 20;
	reference_wrapper<int> r1 = v1;
	reference_wrapper<int> r2 = v2;

	r1 = r2; // r1.operator=(r2)�ε�..
				// �����Ϸ��� �����ϴ� ����Ʈ ���� ���
				// �ᱹ�� ��ü�� �ּ� ����. => ������ �̵��ϴ� ȿ��

	int& r = r1; // raw reference �� ȣȯ �����ϰ�.
				 // r1.operator int&() ��� ��ȯ ������ �ʿ�

	std::cout << v1 << std::endl; // 
	std::cout << v2 << std::endl; // 
	std::cout << r1 << std::endl; // 
	std::cout << r2 << std::endl; // 
		// 1. cout ���� ��� ������ Ÿ������ ��ȯ�Ǵ��� ����		
		// 2. cout << r2.operator int&() �� ����!
}


