#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

constexpr std::size_t sz = 1000000;

std::vector<int> v;

void init()
{
    for (int i = 0; i < sz; ++i)
    {
        v.push_back(i);
    }
}
//---------------------------------------------

template<typename IT, typename RT>
void sum(IT first, IT last, RT& result)
{
    result = std::accumulate(first, last, result);
}

// 주어진 구간의 합을 병렬로 구하는 함수!!
// => STL 의 병렬 함수들의 원리와 유사합니다.
template<typename IT, typename RT>
RT parallel_sum(IT first, IT last, RT init)
{
    // 주어진 구간의 합을 멀티 스레드로 구해서 반환
}
int main()
{
    init();

    int s = parallel_sum(v.begin(), v.end(), 0);

    std::cout << s << std::endl;
}
