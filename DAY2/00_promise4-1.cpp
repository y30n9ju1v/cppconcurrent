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

    // �۾� 1. v1�� �κ����� ���ؼ� v2�� �ֱ�
    std::partial_sum(v1.begin(), v1.end(), v2.begin());

    //------------------------
    // �۾�2�� �۾�3�� ������ �۾� �Դϴ�.
    // �����带 �����ؼ� �۾� 3�� �����ϵ��� �ϰ�..
    // �ֽ������ �۾�2�� �����մϴ�.
    // ��, �۾�3�� ����� ������ �۾� 4�� �Ҽ� �ֽ��ϴ�
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    std::thread t(work3, std::move(pm), std::ref(v2));

    // �۾� 2. v2 �� ��� ��Ҹ� ȭ�� ���
    for (auto n : v2)
        std::cout << n << ", ";

    // �۾� 3. v2�� ��� ����� ���� ���ϱ�
    // int s = std::accumulate(v2.begin(), v2.end(), 0);

    // work3 �����尡 �������� ������ ����� ��� �մϴ�
    int s = ft.get();

    // �۾� 4. ��� ���
    std::cout << "\n" << s << std::endl;
}

