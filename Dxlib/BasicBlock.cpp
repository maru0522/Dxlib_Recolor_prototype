#include "BasicBlock.h"
#include <DxLib.h>

BasicBlock::BasicBlock(const Vector2& pos, const Vector2& radius)
{
    SetPos(pos);
    SetRadius(radius);
    SetType(Type::BASIC);
}

void BasicBlock::Update(void)
{
}

void BasicBlock::Draw(void)
{
    DrawBoxAA(
        GetPos().x - GetRadius().x, GetPos().y - GetRadius().y, // x1,y1
        GetPos().x + GetRadius().x, GetPos().y + GetRadius().y, // x2,y2
        0xffffff, false);
}
