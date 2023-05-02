#include <iostream>
#include <thread>
#include <windows.h>
#include <chrono>
using namespace std::literals;

// 스레드 우선 순위
// => windows, linux 등의 OS는 지원하지만
// => 지원하지 않은 운영체제도 많이 있습니다.
// => 그래서, C++ 표준 thread 클래스에는 우선순위 개념이 없습니다.
void foo()
{
    auto tid = std::this_thread::get_id(); // 스레드 ID 얻기
}

int main()
{
    std::thread t(&foo);

    // 핵심 1. native handle 얻기
    std::thread::native_handle_type handle = t.native_handle();
    // Windows : HANDLE   타입
    // linux   : pthead_t 타입

    // 이제 native 핸들이 있으므로 각 OS별 시스템 콜 사용가능
    SetThreadPriority((HANDLE)handle, THREAD_PRIORITY_HIGHEST);

    // 단, 위코드는 OS 별 호환되지 않으므로 되도록 사용하지 마세요.

    t.join();
}

