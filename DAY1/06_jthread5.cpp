#include <chrono>
#include <iostream>
#include <thread>
using namespace std::literals;

// C++20 의 jthread 는 "협력적 취소" 모델을 지원 합니다.

void foo(std::stop_token token)
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "foo : " << i << std::endl;

        // 주기적으로 약속된 "cancel flag" 를 확인 합니다.
        if ( token.stop_requested() )
            break;
    }
    // 사용하던 자원들을 release...
    std::cout << "마무리 작업하고.. finish foo\n";
}
void goo() {}

int main()
{
    // 핵심 1. jthread 인자로 어떠한 것도 보내고 있지 않습니다
    std::jthread j1(&goo);
    std::jthread j2(&foo);  // 인자를 전달하지 않습니다
                       // 하지만 stop_token은 전달되고 있습니다
    std::this_thread::sleep_for(2s);

    j2.request_stop(); // 멈춰 달라
    j1.request_stop(); // 요청할수 있지만
                        // 탈출 구문이 없으므로 무시 됩니다.

}

