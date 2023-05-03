
// 00_promise4-2.cpp
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>
// ����

void work3(std::promise<int>&& pm, std::vector<int>& v)
{
    int s = std::accumulate(v.begin(), v.end(), 0);

    pm.set_value(s);
}


int main()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v2(10);

    std::partial_sum(v1.begin(), v1.end(), v2.begin());

    //------------------------
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    // ������� �۾��� �����Ҷ�
    // 1. ������ �Լ��� �и��ؼ� ���� - promise4-1�� ����
    // => main ���� ���� ������ ���ڷ� �����ؼ� ���
    // std::thread t(work3, std::move(pm), std::ref(v2));

    // 2. ���� ǥ�������� ����
    std::thread t([&pm, &v2]() 
        {
            int s = std::accumulate(v2.begin(), v2.end(), 0);
            pm.set_value(s);
        } );




    for (auto n : v2)
        std::cout << n << ", ";

    int s = ft.get();

    
    std::cout << "\n" << s << std::endl;
}

