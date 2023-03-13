#pragma once
#include <array>
#include <vector>
#include <list>
#include <string>
#include "IBlock.h"
#include <memory>

class StageManager
{
public:
	// 定義
	struct Stage
	{
	public:
		// 構造体関数
		void Register(IBlock* p_block);
		void Update(void);
		void Draw(void);

		std::list<std::unique_ptr<IBlock>> getblocks_();

	//private:
		// 構造体変数
		std::list<std::unique_ptr<IBlock>> blocks_;
	};

	static constexpr uint32_t blockDistance_{ 32 };
	static constexpr uint32_t defaultBlockSize_{ 32 };
	static constexpr uint32_t defaultBlockPosOffset_{ defaultBlockSize_ / 2 };

	// 静的関数
	static void LoadCSV(Stage* ins, std::string csvPath);
};

#ifndef NON_USING_NAMESPACE_STAGE

using Stage = StageManager::Stage;

#endif // !NON_USING_NAMESPACE_STAGE