#pragma once
#include "BeaconDrawer.h"

class GateDrawer
{
private:
	// �ʒu�|�C���^
	Vector2* pPos_ = nullptr;
	// ���a
	Vector2 size_;
	// �F
	int color_ = 0xFFFFFF;
	// ���݂̉񐔃|�C���^
	int* pCount_ = nullptr;

	// �r�[�R���`��N���X
	BeaconDrawer beaconDra_;
public:
	// ������ (�ʒu�|�C���^�擾)
	void Initialize(Vector2* pPos, const Vector2& size, const int color);
	// ������ (�ʒu�|�C���^�擾, �񐔐��������邩)
	void Initialize(int* pCount, Vector2* pPos, const Vector2& size, const int color);
	void Reset();
	void Update();
	void Draw();
public:
	// ���������Ƃ��̉��o
	void Pass();
private:
	// �ÓI�p�[�e�B�N���}�l�[�W���[�|�C���^
	static ParticleManager* spParticleMan_;
public:
	// �ÓI������
	static void StaticInitialze(ParticleManager* pParticleMan);
};

