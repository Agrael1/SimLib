#include <Promises.h>

ver::action Wait()
{
	co_await 0.5;
}

void func()
{
	puts(__FUNCTION__ " begin");
	Wait();
	puts(__FUNCTION__ " wait");
	Wait();
	puts(__FUNCTION__ " end");
}

ver::delayed_action long_process()
{
	puts(__FUNCTION__ " begin");
	func();
	puts(__FUNCTION__ " end");
	co_return;
}

ver::delayed_operation<int> short_process()
{
	puts(__FUNCTION__ " begin");
	co_await 0.5;
	puts(__FUNCTION__ " end");
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