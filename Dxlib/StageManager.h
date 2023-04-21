#pragma once
#include <array>
#include <vector>
#include <list>
#include <string>
#include <memory>
#include "BlockFactory.h"

constexpr int blockRadius_{ 16 }; // ���a
constexpr int blockSize_{ blockRadius_ * 2 }; // ���a

class Stage
{
public:
    // �֐�
    Stage(void) = default;
    ~Stage(void) = default;

    void Update(void);
    void Draw(void);

    void LoadCSV(std::string csvPath);

    // �ϐ�
    std::list<std::unique_ptr<IBlock>> blocks_;
    std::vector<std::vector<IBlock*>> mapchip_;

private:
    int offsetX{ blockRadius_ + 10 };
    int offsetY{ blockRadius_ };
};

class StageManager
{
public:
    // �֐�
    static StageManager* GetInstance(void);

    void Update(void);
    void Draw(void);

    Stage* currentPtr_{ nullptr };

    inline void SetStage(Stage* ptr) { currentPtr_ = ptr; }
    inline Stage* GetStagePtr(void) { return currentPtr_; }

private:
    // singleton
    StageManager(void) = default;
};