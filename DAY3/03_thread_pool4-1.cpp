// threadpool4-1
#include <functional>

void foo(int a, int b) {}

int main()
{
	// C�� �Ϲ� �Լ� �����ʹ� �ݵ�� �Լ� ����� �����ؾ� �մϴ�.
	void(*f)() = &foo; // error

	// std::function �� std::bind �� ����ϸ� ���ڸ� �����ؼ�
	// ��������
	std::function<void()> f1;
	f1 = &foo;
	f1();
}