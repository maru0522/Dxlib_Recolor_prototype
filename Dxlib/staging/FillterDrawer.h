#pragma once
#pragma once
#include "../Vector2.h"
#include "ParticleManager.h"

class FillterDrawer
{
private:
	// �ʒu�|�C���^
	Vector2* pPos_ = nullptr;
	// ���a
	Vector2 size_;
	// �F
	int color_ = 0xFFFFFF;
	// �����Ă��邩�t���O
	bool isMove_ = false;

	// �r�[�R������t���O
	bool isBeaconAct_ = false;
	// �r�[�R�����o�C���^�[�o���^�C�}�[
	YMath::Timer intervalTim_;
	// ���M�J�E���^
	int beaconCounter_ = 0;
	// ���M�t���O
	bool isSign_ = false;

public:
	// ������ (�ʒu�|�C���^�擾)
	void Initialize(Vector2* pPos, const Vector2& size, const int color);
	void Reset();
	void Update();
	void Draw();
public:
	// ����؂�ւ����Ƃ��̉��o (�����Ȃ�true)
	void Switch(const bool isMove);
private:
	// �ÓI�p�[�e�B�N���}�l�[�W���[�|�C���^
	static ParticleManager* spParticleMan_;
public:
	// �ÓI������
	static void StaticInitialze(ParticleManager* pParticleMan);
};
