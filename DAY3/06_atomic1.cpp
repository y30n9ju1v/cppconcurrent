#include <iostream>
#include <thread>
#include <mutex>
#include <windows.h>
#include "chronometry.h"

constexpr unsigned int cnt = 1000000;


long x = 0; // 모든 스레드가 공유.

void foo()
{
    for (int i = 0; i < 1000000; ++i)
    {
        // x = x + 1;  
        // 위 한줄은 아래 기계어를 생성합니다.
        // VC 사용자는 "32bit"로 놓으면 컴파일 가능합니다.
        /*
        __asm
        {
            mov eax, x
            add eax, 1
            mov x, eax
        }
        */
        // 해결책 1. mutex 등으로 동기화
        //  => 단지 1증가인데.. mutex 사용하는 것은 너무 오버헤드가 크다

        // 해결책 2. context switch 이 발생하지 않은 기계어 사용
        // => CPU가 한개인 상황에서 여러개 멀티 스레드를 만드는 경우
        //    아래 코드는 안전하게 1증가 합니다.
        // => 단, CPU 가 여러개 이면 안전한 1증가 아닙니다.
        /*
        __asm
        {
            inc x
        }
        */

        // 해결책 3. 멀티 코어를 지원하는 CPU 에는 "lock" 이라는 의미의
        // opcode 가 있습니다.
        // => 특정 코어가 메모리 사용시, 해당 메모리는 다른 CPU 
        //    접근안됨
        /*
        __asm
        {
            lock inc x
        }
        */
        // mutex, semaphore 등은 : OS 가 제공하는 기능
        // 위 코드는 : CPU 가 제공하는 명령!!

        // lock-free : OS가 제공하는 기능이 아니라
        //             CPU 가 제공하는 명령으로만 동기화 하는 기술
        InterlockedIncrement(&x); // win32 API 
                                  // 위 코드 처럼 동작하는 함수
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    std::thread t3(foo);
    t1.join();
    t2.join();
    t3.join();
    std::cout << x << std::endl;
}
