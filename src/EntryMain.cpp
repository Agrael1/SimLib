#include <Promises.h>
#include <source_location>
#include <string_view>
#include <cstdio>

void print(std::string_view r, std::source_location a = std::source_location::current())
{
	printf("%s %s\n", a.function_name(), r.data());
}

ver::action Wait()
{
	co_await 0.5;
}

void func()
{
	print("begin");
	Wait();
	print("wait");
	Wait();
	print("end");
}

ver::delayed_action long_process()
{
	print("begin");
	func();
	print("end");
	co_return;
}

ver::delayed_operation<int> short_process()
{
	print("begin");
	co_await 0.5;
	print("end");
	co_return 10;
}

int main()
{
	auto lproc = long_process();
	auto sproc = short_process();

	scheduler.push(sproc.m_handle);
	scheduler.push(lproc.m_handle);
	scheduler.front().resume();

	return *sproc.get();
}