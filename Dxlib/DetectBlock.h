#pragma once
#include "IBlock.h"

class DetectBlock : public IBlock
{
public:
    DetectBlock(const Vector2& pos, const Vector2& size);

    void Update(void) override;
    void Draw(void) override;
};

