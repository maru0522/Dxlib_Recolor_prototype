#pragma once
#include "IBlock.h"
class StoneBlock :
    public IBlock
{
public:
    // �֐�
    StoneBlock(const Vector2& pos, const Vector2& radius);

    void Update(void) override;
    void Draw(void) override;
};

