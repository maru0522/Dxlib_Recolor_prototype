#include "WoodenBlock.h"
#include <cmath>

WoodenBlock::WoodenBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::WOODEN);
}

void WoodenBlock::Update(void)
{
    //SetPos({ GetPos().x,GetPos().y + 1 });
}

void WoodenBlock::Draw(void)
{
    int posX{ static_cast<int>(GetPos().x) }, posY{ static_cast<int>(GetPos().y) };
    int radiusX{ static_cast<int>(GetRadius().x) }, radiusY{ static_cast<int>(GetRadius().y) };

    DrawBox(
        posX - radiusX, posY - radiusY,
        posX + radiusX, posY + radiusY,
        0x8f563b, true
    );
}
