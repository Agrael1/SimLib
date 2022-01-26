#pragma once
#include <string>

class SimObject
{
public:
	SimObject() = default;
	SimObject(std::string_view name):name(name){}
	virtual ~SimObject() = default;
public:
	virtual std::string Output()const noexcept{
		return name;
	}
	std::string_view Name()const noexcept { return name; }
	void SetName(std::string_view xname) { name = xname; }
	friend std::ostream& operator<<(std::ostream& in, const SimObject& obj);
private:
	std::string name;
};

std::ostream& operator<<(std::ostream& in, const SimObject& obj);
