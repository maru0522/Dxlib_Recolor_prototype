#include "BeaconDrawer.h"
#include <cassert>

ParticleManager* BeaconDrawer::spParticleMan_ = nullptr;

void BeaconDrawer::Initialize(Vector2* pPos, int* pColor)
{
	assert(pPos);
	pPos_ = pPos;

	shape = Shape::Circle;
	pColor_ = pColor;

	Reset();
}

void BeaconDrawer::Initialize(Vector2* pPos, const Vector2& ratio, int* pColor)
{
	assert(pPos);
	pPos_ = pPos;

	shape = Shape::Rectangle;
	ratio_ = ratio;
	pColor_ = pColor;

	Reset();
}

void BeaconDrawer::Reset()
{
	isAct_ = false;
	frame_ = 0;
	intervalTim_.Reset(false);
	counter_ = 0;
	maxCount_ = 0;
	isSign_ = false;
	isRecede_ = false;
}

void BeaconDrawer::Sign(const uint32_t frame, const bool isRecede, const uint32_t count, const uint32_t intervalFrame)
{
	Reset();

	frame_ = frame;
	maxCount_ = count;
	intervalTim_.Initialize(intervalFrame);
	intervalTim_.SetActive(true);

	isRecede_ = isRecede;
	isAct_ = true;
}

void BeaconDrawer::Update()
{
	// ���삵�Ă��Ȃ��Ȃ�X�V���Ȃ�
	if (isAct_ == false) { return; }

	// ���M�t���O��߂�
	isSign_ = false;

	// �C���^�[�o���^�C�}�[�X�V
	intervalTim_.Update();
	// �C���^�[�o���^�C�}�[���I�������
	if (intervalTim_.IsEnd())
	{
		// ������x��邩
		bool isAgain = true;

		// �J�E���g���ő�l�Ȃ�
		counter_++;
		if (counter_ >= maxCount_)
		{
			// �I��
			isAgain = false;
			isAct_ = false;
		}

		// ���Z�b�g
		intervalTim_.Reset(isAgain);

		// ���M
		isSign_ = true;
	}

	// ���M����Ȃ�
	if (isSign_)
	{
		// �����̈ʒu�Ƀp�[�e�B�N������
		if (shape == Shape::Circle)
		{
			spParticleMan_->EmitCircleWave(frame_, isRecede_, { pPos_->x, pPos_->y }, *pColor_);
		}
		else if (shape == Shape::Rectangle)
		{
			spParticleMan_->EmitRectWave(frame_, isRecede_, { pPos_->x, pPos_->y }, { ratio_.x, ratio_.y }, *pColor_);
		}
	}
}

void BeaconDrawer::StaticInitialze(ParticleManager* pParticleMan)
{
	assert(pParticleMan);
	spParticleMan_ = pParticleMan;
}
