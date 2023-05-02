#include <chrono>
#include <iostream>
#include <thread>
using namespace std::literals;

// C++20 �� jthread �� "������ ���" ���� ���� �մϴ�.

void foo(std::stop_token token)
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "foo : " << i << std::endl;

        // �ֱ������� ��ӵ� "cancel flag" �� Ȯ�� �մϴ�.
        if ( token.stop_requested() )
            break;
    }
    // ����ϴ� �ڿ����� release...
    std::cout << "������ �۾��ϰ�.. finish foo\n";
}
void goo() {}

int main()
{
    // �ٽ� 1. jthread ���ڷ� ��� �͵� ������ ���� �ʽ��ϴ�
    std::jthread j1(&goo);
    std::jthread j2(&foo);  // ���ڸ� �������� �ʽ��ϴ�
                       // ������ stop_token�� ���޵ǰ� �ֽ��ϴ�
    std::this_thread::sleep_for(2s);

    j2.request_stop(); // ���� �޶�
    j1.request_stop(); // ��û�Ҽ� ������
                        // Ż�� ������ �����Ƿ� ���� �˴ϴ�.

}

