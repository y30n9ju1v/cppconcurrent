#include <chrono>
#include <iostream>
#include <future>
#include <random>
#include <vector>
#include <string>
#include <numeric>
#include <execution>
#include "chronometry.h"

static const int NUM = 100000000; // 1억

std::vector<int> v1, v2;

void fill_vector()
{
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> dist(0, 100);

    v1.reserve(NUM);
    v2.reserve(NUM);

    for (int i = 0; i < NUM; ++i)
    {
        v1.push_back(dist(engine));
        v2.push_back(dist(engine));
    }
}

// vector 내적 구하기
// 1. 한개의 스레드 사용
long long f1()
{
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0LL);
}

// 2. 4개의 스레드 사용.
long long f2()
{
    // NUM : vector의 요소 갯수
    long long block_size = NUM / 4;

    auto v1_first = v1.begin();
    auto v2_first = v2.begin();
    auto v1_last = std::next(v1.begin(), block_size);

    // std::thread : 결과를 얻기 위해 다양한 기법을 사용해야 합니다.
    // std::async  : 기존 함수의 반환값을 그대로 사용 가능.
    
    std::future<long long> ft1 = std::async(
        []() { return std::inner_product(v1_first, v1_last,
            v2_first, 0LL); }
    );

}







int main()
{
    fill_vector();
    
    f1();
}