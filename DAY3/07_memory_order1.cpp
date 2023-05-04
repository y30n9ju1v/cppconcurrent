// g++ reorder1.cpp –S –masm=intel -O2
// cl reorder1.cpp /FAs /c /O2

// 아래 코드를 잘 보세요 goo 의 주석을 생각해 보세요!
#include <atomic>
int a = 0;
int b = 0;

// thread A
void foo()
{
    a = b + 1;

    // 펜스 설치 : 펜스 위의 코드는 펜스 아래로 내려갈수 없습니다
    // => reordering 금지..
    // => 컴파일러 최적화라도 순서 바꾸지 말라는 의미
    //    std::atomic_thread_fence(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_seq_cst);
    b = 1;
}








// thread B
void goo()
{
    if (b == 1)
    {
        // a == 1 을 보장할수 있을까 ?
    }
}

// godbolt.org 접속해 보세요.. 위 소스 왼쪽에 넣어 보세요





