#include "FillterDrawer.h"
#include "DxLib.h"
#include <cassert>

ParticleManager* FillterDrawer::spParticleMan_ = nullptr;

static const int IntervalTime = 5;
static const int MaxBeaconCount = 3;
static const int BeaconTime = 5;

static const int MaxAlpha = 200;
static const int StopAlpha = 100;

void FillterDrawer::Initialize(Vector2* pPos, const Vector2& size, const int color)
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

void FillterDrawer::Reset()
{
	isMove_ = false;
	beaconDra_.Reset();
}

void FillterDrawer::Switch(const bool isMove)
{
	Reset();
	isMove_ = isMove;
	beaconDra_.Sign(20, !isMove_, MaxBeaconCount, IntervalTime);
}

void FillterDrawer::Update()
{
	beaconDra_.Update();
}

void FillterDrawer::Draw()
{
	// “®‚©‚È‚¢‚È‚ç“§‚¯‚é
	int alpha = MaxAlpha;
	if (isMove_ == false) { alpha = StopAlpha; }

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	Vector2 leftTop = *pPos_ - (size_ / 2.0f);
	Vector2 rigthBottom = *pPos_ + (size_ / 2.0f);
	DrawBox(leftTop.x, leftTop.y, rigthBottom.x, rigthBottom.y, color_, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void FillterDrawer::StaticInitialze(ParticleManager* pParticleMan)
{
	assert(pParticleMan);
	spParticleMan_ = pParticleMan;
}
