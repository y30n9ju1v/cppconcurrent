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

    // 작업 1. v1의 부분합을 구해서 v2에 넣기
    std::partial_sum(v1.begin(), v1.end(), v2.begin());

    //------------------------
    // 작업2와 작업3은 독립된 작업 입니다.
    // 스레드를 생성해서 작업 3을 수행하도록 하고..
    // 주스레드는 작업2를 수행합니다.
    // 단, 작업3의 결과를 얻어야지 작업 4를 할수 있습니다
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    std::thread t(work3, std::move(pm), std::ref(v2));

    // 작업 2. v2 의 모든 요소를 화면 출력
    for (auto n : v2)
        std::cout << n << ", ";

    // 작업 3. v2의 모든 요소의 합을 구하기
    // int s = std::accumulate(v2.begin(), v2.end(), 0);

    // work3 스레드가 수행중인 연산의 결과를 대기 합니다
    int s = ft.get();

    // 작업 4. 결과 출력
    std::cout << "\n" << s << std::endl;
}

