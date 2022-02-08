#include <Scheduler.h>


//volatile void* y = 0;
//size_t ptr;
//void* buf;
//
//ver::ResumableAction resuma()
//{
//	co_await std::suspend_always();
//	int i = 10;
//	i++;
//}

//void a()
//{
//	volatile size_t x{};
//	ptr = ((size_t*)y-((void*) & x));
//	buf = malloc(ptr);
//	memcpy(buf, (void*)y, ptr);
//
//	r.emplace(resuma());
//}

//void B()
//{
//	a();
//}
//
//void c()
//{
//	volatile size_t x{};
//	y = &x;
//	B();
//	int i = 10;
//	i++;
//}

//ver::fire_and_forget u()
//{
//	volatile size_t x{};
//	y = &x;
//	while (true)
//	{
//		
//	}
//}

//int main()
//{
//	u();
//
//}
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