#pragma once
#include "Particle.h"
#include <list>
#include <memory>

// パーティクルマネージャー
class ParticleManager
{
private:
	std::list<std::unique_ptr<IParticle>> particles_;
public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
public:
	// 波(円)生成
	void EmitCircleWave(const bool isRecede, const YMath::Vec2& pos, const int color = 0xFFFFFF);
	// 波(矩形)生成
	void EmitRectWave(const bool isRecede, const YMath::Vec2& pos, const YMath::Vec2& ratio, const int color = 0xFFFFFF);
};

