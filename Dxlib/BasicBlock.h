#pragma once
#include "IBlock.h"
class BasicBlock :
    public IBlock
{
public:
    // ä÷êî
    BasicBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius = { 1,1 });
    ~BasicBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};

