#include "StoneBlock.h"

StoneBlock::StoneBlock(const Vector2& pos, const Vector2& radius) :
    IBlock(pos, radius)
{
    SetType(Type::STONE);
}

void StoneBlock::Update(void)
{
}

void StoneBlock::Draw(void)
{
    DrawBoxAA(
        GetPos().x - GetRadius().x, GetPos().y - GetRadius().y, // x1,y1
        GetPos().x + GetRadius().x, GetPos().y + GetRadius().y, // x2,y2
        0x0000ff, false);
}
