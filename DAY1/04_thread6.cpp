#include <iostream>
#include <thread>

void foo() {}

int main()
{
    std::thread t1(&foo);

    t1.join();  // ok.. 
//  t1.join();  // runtime error. �̹� join �Ѱ��� �ٽ� �Ҽ������ϴ�

    std::thread t2; // ������ ��ü�� ��������ϴ�.
                    // �Լ��� �������� ������
                    // ����, �����尡 �����Ȱ��� �ƴմϴ�
    t2.join(); // runtime error. ���� ������ �����ȵ�

    if (t2.joinable()) // join �����Ѱ��� ����
    {
        t2.join();
    }

    // joinable : join �� �����Ѱ��� �����ϴ� ��
    // => �����尡 ����ִ��� �����ϴ� ���� �ƴմϴ�.
    std::thread t3(&f1);
    std::thread t4(&f2);

    // �����尡 �������̰� ���� �Ǿ��� t3, t4 �� ��� join����
    bool b1 = t3.joinable(); // f1�� �������̰�
    bool b2 = t4.joinable(); // f2�� ����Ǿ���
                             // ��� true

    // �����带 ������ �ʰų�
    // �̹� join(�Ǵ� detach) �� ��츸 false �Դϴ�.
    std::thread t5;
    std::thread t6(&f2);
    t6.join(); // t6.detach();

    bool b1 = t5.joinable();  // ������ ���� �ȵ�
    bool b2 = t6.joinable();  // �̹� join ����
}
