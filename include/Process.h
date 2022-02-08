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
	ver::fire_and_forget Wait(float dt = 0.0f)
	{
		//return backfire->resume();
		//co_await behavior2.promise.yield_value();
		co_return;
	}
public:
	ver::Action Behavior()
	{

	}
	ver::Action BehaviorImpl()
	{
		a++;
		Wait();
		int a = 10;
		co_await behavior.promise.yield_value();

		co_return;
	}
private:
	int a = 0;
	ver::Action behavior = BehaviorImpl();
};