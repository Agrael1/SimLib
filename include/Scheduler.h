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
	void start()
	{
		main_loop();
	}
private:
	void main_loop()
	{
		while (time < finish_time && !processes.empty())
		{
			auto proc{ processes.front() };
			proc->x.one_step();
			printf("done\n");
			//processes.pop();
		}
	}
private:
	std::queue<process_ty*> processes;
	float time = 0.0f;
	float finish_time;
};