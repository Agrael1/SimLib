#include <Scheduler.h>
//#include <cstdio>
//#include <coroutine>
//#include <optional>
#include <Entity.h>


int main()
{
	{
		Scheduler sc(20);
		Process p;
		sc.enqueue(p);

		sc.start();
	}


	int a = 1;
	a++;
	return 0;
}