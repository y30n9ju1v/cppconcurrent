// 04_thread0.cpp - git 에서 복사해 오세요.
#include <Windows.h>
#include <iostream>

DWORD __stdcall foo(void* p)
{
	std::cout << "foo" << std::endl;
	return 100;
}

int main()
{
	HANDLE handle = CreateThread(0, 0, foo, 0, 0, 0);
					// 리눅스 : pthread_create()

	Sleep(1000); // 1초 대기

	// 스레드 자체는 종료 되었지만 스레드를 관리하는 OS가 유지하는
	// 객체는 메모리에 남아 있습니다.
	// 따라서, 종료 코드를구할수 있습니다.
	DWORD n = 0;
	GetExitCodeThread(handle, &n);

	std::cout << n << std::endl;

}