#include <iostream>
#include <thread>
#include <vector>
#include <unordered_set>


// std::this_thread �ȿ� 4���� ���� �Լ��� �ֽ��ϴ�.

int main()
{
    // 1. std::this_thread::get_id() : ���� ������ ID���
    std::cout << std::this_thread::get_id() << std::endl;

    // 2. ������ ID Ÿ�� �˾� �μ���.
    std::thread::id tid1 = std::this_thread::get_id();

    // Ư¡ 1. ���� ��ȯ �ȵ˴ϴ�.
    // int n = tid1; // error. 

    // Ư¡ 2. �����̳� ���� �����ϰ�, hash �� ����
    std::vector<std::thread::id> v; // ok
    std::hash<std::thread::id> h;

    // Ư¡ 3. ==, != ���� �����մϴ�.
    auto tid2 = std::this_thread::get_id();

    bool b1 = tid1 == tid2;
}