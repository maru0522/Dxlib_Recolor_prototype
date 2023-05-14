#pragma once
#include "IBlock.h"
// 制約、初めから固定されてるピースに登録するのが望ましい

class WoodenBlock :
    public IBlock
{
public:
    // 関数
    WoodenBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius = { 1,1 });
    ~WoodenBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};

