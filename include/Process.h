#pragma once
#include <Promises.h>
#include <memory>

class Process
{
	friend class Scheduler;
public:
	Process() {}
public:
	virtual void Behavior() {}
private:
	ver::Action BehaviorImpl()
	{
		co_return Behavior();
	}
};