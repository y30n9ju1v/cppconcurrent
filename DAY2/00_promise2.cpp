#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// �Ϲ� �Լ� : ��ȯ ������ ��� ��ȯ
int add1(int a, int b)
{
	int s = a + b;
	return s;
}

// out parameter ���
void add2(int a, int b, int& s)
{
	s = a + b;
	std::this_thread::sleep_for(3s);
}

// promise �� ����ϴ� ��
void add3(int a, int b, std::promise<int>& p)
{
	int s = a + b;

	// ������ ����Ǿ����� ����� promise ��ü�� ��� �Լ��� �˷��ش�
	// => �̼��� ������ ����� ������� �����尡 ���� ���� �˴ϴ�.
	p.set_value(s);

	std::this_thread::sleep_for(3s);
}

int main()
{
	// 1. promise ��ü�� �����մϴ�
	std::promise<int> pr;

	// 2. promise ��ü���� �̷��� ����� ���� future ��ü �����ϴ�.
	std::future<int> ft = pr.get_future();

	// 3. �����带 �����Ҷ� promise ��ü�� ������ ����
	std::thread t(add3, 1, 2, std::ref(pr));

	// ���� �ֽ������ �ٸ� �۾��� �����ϸ� �˴ϴ�.
	std::cout << "continue main\n";

	// 4. �������� ����� �ʿ� �Ҷ� future ��ü���� ������ �˴ϴ�.
	int ret = ft.get(); // ����� ������ ��� ������
						// ������(�����尡 ���� �������̸�)
						// ����� ���ö� ���� ���.

	std::cout << ret << std::endl;
}
// promise �� ����ϸ� ���� ?? �� future �� �������� ?
// => �Ϲ�ȭ�� �� ����
// => promise & future
// => packaged_task & future
// => async & future

// �������� future �� ���� ���� �����尡 
// �ϳ��� ����� ����ϴ� ����� ����