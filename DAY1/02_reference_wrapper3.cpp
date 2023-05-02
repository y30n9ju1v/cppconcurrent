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
//	foo(n); // n�� ������ ����.
	
	// forward_foo �� ������ ����� �Լ� �̹Ƿ� �Ʒ� ó�� ������
	//forward_foo(n); // ���纻 ����

//	forward_foo(&n); // �ּҸ� ������ ??
					// �޸� ����(�ּ�)�� ������������
					// ������ => ���� ���� ��ȯ�� �ȵǹǷ� error

	std::reference_wrapper<int> r(n);
	forward_foo(r); // ok.. ������ ����� ���̺귯����
					// ������ ������ �����ϴ� ���.

	std::cout << n << std::endl;
}