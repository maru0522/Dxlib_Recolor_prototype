#pragma once

namespace YMath
{
	class Timer
	{
	private:
		// カウンタ
		float count_ = 0;
		// タイマー終了時刻
		float end_ = 0;
		// 動作しているか
		bool isAct_ = false;
	public:
		// 初期化
		void Initialize(const unsigned int time);
		// リセット
		void Reset(const bool isAct);
		// 更新
		void Update();
	public:
		// 比率
		float Ratio();
		// 現在時刻
		float Current() { return count_; }
		// 動いているか
		bool IsAct() { return isAct_; }
		// 終了したか
		bool IsEnd() { return end_ != 0 && count_ == end_; }
		// 動作設定
		void SetActive(bool isAct) { isAct_ = isAct; }
	};
}