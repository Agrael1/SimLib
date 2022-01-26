/////////////////////////////////////////////////////////////////////////////
//! \file  Stats.cpp Statsistics
//
// Copyright (c) 1991-2004 Petr Peringer
//
// This library is licensed under GNU Library GPL. See the file COPYING.
//
#include <Stats.h>


void Stats::operator () (float x) noexcept
{
	Record(x);
}
void Stats::Record(float x) noexcept
{
	sx += x;
	sx2 += x * x;
	if (++n == 1) min = max = x;
	else {
		min = std::min(x, min); 
		max = std::max(x, max);
	}
}

Stats& Stats::operator+=(Stats& x)noexcept
{
	sx += x.sx;
	sx2 += x.sx2;
	min = std::min(min, x.min);
	max = std::max(max, x.max);
	n += x.n;
	return *this;
}
void Stats::Clear() noexcept
{
	sx = sx2 = 0;    // sums
	min = max = 0;
	n = 0;           // # of records
}
std::optional<float> Stats::MeanValue() const noexcept
{
	if (!n)return{};
	return sx / n;
}
std::optional<float> Stats::StdDev() const noexcept
{
	if (n < 2) return{};
	float mv = sx / n;
	return sqrt((sx2 - n * mv * mv) / (n - 1));
}
