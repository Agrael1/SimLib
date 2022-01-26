#include <Log.h>
#include <iostream>
#include <format>

void Log::Print()
{
	for (auto& i : msgvec){
		std::cout << std::format("[{}]: {}", Message::levels[size_t(i.level())], i.Text());
	}
}
