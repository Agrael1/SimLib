#pragma once

class System
{
public:
	System() = default;
public:
	float Time()const noexcept { return time; }
private:
	float time = 0.0f;
};
