#pragma once
#include <SimObject.h>
#include <optional>

////////////////////////////////////////////////////////////////////////////
//! class for statistical information gathering
//! \ingroup simlib
class Stats : public SimObject
{
public:
	Stats() = default;
	using SimObject::SimObject;
public:
	virtual void Clear()noexcept;		//!< initialize
	void operator () (float x)noexcept;	//!< record the value
	void Record(float x)noexcept;		//!< record the value, alternative to operator

	/// @brief Sums up two statistics
	/// @param x other statistics
	/// @return reference to this modified object
	Stats& operator += (Stats& x)noexcept;

	size_t Number() const noexcept { return n; }
	std::optional<float> Min() const noexcept { if (!n)return{}; return min; }
	std::optional<float> Max() const noexcept { if (!n)return{}; return max; }
	std::optional<float> Sum() const noexcept { if (!n)return{}; return sx; }
	std::optional<float> SumSquare() const noexcept { if (!n)return{}; return sx2; }
	std::optional<float> MeanValue() const noexcept;

	/// @brief Returns standard deviation of statistics
	/// Does not work if number of stats is less than 2
	/// @return standard deviation or nullopt if n is less than two
	std::optional<float> StdDev() const noexcept;
protected:
	float sx = 0.0f;		///<sum of values
	float sx2 = 0.0f;		///<sum of value square
	float min = 0.0f;		///<min value
	float max = 0.0f;		///<max value
	size_t n = 0;			///<number of values recorded
};