#pragma once
#include "../Vector2.h"
#include "ParticleManager.h"

class BeaconDrawer
{
private:
	// �`�̎��
	enum class Shape
	{
		Circle, // �~
		Rectangle, // ��`
		None, // ����
	};
private:
	// �`
	Shape shape = Shape::None;

	// �ʒu�|�C���^
	Vector2* pPos_ = nullptr;
	// �䗦
	Vector2 ratio_;
	// �F
	int* pColor_ = nullptr;

	// ����t���O
	bool isAct_ = false;
	// �t���[��
	uint32_t frame_ = 0;
	// �C���^�[�o���^�C�}�[
	YMath::Timer intervalTim_;
	// ���M�J�E���^
	int counter_ = 0;
	// �ő唭�M��
	int maxCount_ = 0;
	// ���M�t���O
	bool isSign_ = false;
	// �����t���O
	bool isRecede_ = false;
public:
	// ������ (�ʒu�|�C���^�擾)
	void Initialize(Vector2* pPos, int* pColor);
	// ������ (�ʒu�|�C���^, �䗦�擾)
	void Initialize(Vector2* pPos, const Vector2& ratio, int* pColor);
	void Reset();
	void Update();
public:
	// ���M
	void Sign(const uint32_t frame, const bool isRecede, const uint32_t count, const uint32_t intervalFrame);
private:
	// �ÓI�p�[�e�B�N���}�l�[�W���[�|�C���^
	static ParticleManager* spParticleMan_;
public:
	// �ÓI������
	static void StaticInitialze(ParticleManager* pParticleMan);
};

