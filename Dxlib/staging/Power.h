#pragma once

namespace YMath
{
	class Power
	{
	private:
		// �J�E���^
		float count_ = 0;
		// �p���[�ő厞
		float end_ = 0;
		// ���삵�Ă��邩
		bool isAct_ = false;
	public:
		// ������
		void Initialize(const unsigned int max);
		// ���Z�b�g
		void Reset();
		// �X�V
		void Update(const bool isAct);
	public:
		// �䗦
		float Ratio();
		// ���݃p���[
		float Current() { return count_; }
		// �����Ă��邩
		bool IsAct() { return isAct_; }
		// �ő傩
		bool IsMax() { return count_ == end_; }
		// �[����
		bool IsZero() { return count_ == 0; }
	};
}