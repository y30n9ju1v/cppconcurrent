#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> Q;

std::mutex m;

std::condition_variable cv;

// �Ʒ� �ڵ�� cv �� ����ؼ� Q�� ��������� 
// �Һ��ڸ� ����ϰ� �ϴ� �ڵ� �Դϴ�.

// ������ ������ �����ڰ� �ʹ� ���� Q�� ���� ���� �Դϴ�.
// => ������ �غ�����..(Q.size() == 10000 ���� �������� �غ�����)

void producer()
{
	while (true)
	{
		static int cnt = 0;
		{
			std::lock_guard<std::mutex> g(m);

			Q.push(++cnt);
			std::cout << "producer : " << cnt << std::endl;
			if (cnt == 1000000) cnt = 0;
		}
		// �����ڴ� �����Ŀ�.. ��ȣ�� �ָ�˴ϴ�.
		cv.notify_one(); // �Һ��ڰ� ������� ���ٸ� �̶�
						 // ����� �˴ϴ�.
	}
}
void consume()
{
	while (true)
	{
		{
			// 1. unique_lock ���� ���ؽ��� ȹ��
			std::unique_lock<std::mutex> ul(m);

			// 2. ������ Q�� ������� ����..,.
			//    ������ �����Ҷ��� ���
			//    ������ �������� ������ unlock �ϰ� ���

//			cv.wait(ul, !Q.empty()); // error
							// 2��° ���ڴ� bool �� �ƴ�
							// �Լ� �̾�� �մϴ�.
							// �Ʒ� ó�� ����ǥ���ĵ��� ����ϼ���

			cv.wait(ul, []() { return !Q.empty(); });
					// => ������ ���� �Ҷ� Q�� ����Լ��� ���
					// => ������ ���������� ��� �˴ϴ�.




			int element = Q.front();
			Q.pop();
			std::cout << "\tconsume : " << element << ", current Q size : " << Q.size() << std::endl;
		}
	}
}

int main()
{
	std::thread t1(producer);
	std::thread t2(consume);

	t1.join();
	t2.join();
}
