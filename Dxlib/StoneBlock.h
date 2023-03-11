#pragma once
#include "IBlock.h"
#include "IColor.h"

class StoneBlock : public IBlock, public IColor
{
public:
    StoneBlock(const Vector2& pos, const Vector2& size, Color color);

    void Update(void) override;
    void Draw(void) override;
};

