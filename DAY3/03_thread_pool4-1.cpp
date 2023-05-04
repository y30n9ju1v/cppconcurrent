// threadpool4-1
#include <functional>

void foo(int a, int b) {}

int main()
{
	// C의 일반 함수 포인터는 반드시 함수 모양이 동일해야 합니다.
	void(*f)() = &foo; // error

	// std::function 은 std::bind 를 사용하면 인자를 고정해서
	// 보관가능
	std::function<void()> f1;
	//f1 = &foo;	// error. foo 는 인자가 2개 인데
				// f1은 인자가 없는 함수 만 보관

	f1 = std::bind(&foo, 1, 2); // foo 와 인자 2개를 같이 보관
	f1(); // foo(1,2);
}