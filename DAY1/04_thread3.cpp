#include <iostream>
#include <thread>

// 스레드 함수의 모양
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
    // C++은 모든 callable object 를 스레드로 수행가능합니다
    // 1. 일반 함수
    std::thread t1(&foo, 1, 3.4); // ok
//  std::thread t1(foo, 1, 3.4); // ok

    // 2. 멤버 함수
    Machine m;
    std::thread t2(&Machine::Run, &m, 1, 3.4); // ok
//  std::thread t2(Machine::Run, &m, 1, 3.4); // error
                    //  m.Run(1, 3.4) 를 스레드로 수행
    // 2. 멤버함수에서 1번 처럼 m.Run으로 하면 안되나요 ?
    // => 안됩니다.

    // 3. 함수 객체
    Work w;
    w(1, 3.4); // w 는 객체지만 함수 처럼 사용가능.

    std::thread t3(w, 1, 3.4); // w(1, 3.4) 를 스레드로 수행
//  std::thread t3(&w, 1, 3.4);// error

    // 4. 람다 표현식도 가능
    std::thread t4([]() {std::cout << "lambda\n"; });
//  std::thread t5([](int a) {std::cout << "lambda\n"; }, 0);
    //                  함수,                             인자
}

