#include <chrono>
#include <iostream>
#include <thread>
using namespace std::literals;

void foo(bool& flag)
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "foo : " << i << std::endl;

        // �ֱ������� ��ӵ� "cancel flag" �� Ȯ�� �մϴ�.
        if (flag == true)
            break;
    }
    // ����ϴ� �ڿ����� release...
    std::cout << "������ �۾��ϰ�.. finish foo\n";
}
int main()
{
    bool flag = false;
    std::thread t(&foo, std::ref(flag) );

    std::this_thread::sleep_for(2s);

    // ���ο� ������ �����ϴ� �۾��� ���
    flag = true;

    t.join();
}

// �� �ڵ尡 "coperative cancelation" �̶�� 
// �Ҹ��� ��� �Դϴ�.
// C# �� thread Ŭ������ ����ϴ� ��� �Դϴ�.
