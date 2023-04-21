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

    inline void SetMapchip(const std::array<std::array<int, 30>, 20>& mapchip) { mapchip_ = mapchip; }
    std::array<std::array<int, 30>, 20> mapchip_{};
    int offsetX{ blockRadius_ + 10 };
    int offsetY{ blockRadius_ };

    // ê√ìIä÷êî
     void LoadCSV(std::string csvPath);
};