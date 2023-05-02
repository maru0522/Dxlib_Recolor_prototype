#pragma once
#include "IBlock.h"
class PieceEntranceBlock :
    public IBlock
{
public:
    // ä÷êî
    PieceEntranceBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius = { 1,1 });
    ~PieceEntranceBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};

