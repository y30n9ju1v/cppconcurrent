#include <chrono>
#include <iostream>
#include <future>
#include <random>
#include <vector>
#include <string>
#include <numeric>
#include <execution>
#include "chronometry.h"

//static const int NUM = 100000000; // 1억
static const int NUM = 10000000; // 

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
        [v1_first, v2_first, v1_last] 
        { return std::inner_product(v1_first, v1_last, v2_first, 0LL); }
    );
    // 위 스레드 생성시, 반복자를 값 캡쳐(복사본) 했으므로
    // main의 원래 반복자는 변경해도 안전합니다.
    std::advance(v1_first, block_size);
    std::advance(v2_first, block_size);
    std::advance(v1_last,  block_size);

    std::future<long long> ft2 = std::async(
        [v1_first, v2_first, v1_last]
        { return std::inner_product(v1_first, v1_last, v2_first, 0LL); }
        );

    std::advance(v1_first, block_size);
    std::advance(v2_first, block_size);
    std::advance(v1_last, block_size);

    std::future<long long> ft3 = std::async(
        [v1_first, v2_first, v1_last]
        { return std::inner_product(v1_first, v1_last, v2_first, 0LL); }
        );
    
    std::advance(v1_first, block_size);
    std::advance(v2_first, block_size);
    v1_last = v1.end();

    std::future<long long> ft4 = std::async(
        [v1_first, v2_first, v1_last]
        { return std::inner_product(v1_first, v1_last, v2_first, 0LL); }
        );

    // 이제 각각의 결과를 대기했다가 더하면 됩니다.
    return ft1.get() + ft2.get() + ft3.get() + ft4.get();
}

int main()
{
    fill_vector();
    
    // 성능비교
    chronometry(f1);
    chronometry(f2);
    chronometry(f1);
    chronometry(f2);
}