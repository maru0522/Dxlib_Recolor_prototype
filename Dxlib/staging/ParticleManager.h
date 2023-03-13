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
	// 波生成
	void EmitWave(const YMath::Vec2& pos, const int color = 0xFFFFFF);
};

