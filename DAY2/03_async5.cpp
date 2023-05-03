#include <chrono>
#include <iostream>
#include <future>
#include <random>
#include <vector>
#include <string>
#include <numeric>
#include <execution>
#include "chronometry.h"

//static const int NUM = 100000000; // 1��
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

// vector ���� ���ϱ�
// 1. �Ѱ��� ������ ���
long long f1()
{
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0LL);
}

// 2. 4���� ������ ���.
long long f2()
{
    // NUM : vector�� ��� ����
    long long block_size = NUM / 4;

    auto v1_first = v1.begin();
    auto v2_first = v2.begin();
    auto v1_last = std::next(v1.begin(), block_size);

    // std::thread : ����� ��� ���� �پ��� ����� ����ؾ� �մϴ�.
    // std::async  : ���� �Լ��� ��ȯ���� �״�� ��� ����.
    
    std::future<long long> ft1 = std::async(
        [v1_first, v2_first, v1_last] 
        { return std::inner_product(v1_first, v1_last, v2_first, 0LL); }
    );
    // �� ������ ������, �ݺ��ڸ� �� ĸ��(���纻) �����Ƿ�
    // main�� ���� �ݺ��ڴ� �����ص� �����մϴ�.
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

    // ���� ������ ����� ����ߴٰ� ���ϸ� �˴ϴ�.
    return ft1.get() + ft2.get() + ft3.get() + ft4.get();
}

int main()
{
    fill_vector();
    
    // ���ɺ�
    chronometry(f1);
    chronometry(f2);
    chronometry(f1);
    chronometry(f2);
}