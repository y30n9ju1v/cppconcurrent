#include <iostream>
#include <thread>
#include <atomic>

struct Point   { int x, y; };    // 64bit ����ü
struct Point3D { int x, y, z; }; // 96bit ����ü

std::atomic<int>     a1;
std::atomic<Point>   a2;
std::atomic<Point3D> a3;

int main()
{
    // �Ʒ� 2���� OS �� ����ȭ�� ������� �ʰ� CPU ��ɸ�����
    // ����ȭ �մϴ�.
    ++a1;
    int n = a1.load(); 
    Point pt = a2.load();
    Point3D p3d = a3.load(); // CPU ��ɸ����� ����ȭ �ȵ˴ϴ�.
                            // �ٸ� ��� ���
                            // ��κ� spinlock
                            // (�÷��׺��� ����� ����)

    std::cout << a1.is_lock_free() << std::endl;
    std::cout << a2.is_lock_free() << std::endl;
    std::cout << a3.is_lock_free() << std::endl;
}

