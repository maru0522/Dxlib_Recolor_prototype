#pragma once
#include "Particle.h"
#include <list>
#include <memory>

// �p�[�e�B�N���}�l�[�W���[
class ParticleManager
{
private:
	std::list<std::unique_ptr<IParticle>> particles_;
public:
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
public:
	// �g(�~)����
	void EmitCircleWave(const bool isRecede, const YMath::Vec2& pos, const int color = 0xFFFFFF);
	// �g(��`)����
	void EmitRectWave(const bool isRecede, const YMath::Vec2& pos, const YMath::Vec2& ratio, const int color = 0xFFFFFF);
};

