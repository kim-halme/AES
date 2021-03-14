#pragma once

#include <chrono>
#include <iostream>

struct Timer
{
public:
	Timer();
	~Timer();
	void Stop();
private:
	std::chrono::steady_clock::time_point mStartTimepoint, mEndTimepoint;
};