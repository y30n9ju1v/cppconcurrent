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

    // 스레드가 실행중이건 종료 되었건 t3, t4 는 모두 join가능
    bool b1 = t3.joinable(); // f1이 실행중이건
    bool b2 = t4.joinable(); // f2가 종료되었건
                             // 모두 true

    // 스레드를 만들지 않거나
    // 이미 join(또는 detach) 한 경우만 false 입니다.
    std::thread t5;
    std::thread t6(&f2);
    t6.join(); // t6.detach();

    bool b1 = t5.joinable();  // 스레드 생성 안됨
    bool b2 = t6.joinable();  // 이미 join 했음
}
