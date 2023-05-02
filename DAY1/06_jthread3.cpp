#include <iostream>
#include <thread>

void foo(int a, int b)
{
    std::cout << "foo : " << a << ", " << b << std::endl;
}

int main()
{
    // C++11 의 std::thread 는 반드시 사용자가 join()해야 합니다
    /*
    std::thread t1(&foo, 10, 20);
    std::thread t2(&foo, 10, 20);
    t1.join();
    t2.join();
    */

    // C++20 의 jthread는 소멸자에서 자동으로 join 호출합니다.
    // => 원리는 jthread2.cpp 의 join_thread 코드 참고
    // => g++ 소스.cpp -std=c++20
    std::jthread t1(&foo, 10, 20);
    std::jthread t2(&foo, 10, 20);

}

