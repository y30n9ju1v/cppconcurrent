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

    // 핵심 : 인자 전달 방법
    std::thread t1(&f1); // 인자가 없는 함수를 스레드로!

    std::thread t2(&f2, 3, 3.4); 

    // 주의 : 인자를 참조로 전달하려면 std::ref() 사용
    //       단, 위험하니 주의해서 사용해야 합니다
    std::thread t3(&f3, 3, std::ref(n), std::move(s));

    t1.join();
    t2.join();
    t3.join();
}

