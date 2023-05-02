#include <iostream>
#include <thread>

// join_thread 

void foo(int a, int b)
{
	std::cout << "foo : " << a << ", " << b << std::endl;
}

// �Ҹ��ڿ��� �ڵ����� join �Ǵ� ������ Ŭ����
class scoped_thread
{
	std::thread impl;
public:
	scoped_thread(std::thread&& t) : impl(std::move(t)) {}

	~scoped_thread()
	{
		if (impl.joinable())
			impl.join();
	}
};


int main()
{
	// 1. std::thread ����, �׻� join()/detach()�ʿ�
    std::thread t1(&foo, 10, 20);
	t1.join();

	//
	std::thread t2(&foo, 10, 20);
	scoped_thread sc1( std::move(t2) );

	scoped_thread sc2( std::thread(&foo, 10, 20) );
}

