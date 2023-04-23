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

    struct McInfo
    {
        IBlock::Type type{};
        Vector2 pos{};
    };

public:
    // ä÷êî
    static const unsigned int defaultElemWidth_{ 3 };
    static const unsigned int defaultElemHeight_{ 3 };

    Filter(Player* pPtr);
    void Update(void);
    void Draw(void);


private:
    void CopyToFilter(void);
    void PlaceToMapchip(void);
    void MapchipAdaptDirection(Direction nextDir);
    std::unique_ptr<IBlock> GenerateBlock(IBlock::Type type,const Vector2& pos, const Vector2& radius);


    void UpdatePos(void);
    void RotateDirection(void);

    std::unique_ptr<IBlock> CutPointingBlock(int offsetY, int offsetX);
    void CheckMapchipAutoC(int mceY, int mceX, int offsetY, int offsetX);
    std::unique_ptr<IBlock> PastePointingBlock(int mcElemY, int mcElemX);
    void CheckMapchipAutoP(int mceY, int mceX, int offsetY, int offsetX);

    void DrawDebug(void);

    // ïœêî
    unsigned int basePointByElemX_{};
    unsigned int basePointByElemY_{};
    unsigned int possibleMoveBlock_{};
    Direction dir_{};
    Player* pPtr_{};
    std::array<std::array<std::unique_ptr<IBlock>, defaultElemWidth_>, defaultElemHeight_> mapchip_;
};

