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
    // 아래 처럼하면 unlock 을 직접해야 합니다.
    // std::lock(acc1.m, acc2.m); 

    // 아래 처럼 하면 소멸자가 unlock 합니다.
    // => 생성자에서는 std::lock 사용
    //std::scoped_lock<std::mutex, std::mutex> g(acc1.m,
    //                                          acc2.m);

    // C++17 부터는 템플릿 인자 생략 가능
    std::scoped_lock g(acc1.m, acc2.m);


    acc1.money -= cnt;
    acc2.money += cnt;
    std::cout << "finish transfer" << std::endl;

//  acc1.m.unlock();
//  acc2.m.unlock();
}



int main()
{
    Account kim, lee;
    std::thread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::thread t2(transfer, std::ref(lee), std::ref(kim), 5);
    t1.join();
    t2.join();
}

