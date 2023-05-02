#include <thread>

// copy, move

void foo() {}
void goo() {}

int main()
{
    std::thread t1(&foo);
    std::thread t2(&goo);

    // 1. swap
//  t1.swap(t2); // ok

    // 2. copy �� �ȵǰ�, move �� �����մϴ�.
//  std::thread t3 = t1;            // error. copy �� �ȵ�
    std::thread t4 = std::move(t1); // ok

    t2.join();
    t4.join();

    // 3. ������ ��ü�� ���� �����, ����(������ ����)�� ���߿�
    std::thread t5; // ��ü�� �������
                    // ���� ������ ���� �ȵ�.

    t5 = std::thread(&foo); // ok
         // ^ �ӽð�ü�̹Ƿ� rvalue �Դϴ�
         //   move �� ����

//    std::vector< std::thread> v(10);

    // ��ü�� �ƴ� ������ ��ü�� �̸� ����� ������ ?
    // => ���� thread pool �Ҷ� �մϴ�.
}



void f1(std::thread t) 
{
    t.join(); 
}

std::thread f2()
{
    return std::thread(foo());
}
