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


// 구간의 합을 구하는 함수.
template<typename IT, typename RT> 
void sum(IT first, IT last, RT& result)
{
    result = std::accumulate(first, last, result);
}
int main()
{
    init();

    int s = 0;
//  sum(v.begin(), v.end(), s); // 주스레드가 직접 호출

//  std::thread t(sum, v.begin(), v.end(), std::ref(s));
                // 왜 에러일까요 ?
                // sum 이 템플릿인데. 
                // => 직접 호출하면 인자 타입 추론가능
                // => 하지만 이름만 전달하므로 타입 추론안됨

    // 아래 처럼 타입 전달해야 합니다.
    std::thread t(sum<std::vector<int>::iterator, int>, 
                v.begin(), v.end(), std::ref(s));
    t.join();

    std::cout << s << std::endl;
}
