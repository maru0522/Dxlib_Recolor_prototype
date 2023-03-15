#include "ParticleManager.h"
#include "MathUtillity.h"

const float PI = 3.141592f;

void ParticleManager::Initialize()
{
	// �p�[�e�B�N���S�폜
	if (particles_.empty() == false)
	{
		particles_.clear();
	}
}

void ParticleManager::Update()
{
	// �p�[�e�B�N�����񂾂�폜
	particles_.remove_if([](std::unique_ptr<IParticle>& particle) { return particle->isAlive_ == false; });
	
	// �p�[�e�B�N�����X�V
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Update();
	}
}

void ParticleManager::Draw()
{
	// �p�[�e�B�N���`��
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
