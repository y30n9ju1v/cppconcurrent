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

	Sleep(1000); // 1초 대기

	DWORD n = 0;
	
	GetExitCodeThread(handle, &n);

	std::cout << n << std::endl;

}
