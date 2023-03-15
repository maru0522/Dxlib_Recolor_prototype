#pragma once
#include "../Vector2.h"
#include "ParticleManager.h"

class BeaconDrawer
{
private:
	// 形の種類
	enum class Shape
	{
		Circle, // 円
		Rectangle, // 矩形
		None, // 無し
	};
private:
	// 形
	Shape shape = Shape::None;

	// 位置ポインタ
	Vector2* pPos_ = nullptr;
	// 比率
	Vector2 ratio_;
	// 色
	int* pColor_ = nullptr;

	// 動作フラグ
	bool isAct_ = false;
	// フレーム
	uint32_t frame_ = 0;
	// インターバルタイマー
	YMath::Timer intervalTim_;
	// 発信カウンタ
	int counter_ = 0;
	// 最大発信回数
	int maxCount_ = 0;
	// 発信フラグ
	bool isSign_ = false;
	// 引きフラグ
	bool isRecede_ = false;
public:
	// 初期化 (位置ポインタ取得)
	void Initialize(Vector2* pPos, int* pColor);
	// 初期化 (位置ポインタ, 比率取得)
	void Initialize(Vector2* pPos, const Vector2& ratio, int* pColor);
	void Reset();
	void Update();
public:
	// 発信
	void Sign(const uint32_t frame, const bool isRecede, const uint32_t count, const uint32_t intervalFrame);
private:
	// 静的パーティクルマネージャーポインタ
	static ParticleManager* spParticleMan_;
public:
	// 静的初期化
	static void StaticInitialze(ParticleManager* pParticleMan);
};

