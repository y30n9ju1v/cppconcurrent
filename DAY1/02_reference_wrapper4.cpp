#include <iostream>
#include <functional>
using namespace std::placeholders;

void foo(int n, int& r)
{
	r = 100;
}
int main()
{
	std::function<void(int)> f;

//	{
		int n = 0;
		// 2���Լ��� foo �� 2��° ���ڸ� "n"���� ������ 
		// ���ڰ� �Ѱ��� ���ο� �Լ� f �����.
		// f �� ���������� "0" �� �����ұ�� ? "n"�� �����ұ��?
		// f = std::bind(&foo, _1, n);  // n �� �ƴ� "n�� ��(0)" ����

		f = std::bind(&foo, _1, std::ref(n) ); // n�� �����ΰ���

//	} // <== n �� �̼��� �ı�

	f(0); // f �� ���ڰ� �Ѱ��� �����Լ�
		  // foo(0, n)
	std::cout << n << std::endl;
}

