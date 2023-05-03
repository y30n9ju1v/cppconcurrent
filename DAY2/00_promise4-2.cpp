
// 00_promise4-2.cpp
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>
// ¿¹Á¦

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

    std::thread t(work3, std::move(pm), std::ref(v2));




    for (auto n : v2)
        std::cout << n << ", ";

    int s = ft.get();

    
    std::cout << "\n" << s << std::endl;
}

