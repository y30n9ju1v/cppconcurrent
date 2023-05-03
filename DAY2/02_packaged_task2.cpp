#include <iostream>
#include <thread>
#include <future>

// 39 page

// 일반 함수라면 아래 처럼 만들게 됩니다.
// => 이미 아래 처럼 만들어진 함수를 스레드로 수행해서 결과 얻기
int add(int a, int b)
{
	return a + b;
}

int main()
{
	// 1. packaged_task 타입의 객체를 생성합니다.
	std::packaged_task<int(int, int)> task(add);

	// 2. packaged_task 객체에서 future를 꺼냅니다.
	std::future<int> ft = task.get_future();

	// 3. 주스레드가 실행해도 됩니다.
//	task(1, 2);  // () 연산자가 재정의 되어 있으므로
				 // 이렇게 호출가능
				 // add(1, 2)
//	int ret1 = ft.get();

	// 4. 새로운 스레드를 만들때 1번째 인자로 task 전달하면 됩니다.
	// std::ref(task)  : task 를 계속 사용하고 싶을때
	// std::move(task) : task 객체가 더이상 필요 없다면
	//std::thread t(std::ref(task), 1, 2); 
	std::thread t(std::move(task), 1, 2);
	
	int ret2 = ft.get();
	t.join();
}

// promise & future : 함수인자로 promise 를 받아야 합니다
// 
// packaged_task    : 스레드 함수가 아닌 일반 함수 모양으로
//						만들어진 함수를 스레드로 수행해서 결과 얻기
//						"보관" 했다가 "원할때 실행"

