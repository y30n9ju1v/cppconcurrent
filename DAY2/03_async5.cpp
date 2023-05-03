#include <chrono>
#include <iostream>
#include <future>
#include <random>
#include <vector>
#include <string>
#include <numeric>
#include <execution>
#include "chronometry.h"

static const int NUM = 100000000; // 1��

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
        []() { return std::inner_product(v1_first, v1_last,
            v2_first, 0LL); }
    );

}







int main()
{
    fill_vector();
    
    f1();
}