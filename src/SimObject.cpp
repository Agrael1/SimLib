#include <ostream>
#include <SimObject.h>

std::ostream& operator<<(std::ostream& in, const SimObject& obj)
{
	return in << obj.Output();
}