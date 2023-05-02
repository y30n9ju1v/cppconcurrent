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
//---------------------------------------------------------
template<typename IT, typename RT>
RT parallel_sum(IT first, IT last, RT init)
{
    // 1. ��� ���� ���ϱ�
//  auto cnt_element = last - first; // �������� �ݺ��ڸ�����
    auto cnt_element = std::distance(first, last);

    if (cnt_element == 0) return 0;

    // 2. ���� PC���� ���� ���డ���� ������ ���� ���ϱ�
    // => �Ϲ������� CPU���� * 2
    auto cnt_hw_thread = std::thread::hardware_concurrency;

    if (cnt_hw_thread == 0) // ������ ���Ҽ� ���ٸ�
        cnt_hw_thread = 2;
}





int main()
{
    init();

    int s = parallel_sum(v.begin(), v.end(), 0);

    std::cout << s << std::endl;
}
