#include <Scheduler.h>

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