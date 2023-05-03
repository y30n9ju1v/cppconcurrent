#include <iostream>
#include <thread>
#include <string_view>
// 3의 배수를 순차적으로 반환 하는 함수
// => 아래 코드는 싱글스레드에서는 안전합니다.
// => 멀티 스레드 라면?
int next3times()
{
//	int n = 0;		// stack, 스레드당 한개 씩 생성됨
//	static int n = 0; // static 모든 스레드가 공유.. 

	thread_local static int n = 0; 
					// 스레드당 한개의 static 메모리 공간에 할당
					// TSS(thread specifit storage)또는
					// TLS(thread local storage) 라고 합니다
	n = n + 3;
	return n;
}

void foo(const std::string& name)
{
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
}
int main()
{
//	foo("A");

	std::thread t1(&foo, "A");
	std::thread t2(&foo, "\tB");

	t1.join();
	t2.join();
}

// 핵심 : 프로세스가 소유하는 것과 스레드가 소유하는것을 구분해야 합니다.

// 프로세스 소유 : static(data) 메모리, 힙, 파일(소켓) 핸들.. 
//				A 스레드가 파일 오픈후 스레드가 종료 되어도
//				파일은 자동으로 close 되지 않습니다.
// 
// 스레드 소유  : 스택, GUI핸들(윈도우 등을 만들때)
//				A 스레드가 만든 윈도우는 A스레드 종료시 GUI 파괴
//				OS 마다 다를수 있음.



int g1 = 0; // 전역변수 모든 스레드가 공유 합니다.
thread_local int g2 = 0; // 스레드당 각각의 전역변수
						// TSS 공간에 할당됩니다.

// 일반적으로 OS에는 TSS 공간의 크기가 제한 되어 있습니다.
// => 커다란 데이타를 사용하려면 스레드별로 힙에 할당하고
//    TSS에는 주소를 보관하세요

// WIndows OS : TSS 크기는 sizeof(int)*1088 입니다.
