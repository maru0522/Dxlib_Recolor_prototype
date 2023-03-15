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

        // �\���̕ϐ�
        std::list<std::unique_ptr<IBlock>> blocks_;
    };

    static constexpr uint32_t blockDistance_{ 32 };
    static constexpr uint32_t defaultBlockSize_{ 32 };
    static constexpr uint32_t defaultBlockPosOffset_{ defaultBlockSize_ / 2 };

    // �ÓI�֐�
    static void LoadCSV(Stage* ins, std::string csvPath);

    static void Update(void);
    static void Draw(void);

    static inline void SetStage(std::unique_ptr<Stage>& ins) { current_ = std::move(ins); }
    static inline Stage* GetStage(void) { return current_.get(); }

private:
    // �ÓI�ϐ�
    static std::unique_ptr<Stage> current_;
};

#ifndef NON_USING_NAMESPACE_STAGE

using Stage = StageManager::Stage;

#endif // !NON_USING_NAMESPACE_STAGE