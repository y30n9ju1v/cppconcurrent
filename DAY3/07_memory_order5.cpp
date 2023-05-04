#include <thread>
#include <atomic>
#include <cassert>

std::atomic<int> data1 = 0;
std::atomic<int> data2 = 0;

int main()
{
    // memory_order_seq_cst : �ݵ�� ���������� ����Ǿ�� �Ѵ�.
    // => ���� �䱸������ �����ϴ�. 
    // => ���� ������尡 ū ��� �Դϴ�.
    data1.store(100, std::memory_order_seq_cst);
    data2.store(200, std::memory_order_seq_cst);
    data2.store(300); // 2��° ���ڻ����� ����Ʈ �� �Դϴ�.

    ++data2; // �� ���� �ϸ�  memory_order_seq_cst

    data2.fetch_add(1, std::memory_order_relaxed); 
            // �� �ڵ� ���� ���� �� ȿ������ ���� �ڵ�
}