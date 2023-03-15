#pragma once
#include "BeaconDrawer.h"

class FillterDrawer
{
private:
	// 位置ポインタ
	Vector2* pPos_ = nullptr;
	// 半径
	Vector2 size_;
	// 色
	int color_ = 0xFFFFFF;
	// 動いているかフラグ
	bool isMove_ = false;

	// ビーコン描画クラス
	BeaconDrawer beaconDra_;
public:
	// 初期化 (位置ポインタ取得)
	void Initialize(Vector2* pPos, const Vector2& size, const int color);
	void Reset();
	void Update();
	void Draw();
public:
	// 操作切り替えたときの演出 (動くならtrue)
	void Switch(const bool isMove);
private:
	// 静的パーティクルマネージャーポインタ
	static ParticleManager* spParticleMan_;
public:
	// 静的初期化
	static void StaticInitialze(ParticleManager* pParticleMan);
};
