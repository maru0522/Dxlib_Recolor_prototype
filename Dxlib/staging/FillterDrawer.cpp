#include "FillterDrawer.h"
#include "DxLib.h"
#include <cassert>

ParticleManager* FillterDrawer::spParticleMan_ = nullptr;

static const int IntervalTime = 5;
static const int MaxBeaconCount = 3;

static const int MaxAlpha = 200;
static const int StopAlpha = 100;

void FillterDrawer::Initialize(Vector2* pPos, const Vector2& size, const int color)
{
	assert(pPos);
	pPos_ = pPos;
	size_ = size;
	color_ = color;

	intervalTim_.Initialize(IntervalTime);

	Reset();
}

void FillterDrawer::Reset()
{
	isMove_ = false;
	isBeaconAct_ = false;
	intervalTim_.Reset(false);
	beaconCounter_ = 0;
	isSign_ = false;
}

void FillterDrawer::Switch(const bool isMove)
{
	Reset();
	isMove_ = isMove;
	intervalTim_.SetActive(true);
	isBeaconAct_ = true;
}

void FillterDrawer::Update()
{
	// ビーコンが動作していないなら更新しない
	if (isBeaconAct_ == false) { return; }

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
		beaconCounter_++;
		if (beaconCounter_ >= MaxBeaconCount)
		{
			// 終了
			isAgain = false;
			isBeaconAct_ = false;
		}

		// リセット
		intervalTim_.Reset(isAgain);

		// 発信
		isSign_ = true;
	}

	// 発信するなら
	if (isSign_)
	{
		// 比率を計算 (X基準)
		Vector2 ratio;
		ratio.x = 1.0f;
		ratio.y = size_.y / size_.x;

		// 自分の位置にパーティクル発生 (動く → 押す波)
		spParticleMan_->EmitRectWave(!isMove_, { pPos_->x, pPos_->y }, { ratio.x, ratio.y }, color_);
	}
}

void FillterDrawer::Draw()
{
	// 動かないなら透ける
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
