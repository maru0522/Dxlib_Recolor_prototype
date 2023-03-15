#include "GateDrawer.h"
#include "DxLib.h"
#include <cassert>

ParticleManager* GateDrawer::spParticleMan_ = nullptr;

static const int IntervalTime = 5;
static const int MaxBeaconCount = 3;

static const int MaxAlpha = 255;
static const int StopAlpha = 150;

void GateDrawer::Initialize(Vector2* pPos, const Vector2& size, const int color)
{
	assert(pPos);
	pPos_ = pPos;
	size_ = size;
	color_ = color;

	// ”ä—¦‚ðŒvŽZ (‘å‚«‚¢‚Ù‚¤Šî€)
	Vector2 ratio;
	if (size.x > size.y)
	{
		ratio.x = 1.0f;
		ratio.y = size_.y / size_.x;
	}
	else if (size.x < size.y)
	{
		ratio.x = size_.x / size_.y;
		ratio.y = 1.0f;
	}
	else
	{
		ratio.x = 1.0f;
		ratio.y = 1.0f;
	}

	beaconDra_.Initialize(pPos, ratio, &color_);

	Reset();
}

void GateDrawer::Initialize(int* pCount, Vector2* pPos, const Vector2& size, const int color)
{
	assert(pCount);
	assert(pPos);
	pCount_ = pCount;
	pPos_ = pPos;
	size_ = size;
	color_ = color;

	// ”ä—¦‚ðŒvŽZ (‘å‚«‚¢‚Ù‚¤Šî€)
	Vector2 ratio;
	if (size.x > size.y)
	{
		ratio.x = 1.0f;
		ratio.y = size_.y / size_.x;
	}
	else if (size.x < size.y)
	{
		ratio.x = size_.x / size_.y;
		ratio.y = 1.0f;
	}
	else
	{
		ratio.x = 1.0f;
		ratio.y = 1.0f;
	}

	beaconDra_.Initialize(pPos, ratio, &color_);

	Reset();
}

void GateDrawer::Reset()
{
	beaconDra_.Reset();
}

void GateDrawer::Pass()
{
	Reset();
	beaconDra_.Sign(20, false, MaxBeaconCount, IntervalTime);
}

void GateDrawer::Update()
{
	beaconDra_.Update();
}

void GateDrawer::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);

	Vector2 leftTop = *pPos_ - (size_ / 2.0f);
	Vector2 rigthBottom = *pPos_ + (size_ / 2.0f);
	DrawBox(leftTop.x, leftTop.y, rigthBottom.x, rigthBottom.y, color_, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (pCount_)
	{
		DrawFormatString(pPos_->x - 10, pPos_->y, 0x0000FF, "%d", *pCount_);
	}
}

void GateDrawer::StaticInitialze(ParticleManager* pParticleMan)
{
	assert(pParticleMan);
	spParticleMan_ = pParticleMan;
}
