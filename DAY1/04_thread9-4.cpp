#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include "chronometry.h" // 성능측정을 위해서..


constexpr std::size_t sz = 1000000;
//constexpr std::size_t sz = 110;

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
//---------------------------------------------------------
template<typename IT, typename RT>
RT parallel_sum(IT first, IT last, RT init)
{
    auto cnt_element = std::distance(first, last);

    if (cnt_element == 0) return 0;

    std::size_t cnt_hw_thread = std::thread::hardware_concurrency();

    if (cnt_hw_thread == 0)
        cnt_hw_thread = 2;

    const std::size_t cnt_per_thread = 25;

    const std::size_t max_cnt_thread =
        (cnt_element + cnt_per_thread - 1) / cnt_per_thread;

    const std::size_t cnt_thread =
        std::min(cnt_hw_thread, max_cnt_thread);

    const std::size_t block_size = cnt_element / cnt_thread;
    std::vector<std::thread> thread_vec(cnt_thread - 1);
    std::vector<RT> result_vec(cnt_thread);

    IT start = first;

    for (int i = 0; i < cnt_thread - 1; ++i)
    {
        IT end = std::next(start, block_size);

        thread_vec[i] = std::thread(sum<std::vector<int>::iterator, int>,
            start, end, std::ref(result_vec[i]));

        start = end;
    }
    sum(start, last, result_vec[cnt_thread - 1]);

    for (auto& t : thread_vec)
        t.join();

    RT ret = std::accumulate(result_vec.begin(),
        result_vec.end(), 0);

    return ret;
}



int f1()
{
    // 싱글 스레드로 합을 구하기
    int s = 0;
    sum(v.begin(), v.end(), s);
    return s;
}
int f2()
{
    // 멀티 스레드로 합을 구하기
    int s = 0;
    s = parallel_sum(v.begin(), v.end(), 0);
    return s;
}
int main()
{
    init();

    chronometry(f1); // f1의 수행시간을 출력
    chronometry(f2); // f2의 수행시간을 출력
}
