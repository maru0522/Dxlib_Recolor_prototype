#include "SpringBlock.h"

SpringBlock::SpringBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::OBJECT);
}

void SpringBlock::Update(void)
{
}

void SpringBlock::Draw(void)
{
    int posX{ static_cast<int>(GetPos().x) }, posY{ static_cast<int>(GetPos().y) };
    int radiusX{ static_cast<int>(GetRadius().x) }, radiusY{ static_cast<int>(GetRadius().y) };

    DrawTriangle(
        posX, posY + radiusY,
        posX - radiusX, posY,
        posX + radiusX, posY,
        0x00ffff, true
    );
}
