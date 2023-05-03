#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Singleton
{
private:
    Singleton() = default;
    static Singleton* sinstance;

    // static inline : static ��� ����Ÿ�� �ܺμ����� �ʿ�����ϴ�.
    // C++17
    static inline std::once_flag flag;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance()
    {
        // ��Ƽ�����忡 �����ϰ� ��ü�� �Ѱ��� �����ǵ���!
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



