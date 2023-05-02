#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id)
{}

int main()
{
    // 핵심 1. 스레드를 만들면 반드시 join(), detach()
    // 해야 합니다.
    std::thread t1(&do_work, 1);
    t1.join();

    // create.. 10 thread
    // 핵심 : 여러개 스레드를 vector 로 관리하는 기술
    std::vector< std::thread> v; // 크기가 0인 vector

    for (int i = 0; i < 10; i++)
    {
        // 방법 1. 스레드 생성후 vector에 std::move로 넣기
        std::thread t(&do_work, 1);
//      v.push_back(t); // error. 복사 생성자가 필요한데 
                        // copy 안됨..
        v.push_back(std::move(t)); // ok

        // 방법 2. 임시객체 형태로 사용
        v.push_back( std::thread(&do_work, 1) );

        // 방법 3. emplace_back 사용 - 가장 권장하는 방법
        v.emplace_back(&do_work, 1);
                // thread 객체를 만들어서 보내지 말고
                // 만들기 위한 인자를 전달
                // emplace_back 이 내부적으로
                // "std::thread t(전달된인자)" 로 생성
    }

}
