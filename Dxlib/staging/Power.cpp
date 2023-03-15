#include "Power.h"

using YMath::Power;

void Power::Initialize(const unsigned int max)
{
	end_ = static_cast<float>(max);
	Reset();
}

void Power::Reset()
{
	count_ = 0;
	isAct_ = false;
}

void Power::Update(const bool isAct)
{
	isAct_ = isAct;
	if (isAct)
	{
		count_ += 1.0f;
		if (count_ >= end_) { count_ = end_; }
	}
	else
	{
		count_ -= 1.0f;
		if (count_ <= 0.0f) { count_ = 0.0f; }
	}
}

float Power::Ratio()
{
	if (end_ == 0) { return 0.0f; }
	return count_ / end_;
}