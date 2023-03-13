#pragma once

namespace YMath
{
	class Power
	{
	private:
		// カウンタ
		float count_ = 0;
		// パワー最大時
		float end_ = 0;
		// 動作しているか
		bool isAct_ = false;
	public:
		// 初期化
		void Initialize(const unsigned int max);
		// リセット
		void Reset();
		// 更新
		void Update(const bool isAct);
	public:
		// 比率
		float Ratio();
		// 現在パワー
		float Current() { return count_; }
		// 動いているか
		bool IsAct() { return isAct_; }
		// 最大か
		bool IsMax() { return count_ == end_; }
		// ゼロか
		bool IsZero() { return count_ == 0; }
	};
}