#include <thread>
#include <atomic>

std::atomic<int> x = 0;
std::atomic<int> y = 0;

// std::memory_order_relaxed
// => 접근 만 동기화되면 된다는 의미 입니다.
// => reordering 이 발생할수 있습니다.

// => 결국, 접근만 동기화 하면 된다는 "최소"의 요구 조건..
// => 다른 것은 보장할 필요가 없으므로 다른 옵션보다 빠르게 동작!!

// => reodering 은 CPU 에 따라 다름.. 보장 안됨.

void foo()
{
    int n1 = y.load(std::memory_order_relaxed);
    x.store(n1, std::memory_order_relaxed);
}

void goo()
{
    int n2 = x.load(std::memory_order_relaxed);
    y.store(100, std::memory_order_relaxed);
}

int main()
{
    std::thread t1(foo);
    std::thread t2(goo);
    t1.join(); t2.join();
}