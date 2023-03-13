#pragma once
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"

// �p�[�e�B�N���C���^�[�t�F�[�X
class IParticle
{
public:
	bool isAlive_ = false;	 // �����t���O
protected:
	YMath::Vec2 pos_;	 // �ʒu
	YMath::Vec2 rota_;	 // �p�x
	YMath::Vec2 scale_;	 // �傫��
	int color_ = 0xFFFFFF; // �F
	int alpha_ = 255; // ���ߓx
	bool isFill_ = true;
public:
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;
public:
	IParticle() = default;
	virtual ~IParticle() = default;
};

// �g
class Wave : public IParticle 
{
private:
	YMath::Ease<float> scaleEas_; // �傫�����
	YMath::Ease<int> alphaEas_; // ���ߓx���
	YMath::Timer scaleTim_; // ��ԗp�^�C�}�[
public:
	// ����
	void Emit(const int frame, const YMath::Vec2& pos, const int color = 0xFFFFFF, const bool isFill = true);
	void Update() override;
	void Draw() override;
public:
	Wave() = default;
	~Wave() override = default;
};