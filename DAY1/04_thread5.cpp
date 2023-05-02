#include <iostream>
#include <thread>
#include <windows.h>
#include <chrono>
using namespace std::literals;

// ������ �켱 ����
// => windows, linux ���� OS�� ����������
// => �������� ���� �ü���� ���� �ֽ��ϴ�.
// => �׷���, C++ ǥ�� thread Ŭ�������� �켱���� ������ �����ϴ�.
void foo()
{
    auto tid = std::this_thread::get_id(); // ������ ID ���
}

int main()
{
    std::thread t(&foo);

    // �ٽ� 1. native handle ���
    std::thread::native_handle_type handle = t.native_handle();
    // Windows : HANDLE   Ÿ��
    // linux   : pthead_t Ÿ��

    // ���� native �ڵ��� �����Ƿ� �� OS�� �ý��� �� ��밡��
    SetThreadPriority((HANDLE)handle, THREAD_PRIORITY_HIGHEST);

    // ��, ���ڵ�� OS �� ȣȯ���� �����Ƿ� �ǵ��� ������� ������.

    t.join();
}

