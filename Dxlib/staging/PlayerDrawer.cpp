#include "PlayerDrawer.h"
#include "DxLib.h"
#include <cassert>

ParticleManager* PlayerDrawer::spParticleMan_ = nullptr;

static const int MaxBeaconCount = 3;
static const int IntervalTime = 5;
static const int BeaconTime = 5;

static const int MaxAlpha = 255;
static const int StopAlpha = 150;

void PlayerDrawer::Initialize(Vector2* pPos, const Vector2& size, const int color)
{
	assert(pPos);
	pPos_ = pPos;
	size_ = size;
	color_ = color;

	beaconDra_.Initialize(pPos, &color_);

	Reset();
}

void PlayerDrawer::Reset()
{
	isMove_ = true;
	beaconDra_.Reset();
}

void PlayerDrawer::ChangeColor(const int color)
{
	beaconDra_.Reset();
	color_ = color;
	beaconDra_.Sign(20, !isMove_, MaxBeaconCount, IntervalTime);
}

void PlayerDrawer::Switch(const bool isMove)
{
	beaconDra_.Reset();
	isMove_ = isMove;
	beaconDra_.Sign(20, !isMove_, MaxBeaconCount, IntervalTime);
}

void PlayerDrawer::Update()
{
	beaconDra_.Update();
}

void PlayerDrawer::Draw()
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

void PlayerDrawer::StaticInitialze(ParticleManager* pParticleMan)
{
	assert(pParticleMan);
	spParticleMan_ = pParticleMan;
}
