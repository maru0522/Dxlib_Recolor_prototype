#pragma once
#include <array>
#include "IBlock.h"
#include <memory>
#include "Player.h"

class Filter
{
private:
    // íËã`
    enum class Direction
    {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT
    };

public:
    // ä÷êî
    static const unsigned int defaultElemWidth_{ 3 };
    static const unsigned int defaultElemHeight_{ 3 };

    Filter(Player* pPtr);
    void Update(void);
    void Draw(void);

    void CopyToFilter(void);
    void PlaceToMapchip(void);

private:
    void UpdatePos(void);

    std::unique_ptr<IBlock> CutPointingBlock(int offsetY, int offsetX);
    std::unique_ptr<IBlock> PastePointingBlock(int mcElemY, int mcElemX);

    void DrawDebug(void);

    // ïœêî
    unsigned int basePointByElemX_{};
    unsigned int basePointByElemY_{};
    unsigned int possibleMoveBlock_{};
    Direction dir_{};
    Player* pPtr_{};
    std::array<std::array<std::unique_ptr<IBlock>, defaultElemWidth_>, defaultElemHeight_> mapchip_;
};

