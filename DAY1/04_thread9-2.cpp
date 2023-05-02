#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

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
    // 1. ��� ���� ���ϱ�
//  auto cnt_element = last - first; // �������� �ݺ��ڸ�����
    auto cnt_element = std::distance(first, last);

    if (cnt_element == 0) return 0;

    // 2. ���� PC���� ���� ���డ���� ������ ���� ���ϱ�
    // => �Ϲ������� CPU���� * 2
    std::size_t cnt_hw_thread = std::thread::hardware_concurrency();

    if (cnt_hw_thread == 0) // ������ ���Ҽ� ���ٸ�
        cnt_hw_thread = 2;

    std::cout << cnt_hw_thread << std::endl;

    // 3. ����Ÿ �翡 ���� �������� ����
    // => �Ѱ��� ������� "�ּ� 25��"�� ����Ÿ�� ó���ؾ� �Ѵٰ� ����

    const std::size_t cnt_per_thread = 25;

    const std::size_t max_cnt_thread =
        (cnt_element + cnt_per_thread - 1) / cnt_per_thread;

    // �������� �������� ����
    const std::size_t cnt_thread =
                std::min(cnt_hw_thread, max_cnt_thread);

    std::cout << cnt_thread << std::endl;

    return 0; 
}





int main()
{
    init();

    int s = parallel_sum(v.begin(), v.end(), 0);

    std::cout << s << std::endl;
}
