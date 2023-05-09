#pragma once
#include "IBlock.h"
class SpringBlock :
    public IBlock
{
public:
    // ä÷êî
    SpringBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius = { 1,1 });
    ~SpringBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};

