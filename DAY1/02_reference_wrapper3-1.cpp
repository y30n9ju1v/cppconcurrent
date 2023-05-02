#include <iostream>
#include <functional>

// ���� reference_wrapper �� ����ϳ��� ?
// => ������ ����� �ڵ忡 "������ ����" �ϰ� ������

void foo(int& a) { a = 100; }

template<typename T> void forward_foo(T value)
{
	foo(value);
}
int main()
{
	int n = 0;
	
//	forward_foo(n); // ���纻 ����
					// ������ �ƴ�����, n�� ������� ����
//	forward_foo(&n);// error. ������=> ���� ��ȯ �ȵǹǷ�

//	std::reference_wrapper<int> r(n);
//	forward_foo(r); 

	// std::ref() �� std::reference_wrapper �� �������ִ�
	// �����Լ� �Դϴ�.
	forward_foo( std::ref(n) );

	std::cout << n << std::endl;
}
// std::ref ����
template<typename T>
std::reference_wrapper<T> ref(T& obj)
{
	return std::reference_wrapper<T>(obj);
}