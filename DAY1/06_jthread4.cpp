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

        // 주기적으로 약속된 "cancel flag" 를 확인 합니다.
        if (flag == true)
            break;
    }
    // 사용하던 자원들을 release...
    std::cout << "마무리 작업하고.. finish foo\n";
}
int main()
{
    bool flag = false;
    std::thread t(&foo, std::ref(flag) );

    std::this_thread::sleep_for(2s);

    // 새로운 스레가 수행하는 작업을 취소
    flag = true;

    t.join();
}

// 위 코드가 "coperative cancelation" 이라고 
// 불리는 기술 입니다.
// C# 의 thread 클래스가 사용하는 기술 입니다.
