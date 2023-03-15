#include "BeaconDrawer.h"
#include <cassert>

ParticleManager* BeaconDrawer::spParticleMan_ = nullptr;

void BeaconDrawer::Initialize(Vector2* pPos, int* pColor)
{
	assert(pPos);
	pPos_ = pPos;

	shape = Shape::Circle;
	pColor_ = pColor;

	Reset();
}

void BeaconDrawer::Initialize(Vector2* pPos, const Vector2& ratio, int* pColor)
{
	assert(pPos);
	pPos_ = pPos;

	shape = Shape::Rectangle;
	ratio_ = ratio;
	pColor_ = pColor;

	Reset();
}

void BeaconDrawer::Reset()
{
	isAct_ = false;
	frame_ = 0;
	intervalTim_.Reset(false);
	counter_ = 0;
	maxCount_ = 0;
	isSign_ = false;
	isRecede_ = false;
}

void BeaconDrawer::Sign(const uint32_t frame, const bool isRecede, const uint32_t count, const uint32_t intervalFrame)
{
	Reset();

	frame_ = frame;
	maxCount_ = count;
	intervalTim_.Initialize(intervalFrame);
	intervalTim_.SetActive(true);

	isRecede_ = isRecede;
	isAct_ = true;
}

void BeaconDrawer::Update()
{
	// 動作していないなら更新しない
	if (isAct_ == false) { return; }

	// 発信フラグを戻す
	isSign_ = false;

	// インターバルタイマー更新
	intervalTim_.Update();
	// インターバルタイマーが終わったら
	if (intervalTim_.IsEnd())
	{
		// もう一度やるか
		bool isAgain = true;

		// カウントが最大値なら
		counter_++;
		if (counter_ >= maxCount_)
		{
			// 終了
			isAgain = false;
			isAct_ = false;
		}

		// リセット
		intervalTim_.Reset(isAgain);

		// 発信
		isSign_ = true;
	}

	// 発信するなら
	if (isSign_)
	{
		// 自分の位置にパーティクル発生
		if (shape == Shape::Circle)
		{
			spParticleMan_->EmitCircleWave(frame_, isRecede_, { pPos_->x, pPos_->y }, *pColor_);
		}
		else if (shape == Shape::Rectangle)
		{
			spParticleMan_->EmitRectWave(frame_, isRecede_, { pPos_->x, pPos_->y }, { ratio_.x, ratio_.y }, *pColor_);
		}
	}
}

void BeaconDrawer::StaticInitialze(ParticleManager* pParticleMan)
{
	assert(pParticleMan);
	spParticleMan_ = pParticleMan;
}
