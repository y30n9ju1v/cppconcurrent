#include <iostream>
#include <mutex>
#include <thread>
#include <latch>
#include <barrier>
#include <chrono>
using namespace std::literals;


//std::latch complete_cnt(3); // 1ȸ���Դϴ�.
							// count �� 0�� �Ǹ� ���̻�
							// ����Ҽ� �����ϴ�.

//std::barrier complete_cnt(3); // ������ ��밡���� latch

void goo() noexcept
{
	std::cout << "====== complete =====\n";
}

std::barrier complete_cnt(3, goo); // goo �� �ݵ�� ���ܰ� 
									// ����� �մϴ�.

void foo(const std::string& name)
{
	std::cout << "start  work : " << name << std::endl;
	std::this_thread::sleep_for(1s);
	std::cout << "finish work : " << name << std::endl;

	complete_cnt.arrive_and_wait(); // wait �����
									// ī��Ʈ�� �ٽ� 3����..

	std::cout << "have dinner : " << name << std::endl;

	complete_cnt.arrive_and_wait();

	std::cout << "go home     : " << name << std::endl;
}

int main()
{
	std::jthread t1(foo, "kim"),
		t2(foo, "lee"),
		t3(foo, "park");

	std::cout << "receive signal" << std::endl;
}
