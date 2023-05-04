#include <memory>
#include <iostream>
#include <future>
#include <functional>
#include <vector>

using F = std::function<void()>;

std::vector<F> v;


int add(int a, int b)
{
	std::cout << "add" << std::endl;

	return a + b;
}

// 핵심 : 함수의 반환 값을 얻으려면 

int main()
{
	// 함수를 호출하면 즉시 반환값을 얻을수 있습니다.
	int ret1 = add(1, 2);

	// packaged_task 를 사용하면 아직 실행되지 않은 함수의 
	// 결과를 얻을수 있습니다.
	std::packaged_task<int(int, int)> task(add);

	// add 가 실행되지 않았지만 미래의 결과를 담은 객체는
	// 꺼낼수 있습니다.
	std::future<int> ft = task.get_future(); 

	int ret2 = ft.get();

}