#pragma once

namespace YMath
{
	class Timer
	{
	private:
		// �J�E���^
		float count_ = 0;
		// �^�C�}�[�I������
		float end_ = 0;
		// ���삵�Ă��邩
		bool isAct_ = false;
	public:
		// ������
		void Initialize(const unsigned int time);
		// ���Z�b�g
		void Reset(const bool isAct);
		// �X�V
		void Update();
	public:
		// �䗦
		float Ratio();
		// ���ݎ���
		float Current() { return count_; }
		// �����Ă��邩
		bool IsAct() { return isAct_; }
		// �I��������
		bool IsEnd() { return end_ != 0 && count_ == end_; }
		// ����ݒ�
		void SetActive(bool isAct) { isAct_ = isAct; }
	};
}