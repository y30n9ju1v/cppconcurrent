#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std::literals;

void foo();

// 네트워크 서버를 만든다고 생각해 봅시다.
int main()
{
	while (true)
	{
		// 1. 서버는 클라이언트의 접속을 대기 합니다.
		getchar();

		// 2. 클라이언트가 접속하면 "새로운 스레드를 생성" 해서
		//    클라이언트의 요청을 처리합니다
		std::thread t(foo);
		t.detach();

		// 3. 주스레드는 다시 1번으로 이동해서 다른 클라이언트 접속 대기
	}
}
// 위 코드의 단점
// 1. 스레드의 생성/파괴가 계속 일어납니다.
// => OS 입장에서는 스레드를 생성/파괴 하는 것은 오버헤드가 꽤 큽니다.

// 2. 스레드 갯수를 제한할수 없습니다.
// => 요청이 많으면 무수히 많은 스레드가 생성됩니다
// => 모든 서비스의 품질 저하..

// 해결책
// => 미리 원하는 갯수만 큼만 생성한후에
// => 재워 놓고, 필요 할때 깨워서 사용







//--------------------------------------------------
void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
}
