#include <iostream>
#include <atomic>

// atomic<T>
// => T는 크기가 작은 타입(64 bit 이하 권장)만 사용하세요
// => 복사 생성자, 대입 연산자를 사용자가 만든 타입을 넣을수없습닏.

// trivial : 사용자가 만들지 않고 컴파일러가 제공하는 것들
//           단, 가상함수도 없어야 한다.

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

