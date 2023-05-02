#include <iostream>
#include <thread>

void foo() {}

int main()
{
    std::thread t1(&foo);

    t1.join();  // ok.. 
//  t1.join();  // runtime error. 이미 join 한것을 다시 할수없습니다

    std::thread t2; // 스레드 객체만 만들었습니다.
                    // 함수를 전달하지 않으면
                    // 아직, 스레드가 생성된것은 아닙니다
    t2.join(); // runtime error. 아직 스레드 생성안됨

    if (t2.joinable()) // join 가능한가를 조사
    {
        t2.join();
    }

    // joinable : join 이 가능한가를 조사하는 것
    // => 스레드가 살아있는지 조사하는 것은 아닙니다.
    std::thread t3(&f1);
    std::thread t4(&f2);

    bool b1 = t3.joinable(); // f1이 실행중이건
    bool b2 = t4.joinable(); // f2가 종료되었건
                             // 모두 true
}
