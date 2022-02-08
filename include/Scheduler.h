#pragma once
#include <queue>
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
		processes.emplace(&proc);
	}
	ver::fire_and_forget start()
	{
		co_await backfire;
	}
private:
	ver::Action main_loop()
	{
		while (time < finish_time && !processes.empty())
		{
			auto proc{ processes.front() };
			//proc->set(&backfire.m_handle);
			co_await proc->behavior;
			//processes.pop();
		}
	}
private:
	std::queue<process_ty*> processes;
	ver::Action backfire = main_loop();
	float time = 0.0f;
	float finish_time;
};