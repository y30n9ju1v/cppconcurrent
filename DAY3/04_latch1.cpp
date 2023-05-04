#include <iostream>
#include <mutex>
#include <thread>
#include <latch>

// C++11 : mutex, conditional_variable
// C++17 : shared_mutex
// C++20 : semaphore, latch, barrier

// latch : ī���� ����� ������ ����ȭ ����
//         ��� condition_variable�� ����� ������
//         ���� ������ �ʿ� ���� �����ϰ� ��밡��.

std::latch complete_cnt(3); // ���������� "3"�� �����մϴ�.
							// wait() ��� �Լ��� 0�� �ɶ�����
							// ��� ����. 

void foo(const std::string& name)
{
	std::cout << "start  work : " << name << std::endl;
	std::cout << "finish work : " << name << std::endl;

	complete_cnt.count_down(); // ī��Ʈ ����
	
	std::cout << "go home     : " << name << std::endl;
}
int main()
{
	std::jthread t1(foo, "kim"), 
		         t2(foo, "lee"), 
		         t3(foo, "park");
	
	complete_cnt.wait(); // ī��Ʈ�� 0�� �ɶ����� ���

	std::cout << "receive signal" << std::endl;
}
