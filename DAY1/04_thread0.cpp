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

	// 현재 새롭게 생성한 스레드는 종료되었지만
	// OS가 관리하는 객체는 메모리에 아직 존재합니다.
	// => 이런 스레드는 "좀비(zombie)"라고 합니다.

	// 더이상 새로운 스레드에 접근할일이 없으면
	// 즉시 핸들을 닫으세요...
	CloseHandle(handle); // t.detach()가 이 일을 합니다.
	// => 스레드 관리 객체의 참조계수가 1감소.
	// => 이미 새로운 스레드가 이미 종료 되었다면, 이순간 객체 파괴

}