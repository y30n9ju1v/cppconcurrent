#include <iostream>
#include <thread>
#include <mutex>
#include <windows.h>
#include "chronometry.h"

constexpr unsigned int cnt = 1000000;


long x = 0; // ��� �����尡 ����.

void foo()
{
    for (int i = 0; i < 1000000; ++i)
    {
        // x = x + 1;  
        // �� ������ �Ʒ� ��� �����մϴ�.
        // VC ����ڴ� "32bit"�� ������ ������ �����մϴ�.
        /*
        __asm
        {
            mov eax, x
            add eax, 1
            mov x, eax
        }
        */
        // �ذ�å 1. mutex ������ ����ȭ
        //  => ���� 1�����ε�.. mutex ����ϴ� ���� �ʹ� ������尡 ũ��

        // �ذ�å 2. context switch �� �߻����� ���� ���� ���
        // => CPU�� �Ѱ��� ��Ȳ���� ������ ��Ƽ �����带 ����� ���
        //    �Ʒ� �ڵ�� �����ϰ� 1���� �մϴ�.
        // => ��, CPU �� ������ �̸� ������ 1���� �ƴմϴ�.
        /*
        __asm
        {
            inc x
        }
        */

        // �ذ�å 3. ��Ƽ �ھ �����ϴ� CPU ���� "lock" �̶�� �ǹ���
        // opcode �� �ֽ��ϴ�.
        // => Ư�� �ھ �޸� ����, �ش� �޸𸮴� �ٸ� CPU 
        //    ���پȵ�
        /*
        __asm
        {
            lock inc x
        }
        */
        // mutex, semaphore ���� : OS �� �����ϴ� ���
        // �� �ڵ�� : CPU �� �����ϴ� ���!!

        // lock-free : OS�� �����ϴ� ����� �ƴ϶�
        //             CPU �� �����ϴ� ������θ� ����ȭ �ϴ� ���
        InterlockedIncrement(&x); // win32 API 
                                  // �� �ڵ� ó�� �����ϴ� �Լ�
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
