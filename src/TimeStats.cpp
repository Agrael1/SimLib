#include <TimeStats.h>
#include <System.h>
#include <Log.h>
#include <Errors.h>

void TimeStat::Clear() noexcept
{
	sxt = sx2t = .0;
	min = max = .0;
	t0 = tl = sys.Time();
	xl = .0;       // last value
	n = 0UL;
}

void TimeStat::Record(float x) noexcept
{
	auto Time = sys.Time();
	if (Time < tl)
		Log::Warning()<<ErrMsg(Error::TStatNotInitialized);//SIMLIB_warning(TStatNotInitialized);
	auto tt = xl * (Time - tl);
	sxt += tt;
	sx2t += xl * tt;
	xl = x;
	tl = Time;
	if (++n == 1) min = max = x;   // TODO: check
	else
	{
		if (x < min) min = x;
		if (x > max) max = x;
	}
}

std::optional<float> TimeStat::MeanValue() const noexcept
{
	if (!n)return{};
	if (sys.Time() == t0)  return xl;
	float sumxt = sxt + xl * (sys.Time() - tl); // count last period
	return sumxt / (sys.Time() - t0);
}
