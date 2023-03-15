#include "ParticleManager.h"
#include "MathUtillity.h"

const float PI = 3.141592f;

void ParticleManager::Initialize()
{
	// パーティクル全削除
	if (particles_.empty() == false)
	{
		particles_.clear();
	}
}

void ParticleManager::Update()
{
	// パーティクル死んだら削除
	particles_.remove_if([](std::unique_ptr<IParticle>& particle) { return particle->isAlive_ == false; });
	
	// パーティクル毎更新
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Update();
	}
}

void ParticleManager::Draw()
{
	// パーティクル描画
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Draw();
	}
}

void ParticleManager::EmitCircleWave(const bool isRecede, const YMath::Vec2& pos, const int color)
{
	std::unique_ptr<CircleWave> newParticle = std::make_unique<CircleWave>();

	newParticle->Emit(20, isRecede, pos, color, false);
	particles_.push_back(std::move(newParticle));
}

void ParticleManager::EmitRectWave(const bool isRecede, const YMath::Vec2& pos, const YMath::Vec2& ratio, const int color)
{
	std::unique_ptr<RectWave> newParticle = std::make_unique<RectWave>();

	newParticle->Emit(20, isRecede, pos, ratio, color, false);
	particles_.push_back(std::move(newParticle));
}
