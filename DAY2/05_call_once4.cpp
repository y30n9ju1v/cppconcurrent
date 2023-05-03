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
    // �Ʒ� �ڵ带 2���� �����尡 �����Ҷ�(A, B)
    // 
    // �ٽ� 1. �������� - ������ ���� ���� �����˴ϴ�.
    // => A, B�� ���ÿ� ���� ��ü �����˴ϴ�.
    // => �����ڵ� ���� ȣ��˴ϴ�.
    // => ����Ÿ�� ���� ����ϹǷ� �����մϴ�.
    Object obj1;


    // �ٽ� 2. static ��������, 
    // => static �޸𸮿� ���� �Ѱ��� �����˴ϴ�.
    // => ������ ȣ�⵵ �ѹ��� �˴ϴ�.
    // => ���߿� ������ ������� ������ ȣ���� ����ɶ�����
    //    ��� �ϰ� �˴ϴ� => ������ ȣ���� �����մϴ�.
    static Object obj2;


    // �ٽ� 3. �Ϲ� ��� �Լ� ȣ���� ����ȭ ���� �ʽ��ϴ�.
    obj2.init();

    // �ٽ� 4. ��ü�� �������� ����
    // => 2�� ����, ������ ȣ�⵵ ���� ȣ��.. 
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



