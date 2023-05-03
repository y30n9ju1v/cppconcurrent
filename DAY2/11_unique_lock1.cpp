#include <mutex>

// C++ ǥ�� mutex : 6�� �Դϴ�.
// C++ ǥ�� lock management : 4�� �Դϴ�

// std::lock_guard : ���� ������, ������, �Ҹ��ڸ� ����! �ܼ����
// 
// std::unique_lock: ���� ����� �����ϴ�. ���̽��ϴ�
//					 condition variable ���� �ݵ�� �ʿ�
// 
// std::shared_lock : shared_mutex ����
// std::scoped_lock : �������� mutex �� �����ϰ� lock


std::mutex m;

int main()
{
	// lock_guard �� ����ϴ� 2���� ���
	// 1. �����ڿ��� lock ȹ��
	{
		std::lock_guard<std::mutex> lg(m);
	}

	// 2. �̹� lock ȹ���� ������ ���ؽ� ����
	if (m.try_lock())
	{
		std::lock_guard<std::mutex> lg(m, std::adopt_lock);
	}

	
}



