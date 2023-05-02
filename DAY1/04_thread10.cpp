#include <vector>
#include <algorithm>
#include <thread>
#include <iostream>
#include <execution>
#include <syncstream> // C++20 ���� �����Ǵ� ���

void foo(int a)
{
	// std::cout : ���� �����尡 ���ÿ� ȭ�� ����ϸ�
	//			   ��� ��ü�� ����ȭ�ȵ˴ϴ�
//	std::cout << a << " : " << std::this_thread::get_id() << std::endl;

	std::osyncstream out(std::cout);

	out << a << " : " << std::this_thread::get_id() << std::endl;
}   

int main() 
{
	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };

//	std::for_each(v.begin(), v.end(), foo);

	// C++17 ���� STL �˰������� ���� ������ ����
	// => 69���� �˰������� ���� ���� ��밡��
	// => �츮�� ���� "parallel_sum" �� �����մϴ�.
	std::for_each(std::execution::par, v.begin(), v.end(), foo);
	    
}