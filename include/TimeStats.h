#pragma once
#include <SimObject.h>
#include <optional>

class System;

////////////////////////////////////////////////////////////////////////////
//! time dependent statistic
//! \ingroup simlib
class TimeStat : public SimObject 
{
public:
	TimeStat(System& sys, std::string_view name = "") :sys(sys) {};
public:
	void Clear()noexcept;					//!< initialize
	void operator () (float x)noexcept { Record(x); }		//!< record the value
	void Record(float x)noexcept;			//!< record the value, alternative to operator
	size_t Number() const noexcept { return n; }
	std::optional<float> Min() const noexcept { if (!n)return{};return min; }
	std::optional<float> Max() const noexcept { if (!n)return{};return max; }
	std::optional<float> Sum() const noexcept { if (!n)return{};return sxt; }
	std::optional<float> SumSquare() const noexcept { if (!n)return{};return sx2t; }
	std::optional<float> StartTime() const noexcept { if (!n)return{};return t0; }
	std::optional<float> LastTime() const noexcept { return tl; }
	std::optional<float> LastValue() const noexcept { return xl; }
	std::optional<float> MeanValue() const noexcept;
private:
	System& sys;
	size_t n = 0;			///<number of records
	float sxt = 0.0f;		///<sum of x*time
	float sx2t = 0.0f;		///<sum of squares
	float min = 0.0f;		///<min value x
	float max = 0.0f;		///<max value x
	float t0 = 0.0f;		///<time of initialization
	float tl = 0.0f;		///<last record time
	float xl = 0.0f;		///<last recorded value x
};
