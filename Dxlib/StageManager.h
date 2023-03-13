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
	// ��`
	struct Stage
	{
	public:
		// �\���̊֐�
		void Register(IBlock* p_block);
		void Update(void);
		void Draw(void);

		std::list<std::unique_ptr<IBlock>> getblocks_();

	//private:
		// �\���̕ϐ�
		std::list<std::unique_ptr<IBlock>> blocks_;
	};

	static constexpr uint32_t blockDistance_{ 32 };
	static constexpr uint32_t defaultBlockSize_{ 32 };
	static constexpr uint32_t defaultBlockPosOffset_{ defaultBlockSize_ / 2 };

	// �ÓI�֐�
	static void LoadCSV(Stage* ins, std::string csvPath);
};

#ifndef NON_USING_NAMESPACE_STAGE

using Stage = StageManager::Stage;

#endif // !NON_USING_NAMESPACE_STAGE