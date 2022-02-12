#pragma once
#include <Promises.h>
#include <memory>
#include <csetjmp>

class Process
{
	friend class Scheduler;
public:
	Process() {}
public:
	ver::task<int> Wait()
	{
		printf("wait\n");
		a++;
		co_await std::suspend_always{};
		a++;
		printf("wait done\n");

		co_return{};
	}
public:
	ver::task<int> Behavior()
	{
		printf("first\n");
		co_await Wait();
		printf("second\n");
		co_await Wait();
		co_return{};
	}
	ver::task<int> BehaviorImpl()
	{
		co_await Behavior();
		co_return{};
	}
private:
	ver::task<int> x = BehaviorImpl();
	int a = 0;
};