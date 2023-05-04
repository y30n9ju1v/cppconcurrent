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
	//f1 = &foo;	// error. foo �� ���ڰ� 2�� �ε�
				// f1�� ���ڰ� ���� �Լ� �� ����

	f1 = std::bind(&foo, 1, 2); // foo �� ���� 2���� ���� ����
	f1(); // foo(1,2);
}