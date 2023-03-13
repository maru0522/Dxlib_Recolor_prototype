#pragma once
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"

// パーティクルインターフェース
class IParticle
{
public:
	bool isAlive_ = false;	 // 生存フラグ
protected:
	YMath::Vec2 pos_;	 // 位置
	YMath::Vec2 rota_;	 // 角度
	YMath::Vec2 scale_;	 // 大きさ
	int color_ = 0xFFFFFF; // 色
	int alpha_ = 255; // 透過度
	bool isFill_ = true;
public:
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;
public:
	IParticle() = default;
	virtual ~IParticle() = default;
};

// 波
class Wave : public IParticle 
{
private:
	YMath::Ease<float> scaleEas_; // 大きさ補間
	YMath::Ease<int> alphaEas_; // 透過度補間
	YMath::Timer scaleTim_; // 補間用タイマー
public:
	// 生成
	void Emit(const int frame, const YMath::Vec2& pos, const int color = 0xFFFFFF, const bool isFill = true);
	void Update() override;
	void Draw() override;
public:
	Wave() = default;
	~Wave() override = default;
};