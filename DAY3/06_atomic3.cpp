#include <iostream>
#include <thread>
#include <atomic>

struct Point   { int x, y; };    // 64bit 구조체
struct Point3D { int x, y, z; }; // 96bit 구조체

std::atomic<int>     a1;
std::atomic<Point>   a2;
std::atomic<Point3D> a3;

int main()
{
    // 아래 2줄은 OS 의 동기화를 사용하지 않고 CPU 명령만으로
    // 동기화 합니다.
    ++a1;
    int n = a1.load(); 
    Point pt = a2.load();
    Point3D p3d = a3.load(); // CPU 명령만으로 동기화 안됩니다.
                            // 다른 방법 사용
                            // 대부분 spinlock
                            // (플래그변수 만들고 복사)

    std::cout << a1.is_lock_free() << std::endl;
    std::cout << a2.is_lock_free() << std::endl;
    std::cout << a3.is_lock_free() << std::endl;
}

