#pragma once
#include "IBlock.h"
class BasicBlock :
    public IBlock
{
public:
    // �֐�
    BasicBlock(const Vector2& pos, const Vector2& radius);

    void Update(void) override;
    void Draw(void) override;
};

