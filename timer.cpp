#include "timer.h"

Timer::Timer()
{
	mStartTimepoint = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	Stop();
}

void Timer::Stop()
{
	mEndTimepoint = std::chrono::high_resolution_clock::now();

	long long start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartTimepoint).time_since_epoch().count();
	long long end = std::chrono::time_point_cast<std::chrono::microseconds>(mEndTimepoint).time_since_epoch().count();

	double micro_seconds = end - start;
	double milli_seconds = micro_seconds * 0.001;

	std::cout << "Operation took " << micro_seconds << " microseconds or " << milli_seconds << " milliseconds" << std::endl;
}