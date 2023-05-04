#include "BasicBlock.h"

BasicBlock::BasicBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::BASIC);
}

void BasicBlock::Update(void)
{
}

void BasicBlock::Draw(void)
{
    int posX{ static_cast<int>(GetPos().x) }, posY{ static_cast<int>(GetPos().y) };
    int radiusX{ static_cast<int>(GetRadius().x) }, radiusY{ static_cast<int>(GetRadius().y) };

    DrawBox(
        posX - radiusX, posY - radiusY,
        posX + radiusX, posY + radiusY,
        0xffff00, true
    );

    DrawCircle(static_cast<int>(GetPos().x), static_cast<int>(GetPos().y), 4, 0x00ffff, true, 1);
}
