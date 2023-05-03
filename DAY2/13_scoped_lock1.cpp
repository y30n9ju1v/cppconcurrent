#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

struct  Account
{
    std::mutex m; // money�� ���� ����ȭ�� ���� ���ؽ�
    int money = 100;
};


void transfer(Account& acc1, Account& acc2, int cnt)
{
    // 2�� ���¸� ��� �����ؾ� �ϹǷ� ��� ���ؽ� ȹ��
    // �Ʒ�ó�� �����, �־��� ��� 2���� �����尡 ���� mutex �ϳ��� ȹ���ϰ�
    // ���� ������� �䱸�ϰ� �˴ϴ�- dead lock
    // �Ʒ� ó�� �ϸ� �ȵ˴ϴ�.
//  acc1.m.lock();
//  acc2.m.lock();

    // �ذ�å�� 
    // ��� ȹ���ϰų�, �ϳ��� ȹ������ �ʰų� �ؾ� �մϴ�.
    std::lock(acc1.m, acc2.m);

    acc1.money -= cnt;
    acc2.money += cnt;
    std::cout << "finish transfer" << std::endl;

    acc1.m.unlock();
    acc2.m.unlock();
}



int main()
{
    Account kim, lee;
    std::thread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::thread t2(transfer, std::ref(lee), std::ref(kim), 5);
    t1.join();
    t2.join();
}

