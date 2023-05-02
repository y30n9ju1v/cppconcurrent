#include <thread>

// copy, move

void foo() {}
void goo() {}

int main()
{
    std::thread t1(&foo);
    std::thread t2(&goo);

    // 1. swap
//  t1.swap(t2); // ok

    // 2. copy 는 안되고, move 는 가능합니다.
//  std::thread t3 = t1;            // error. copy 는 안됨
    std::thread t4 = std::move(t1); // ok

    t2.join();
    t4.join();

    // 3. 스레드 객체를 먼저 만들고, 실행(스레드 생성)은 나중에
    std::thread t5; // 객체만 만들었고
                    // 아직 스레드 생성 안됨.

    t5 = std::thread(&foo); // ok
         // ^ 임시객체이므로 rvalue 입니다
         //   move 로 대입

//    std::vector< std::thread> v(10);

    // 객체가 아닌 스레드 자체를 미리 만들수 없나요 ?
    // => 내일 thread pool 할때 합니다.
}



void f1(std::thread t) 
{
    t.join(); 
}

std::thread f2()
{
    return std::thread(foo());
}
