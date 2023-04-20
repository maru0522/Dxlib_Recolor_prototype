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
    static constexpr int blockRadius_{ 16 }; // îºåa
    static constexpr int blockSize_{ blockRadius_ * 2 }; // íºåa

    StageManager(void) = default;
    void Update(void);
    void Draw(void);

    std::array<std::array<int, 30>, 20> mapchip_;

    // ê√ìIä÷êî
    //static void LoadCSV(Stage* ins, std::string csvPath);
};