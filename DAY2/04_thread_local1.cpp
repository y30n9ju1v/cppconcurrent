#include <iostream>
#include <thread>
#include <string_view>
// 3�� ����� ���������� ��ȯ �ϴ� �Լ�
// => �Ʒ� �ڵ�� �̱۽����忡���� �����մϴ�.
// => ��Ƽ ������ ���?
int next3times()
{
//	int n = 0;		// stack, ������� �Ѱ� �� ������
//	static int n = 0; // static ��� �����尡 ����.. 

	thread_local static int n = 0; 
					// ������� �Ѱ��� static �޸� ������ �Ҵ�
					// TSS(thread specifit storage)�Ǵ�
					// TLS(thread local storage) ��� �մϴ�
	n = n + 3;
	return n;
}

void foo(const std::string& name)
{
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
}
int main()
{
//	foo("A");

	std::thread t1(&foo, "A");
	std::thread t2(&foo, "\tB");

	t1.join();
	t2.join();
}

// �ٽ� : ���μ����� �����ϴ� �Ͱ� �����尡 �����ϴ°��� �����ؾ� �մϴ�.

// ���μ��� ���� : static(data) �޸�, ��, ����(����) �ڵ�.. 
//				A �����尡 ���� ������ �����尡 ���� �Ǿ
//				������ �ڵ����� close ���� �ʽ��ϴ�.
// 
// ������ ����  : ����, GUI�ڵ�(������ ���� ���鶧)
//				A �����尡 ���� ������� A������ ����� GUI �ı�
//				OS ���� �ٸ��� ����.



int g1 = 0; // �������� ��� �����尡 ���� �մϴ�.
thread_local int g2 = 0; // ������� ������ ��������
						// TSS ������ �Ҵ�˴ϴ�.

// �Ϲ������� OS���� TSS ������ ũ�Ⱑ ���� �Ǿ� �ֽ��ϴ�.
// => Ŀ�ٶ� ����Ÿ�� ����Ϸ��� �����庰�� ���� �Ҵ��ϰ�
//    TSS���� �ּҸ� �����ϼ���

// WIndows OS : TSS ũ��� sizeof(int)*1088 �Դϴ�.
