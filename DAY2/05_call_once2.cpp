#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Singleton
{
private:
    Singleton() = default;
    static Singleton* sinstance;

    // static inline : static 멤버 데이타의 외부선언이 필요없습니다.
    // C++17
    static inline std::once_flag flag;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance()
    {
        // 멀티스레드에 안전하게 객체를 한개만 생성되도록!
        std::call_once(flag, init);

        return sinstance;
    }
    static void init()
    {
        sinstance = new Singleton;
    }
};

Singleton* Singleton::sinstance = nullptr;

int main()
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;
}



