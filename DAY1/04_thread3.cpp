#include <iostream>
#include <thread>

// ������ �Լ��� ���
void foo(int a, double d) {}

struct Machine
{
    void Run(int a, double d) {}
};
struct Work
{
    void operator()(int a, double b) const {}
};

int main()
{
    // C++�� ��� callable object �� ������� ���డ���մϴ�
    // 1. �Ϲ� �Լ�
    std::thread t1(&foo, 1, 3.4); // ok
//  std::thread t1(foo, 1, 3.4); // ok

    // 2. ��� �Լ�
    Machine m;
    std::thread t2(&Machine::Run, &m, 1, 3.4); // ok
//  std::thread t2(Machine::Run, &m, 1, 3.4); // error
                    //  m.Run(1, 3.4) �� ������� ����
    // 2. ����Լ����� 1�� ó�� m.Run���� �ϸ� �ȵǳ��� ?
    // => �ȵ˴ϴ�.

    // 3. �Լ� ��ü
    Work w;
    w(1, 3.4); // w �� ��ü���� �Լ� ó�� ��밡��.

    std::thread t3(w, 1, 3.4); // w(1, 3.4) �� ������� ����
//  std::thread t3(&w, 1, 3.4);// error

    // 4. ���� ǥ���ĵ� ����
    std::thread t4([]() {std::cout << "lambda\n"; });
//  std::thread t5([](int a) {std::cout << "lambda\n"; }, 0);
    //                  �Լ�,                             ����
}

