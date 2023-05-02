#include <iostream>
#include <functional>

// ���� reference_wrapper �� ����ϳ��� ?
// => ������ ����� �ڵ忡 "������ ����" �ϰ� ������

void foo(int& a) { a = 100; }

template<typename T>
void forward_foo(T value)
{
	foo(value);
}
int main()
{
	int n = 0;
	foo(n);
	std::cout << n << std::endl;
}