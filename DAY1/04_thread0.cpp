// 04_thread0.cpp - git ���� ������ ������.
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
					// ������ : pthread_create()

	Sleep(1000); // 1�� ���

	// ������ ��ü�� ���� �Ǿ����� �����带 �����ϴ� OS�� �����ϴ�
	// ��ü�� �޸𸮿� ���� �ֽ��ϴ�.
	// ����, ���� �ڵ带���Ҽ� �ֽ��ϴ�.
	DWORD n = 0;
	GetExitCodeThread(handle, &n);

	std::cout << n << std::endl;

}