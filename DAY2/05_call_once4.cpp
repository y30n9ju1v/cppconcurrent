#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Object
{
    int member_data;
public:
    Object()
    {
        std::cout << "start ctor" << std::endl;
        std::this_thread::sleep_for(3s);
        std::cout << "finish ctor" << std::endl;
    }
    void init()
    {
        std::cout << "start init" << std::endl;
        std::this_thread::sleep_for(3s);
        std::cout << "finish init" << std::endl;
    }
};

void foo()
{
    // 아래 코드를 2개의 스레드가 실행할때(A, B)
    // 
    // 핵심 1. 지역변수 - 스레드 별로 따로 생성됩니다.
    // => A, B의 스택에 각각 객체 생성됩니다.
    // => 생성자도 각각 호출됩니다.
    // => 데이타를 따로 사용하므로 안전합니다.
    Object obj1;


    // 핵심 2. static 지역변수, 
    // => static 메모리에 오직 한개만 생성됩니다.
    // => 생성자 호출도 한번만 됩니다.
    // => 나중에 도착한 스레드는 생성자 호출이 종료될때가지
    //    대기 하게 됩니다 => 생성자 호출은 안전합니다.
    static Object obj2;


    // 핵심 3. 일반 멤버 함수 호출은 동기화 되지 않습니다.
    obj2.init();

    // 핵심 4. 객체를 동적으로 생성
    // => 2개 생성, 생성자 호출도 각각 호출.. 
    Object* p = new Object;
    delete p;
}



int main()
{
    std::thread t1(&foo);
    std::thread t2(&foo);

    t1.join();
    t2.join();
}



