#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

void foo()
{
//	std::lock_guard<std::mutex> lg(m); // �����ڿ��� m.lock()
//						// lock �� ȹ������ ���ϸ� ���

	if (m.try_lock())
	{
//		std::lock_guard<std::mutex> g(m); // ����...
						// m�� �̹� lock �� �� ����

		// �Ʒ� ó�� �ϸ�.. �̹� lock �� mutex ��
		// lock_guard�� ����(�ڵ� unlock) �Ҽ� �ֽ��ϴ�.
		std::lock_guard<std::mutex> g(m, std::adopt_lock);

		std::cout << "using shared data" << std::endl;

		//m.unlock(); // ���� �ڵ�
	}
	else
	{

	}
}



int main()
{
	std::thread t1(foo);
	std::thread t2(foo);
	t1.join();
	t2.join();
}



