#include <iostream>
#include <string>
#include <thread>

void f1() { }
void f2(int a, double d) { }
void f3(int a, int& b, std::string&& s) { b = 100; }

int main()
{
    int n = 0;
    std::string s = "hello";

    // �ٽ� : ���� ���� ���
    std::thread t1(&f1); // ���ڰ� ���� �Լ��� �������!

    std::thread t2(&f2, 3, 3.4); 

    // ���� : ���ڸ� ������ �����Ϸ��� std::ref() ���
    //       ��, �����ϴ� �����ؼ� ����ؾ� �մϴ�
    std::thread t3(&f3, 3, std::ref(n), std::move(s));

    t1.join();
    t2.join();
    t3.join();
}

