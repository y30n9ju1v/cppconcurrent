
// 00_promise4-2.cpp
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>
// 예제

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

    // 스레드로 작업을 수행할때
    // 1. 별도의 함수로 분리해서 실행 - promise4-1번 예제
    // => main 에서 만든 변수를 인자로 전달해서 사용
    // std::thread t(work3, std::move(pm), std::ref(v2));

    // 2. 람다 표현식으로 실행
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

