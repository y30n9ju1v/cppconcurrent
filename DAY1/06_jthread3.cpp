#include <iostream>
#include <thread>

void foo(int a, int b)
{
    std::cout << "foo : " << a << ", " << b << std::endl;
}

int main()
{
    // C++11 �� std::thread �� �ݵ�� ����ڰ� join()�ؾ� �մϴ�
    /*
    std::thread t1(&foo, 10, 20);
    std::thread t2(&foo, 10, 20);
    t1.join();
    t2.join();
    */

    // C++20 �� jthread�� �Ҹ��ڿ��� �ڵ����� join ȣ���մϴ�.
    // => ������ jthread2.cpp �� join_thread �ڵ� ����
    // => g++ �ҽ�.cpp -std=c++20
    std::jthread t1(&foo, 10, 20);
    std::jthread t2(&foo, 10, 20);

}

