#include "FillterDrawer.h"
#include "DxLib.h"
#include <cassert>

ParticleManager* FillterDrawer::spParticleMan_ = nullptr;

static const int IntervalTime = 5;
static const int MaxBeaconCount = 3;

static const int MaxAlpha = 200;
static const int StopAlpha = 100;

void FillterDrawer::Initialize(Vector2* pPos, const Vector2& size, const int color)
{
	assert(pPos);
	pPos_ = pPos;
	size_ = size;
	color_ = color;

	intervalTim_.Initialize(IntervalTime);

	Reset();
}

void FillterDrawer::Reset()
{
	isMove_ = false;
	isBeaconAct_ = false;
	intervalTim_.Reset(false);
	beaconCounter_ = 0;
	isSign_ = false;
}

void FillterDrawer::Switch(const bool isMove)
{
	Reset();
	isMove_ = isMove;
	intervalTim_.SetActive(true);
	isBeaconAct_ = true;
}

void FillterDrawer::Update()
{
	// �r�[�R�������삵�Ă��Ȃ��Ȃ�X�V���Ȃ�
	if (isBeaconAct_ == false) { return; }

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
		beaconCounter_++;
		if (beaconCounter_ >= MaxBeaconCount)
		{
			// �I��
			isAgain = false;
			isBeaconAct_ = false;
		}

		// ���Z�b�g
		intervalTim_.Reset(isAgain);

		// ���M
		isSign_ = true;
	}

	// ���M����Ȃ�
	if (isSign_)
	{
		// �䗦���v�Z (X�)
		Vector2 ratio;
		ratio.x = 1.0f;
		ratio.y = size_.y / size_.x;

		// �����̈ʒu�Ƀp�[�e�B�N������ (���� �� �����g)
		spParticleMan_->EmitRectWave(!isMove_, { pPos_->x, pPos_->y }, { ratio.x, ratio.y }, color_);
	}
}

void FillterDrawer::Draw()
{
	// �����Ȃ��Ȃ瓧����
	int alpha = MaxAlpha;
	if (isMove_ == false) { alpha = StopAlpha; }

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	Vector2 leftTop = *pPos_ - (size_ / 2.0f);
	Vector2 rigthBottom = *pPos_ + (size_ / 2.0f);
	DrawBox(leftTop.x, leftTop.y, rigthBottom.x, rigthBottom.y, color_, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void FillterDrawer::StaticInitialze(ParticleManager* pParticleMan)
{
	assert(pParticleMan);
	spParticleMan_ = pParticleMan;
}
