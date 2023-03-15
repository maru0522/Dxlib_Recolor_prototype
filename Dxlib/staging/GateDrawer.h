#pragma once
#include "BeaconDrawer.h"

class GateDrawer
{
private:
	// 位置ポインタ
	Vector2* pPos_ = nullptr;
	// 半径
	Vector2 size_;
	// 色
	int color_ = 0xFFFFFF;
	// 現在の回数ポインタ
	int* pCount_ = nullptr;

	// ビーコン描画クラス
	BeaconDrawer beaconDra_;
public:
	// 初期化 (位置ポインタ取得)
	void Initialize(Vector2* pPos, const Vector2& size, const int color);
	// 初期化 (位置ポインタ取得, 回数制限があるか)
	void Initialize(int* pCount, Vector2* pPos, const Vector2& size, const int color);
	void Reset();
	void Update();
	void Draw();
public:
	// くぐったときの演出
	void Pass();
private:
	// 静的パーティクルマネージャーポインタ
	static ParticleManager* spParticleMan_;
public:
	// 静的初期化
	static void StaticInitialze(ParticleManager* pParticleMan);
};

