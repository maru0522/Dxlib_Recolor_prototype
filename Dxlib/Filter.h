#pragma once
#include <array>
#include "IBlock.h"
#include <memory>

class Filter
{
private:
    // 定義
    enum class Direction
    {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT
    };

public:
    // 関数
    static const unsigned int defaultElemWidth_{ 3 };
    static const unsigned int defaultElemHeight_{ 3 };

    Filter(void);
    void Update(void);
    void Draw(void);

    void CopyToFilter(void);

private:
    IBlock* CutPointingBlock(int offsetY, int offsetX);

    // 変数
    Vector2 basePointByElem_{};
    unsigned int possibleMoveBlock_{};
    Direction dir_{};
    std::array<std::array<std::unique_ptr<IBlock>, defaultElemWidth_>, defaultElemHeight_> mapchip_;
};

