#include <thread>
#include <atomic>
#include <cassert>

std::atomic<int> data1 = 0;
std::atomic<int> data2 = 0;

int main()
{
    // memory_order_seq_cst : 반드시 순차적으로 실행되어야 한다.
    // => 가장 요구조건이 많습니다. 
    // => 가장 오버헤드가 큰 방식 입니다.
    data1.store(100, std::memory_order_seq_cst);
    data2.store(200, std::memory_order_seq_cst);
    data2.store(300); // 2번째 인자생략시 디폴트 값 입니다.

    ++data2; // 이 렇게 하면  memory_order_seq_cst

    data2.fetch_add(1, std::memory_order_relaxed); 
            // 위 코드 보다 조금 더 효율적인 기계어 코드
}