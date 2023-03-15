#include "Timer.h"

using YMath::Timer;

void Timer::Initialize(const unsigned int time)
{
	end_ = static_cast<float>(time);
	Reset(false);
}

void Timer::Reset(const bool isAct)
{
	count_ = 0;
	isAct_ = isAct;
}

void Timer::Update()
{
	if (!isAct_) { return; }

	count_ += 1.0f;
	if (count_ >= end_)
	{
		count_ = end_;
		isAct_ = false;
	}
}

float Timer::Ratio()
{
	if (end_ == 0) { return 0.0f; }
	return count_ / end_;
}
