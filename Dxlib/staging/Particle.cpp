#include "Particle.h"
#include "DxLib.h"

using YMath::Vec2;
using YMath::Vec3;

void Wave::Emit(const int frame, const YMath::Vec2& pos, const int color, const bool isFill)
{
	scaleEas_.Initialize(0.0f, 100.0f, 3.0f);
	alphaEas_.Initialize(255, 0, 2.0f);

	scaleTim_.Initialize(frame);
	scaleTim_.SetActive(true);

	pos_ = pos;
	color_ = color;
	isFill_ = isFill;

	isAlive_ = true;
}

void Wave::Update()
{
	if (isAlive_ == false) { return; }

	scaleTim_.Update();
	if (scaleTim_.IsEnd()) { isAlive_ = false; }

	scale_.x_ += scaleEas_.In(scaleTim_.Ratio());
	alpha_ = alphaEas_.In(scaleTim_.Ratio());
}

void Wave::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	DrawCircle(pos_.x_, pos_.y_, scale_.x_, color_, isFill_);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
