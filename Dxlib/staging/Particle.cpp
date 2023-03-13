#include "Particle.h"
#include "DxLib.h"

using YMath::Vec2;
using YMath::Vec3;

void CircleWave::Emit(const int frame, const bool isRecede, const YMath::Vec2& pos, const int color, const bool isFill)
{
	if (isRecede)
	{
		scaleEas_.Initialize(100.0f, 0.0f, 3.0f);
		alphaEas_.Initialize(0, 255, 2.0f);
	}
	else
	{
		scaleEas_.Initialize(0.0f, 100.0f, 3.0f);
		alphaEas_.Initialize(255, 0, 2.0f);
	}

	scaleTim_.Initialize(frame);
	scaleTim_.SetActive(true);

	pos_ = pos;
	color_ = color;
	isFill_ = isFill;

	isAlive_ = true;
}

void CircleWave::Update()
{
	if (isAlive_ == false) { return; }

	scaleTim_.Update();
	if (scaleTim_.IsEnd()) { isAlive_ = false; }

	scale_.x_ += scaleEas_.In(scaleTim_.Ratio());
	alpha_ = alphaEas_.In(scaleTim_.Ratio());
}

void CircleWave::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	DrawCircle(pos_.x_, pos_.y_, scale_.x_, color_, isFill_);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void RectWave::Emit(const int frame, const bool isRecede, const YMath::Vec2& pos, const YMath::Vec2& ratio, 
	const int color, const bool isFill)
{
	if (isRecede)
	{
		Vec2 end = ratio * 100.0f;
		scaleEas_.Initialize(end, {}, 3.0f);
		alphaEas_.Initialize(0, 255, 2.0f);
	}
	else
	{
		Vec2 end = ratio * 100.0f;
		scaleEas_.Initialize({}, end, 3.0f);
		alphaEas_.Initialize(255, 0, 2.0f);
	}

	scaleTim_.Initialize(frame);
	scaleTim_.SetActive(true);

	pos_ = pos;
	color_ = color;
	isFill_ = isFill;

	isAlive_ = true;
}

void RectWave::Update()
{
	if (isAlive_ == false) { return; }

	scaleTim_.Update();
	if (scaleTim_.IsEnd()) { isAlive_ = false; }

	scale_ += scaleEas_.In(scaleTim_.Ratio());
	alpha_ = alphaEas_.In(scaleTim_.Ratio());
}

void RectWave::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);

	Vec2 leftTop = pos_ - (scale_ / 2.0f);
	Vec2 rigthBottom = pos_ + (scale_ / 2.0f);
	DrawBox(leftTop.x_, leftTop.y_, rigthBottom.x_, rigthBottom.y_, color_, isFill_);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
