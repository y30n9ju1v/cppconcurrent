#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id)
{}

int main()
{
    // �ٽ� 1. �����带 ����� �ݵ�� join(), detach()
    // �ؾ� �մϴ�.
    std::thread t1(&do_work, 1);
    t1.join();

    // create.. 10 thread
    // �ٽ� : ������ �����带 vector �� �����ϴ� ���
    std::vector< std::thread> v; // ũ�Ⱑ 0�� vector

    for (int i = 0; i < 10; i++)
    {
        // ��� 1. ������ ������ vector�� std::move�� �ֱ�
        std::thread t(&do_work, 1);
//      v.push_back(t); // error. ���� �����ڰ� �ʿ��ѵ� 
                        // copy �ȵ�..
        v.push_back(std::move(t)); // ok

        // ��� 2. �ӽð�ü ���·� ���
        v.push_back( std::thread(&do_work, 1) );

        // ��� 3. emplace_back ��� - ���� �����ϴ� ���
        v.emplace_back(&do_work, 1);
                // thread ��ü�� ���� ������ ����
                // ����� ���� ���ڸ� ����
                // emplace_back �� ����������
                // "std::thread t(���޵�����)" �� ����
    }

}
