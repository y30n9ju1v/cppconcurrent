#include <iostream>
#include <atomic>

// atomic<T>
// => T�� ũ�Ⱑ ���� Ÿ��(64 bit ���� ����)�� ����ϼ���
// => ���� ������, ���� �����ڸ� ����ڰ� ���� Ÿ���� ������������.

// trivial : ����ڰ� ������ �ʰ� �����Ϸ��� �����ϴ� �͵�
//           ��, �����Լ��� ����� �Ѵ�.

struct Point
{
    int x, y;

    Point() = default;

    Point(const Point& other) : x(other.x), y(other.y) {}
    //Point(const Point&) = default;
};

std::atomic<Point> pt;

int main()
{
    Point ret = pt.load();
}

