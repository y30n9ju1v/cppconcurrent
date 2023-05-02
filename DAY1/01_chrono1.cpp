#include <iostream>
#include <thread>
#include <chrono>	// C++11
					// �ð� ����
using namespace std::literals; 

int main()
{
	std::chrono::seconds s1(10); // 10 ���� �ǹ�
	std::chrono::minutes m1(3);
	std::chrono::milliseconds ms(10);

	// �ð� ���� ��ü�� ���� �������
	// "user define literal" ���
	auto s2 = 10s;
	auto m2 = 10min;

	// ���罺���带 ��� ����ϴ� ���(sleep)
	// std::this_thread::sleep_for(�ð�);
	// std::this_thread::sleep_for(10);	// error. ������ �ƴ�
										// �ð� Ÿ������ ����.
	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::this_thread::sleep_for(10s);
}