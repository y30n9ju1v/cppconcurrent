#include <iostream>
#include <thread>
#include <future>
int add(int a, int b)
{
	std::cout << "add" << std::endl;
	return a + b;
}
int main()
{
	std::packaged_task<int(int, int)> task(add);
	// task 에 담긴 작업을 2번 실행하는 경우.
	// task 가 내부적으로 promise 를 사용하게 됩니다.
	task(1, 2);
//	task(1, 2); // 예외 발생
	task.reset();
	task(1, 2);


}


