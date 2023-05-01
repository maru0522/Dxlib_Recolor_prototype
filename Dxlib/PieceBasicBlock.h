#pragma once
#include "IBlock.h"

class PieceBasicBlock :
    public IBlock
{
public:
    PieceBasicBlock(const Vector2& pos, const Vector2& radius = { 1,1 });
    ~PieceBasicBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};

