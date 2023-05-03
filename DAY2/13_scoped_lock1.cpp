#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

struct  Account
{
    std::mutex m; // money의 접근 동기화를 위한 뮤텍스
    int money = 100;
};


void transfer(Account& acc1, Account& acc2, int cnt)
{
    // 2개 계좌를 모두 접근해야 하므로 모든 뮤텍스 획득
    // 아래처럼 만들면, 최악의 경우 2개의 스레드가 각각 mutex 하나씩 획득하고
    // 서로 상대방것을 요구하게 됩니다- dead lock
    // 아래 처럼 하면 안됩니다.
//  acc1.m.lock();
//  acc2.m.lock();

    // 해결책은 
    // 모두 획득하거나, 하나도 획득하지 않거나 해야 합니다.
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

