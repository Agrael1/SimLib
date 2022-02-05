#pragma once
#include <queue>
#include <Promises.h>
#include <Process.h>

class Process;

class Scheduler
{
	using process_ty = Process;
public:
	Scheduler(float finish_time)
		:finish_time(finish_time) {}
public:
	void enqueue(process_ty& proc)
	{
		processes.emplace(proc);
	}
	void start()
	{
		main_loop();
		;
	}
private:
	ver::fire_and_forget main_loop()
	{
		while (time < finish_time && !processes.empty())
		{
			auto proc = std::move(processes.front());
			auto x = proc.BehaviorImpl();
			co_await x;
			processes.pop();
		}
	}
private:
	std::queue<process_ty> processes;
	float time = 0.0f;
	float finish_time;
};